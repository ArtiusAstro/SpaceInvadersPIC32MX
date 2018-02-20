/* point.c
   
   This file written 2018-02-14 by Ayub Atif 
   */

#include "switch.h"
#include <pic32mx.h>
#include <stdint.h>

int getbtns() {
	int btns234 = (PORTD >> 4) & 0xe;
	int btn1 = (PORTF >> 1) & 0x1;
	int read = btns234 + btn1;
	return read;
}

void spooky() {
        int i;
        for (i = 0; i < 32; i++) {
                set_pixel(127, i, 1);
        }
        display_update();
}

int mod(int n, int N) {
	int r = n % N;
	return (r < 0) ? (r + N) : r;
}

void pointLight(Point point, int on){
	
	set_pixel(point.xpos, point.ypos, on);
	
}

void move_point(Point *point, int ai) {
	int btns = getbtns();

	if(ai)
		btns = ai; /*if automated, go somewhere*/
	
	if(btns){
		pointLight(*point, 0);

		/*UP to DOWN is defined in header*/
		switch (btns) {
				case UP: point->xpos++; break;
				case LEFT: point->ypos--; break;
				case RIGHT: point->ypos++; break;
				case DOWN: point->xpos--; break;
				default:	;
		}
			
		pointLight(*point, 1);
	}
}
