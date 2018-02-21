/* point.c
   
   This file written 2018-02-14 by Ayub Atif 
   */

#include "switch.h"
#include <pic32mx.h>
#include <stdint.h>

void spooky() {
        int i;
        for (i = 0; i < 32; i++) {
                set_pixel(127, i, 1);
        }
        display_update();
}

int mod_loop(int n, int N) {
	int r = n % N;
	return (r < 0) ? (r + N) : r;
}

int kill(Point *point){
	return (point->ypos<0 || point->ypos>31 || point->xpos<0 || point->xpos>127) ? 1 : 0;
}

void pointLight(Point *point){
	set_pixel(point->xpos, point->ypos, point->on);
}

void move_point(Point *point, int ai) {
	int btns = getbtns();

	if(ai)
		btns = ai; /*if automated, go somewhere*/

	/*UP to DOWN is defined in header*/
	switch (btns) {
		//case UP: (point->xpos++); break;
		case LEFT: (point->ypos--); break;
		case RIGHT: (point->ypos++); break;
		//case DOWN: (point->xpos--); break;
		default:	;
	}
	
	if(kill(point)){
		switch (point->id){
			case RARE_ALIEN: //point->on=0; break;
			default:
				//point->xpos=mod_loop(point->xpos, 128); not needed rn, probs 4 bullet
				point->ypos=mod_loop(point->ypos, 32);
			}
	}
}



