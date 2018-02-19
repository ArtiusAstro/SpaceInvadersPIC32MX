#include "switch.h"
#include <pic32mx.h>
#include <stdint.h>

void move(Point *thing){
	int i;
	
	int len = sizeof(thing)/sizeof(thing[0]);
	for(i=0; i<len; i++)
			move_point(&(thing[i]));
}

void init_ship(int x_origin, int y_origin){
	int i, j, count; /*i is y, j is x*/
	count=0;
	
	for(i=0; i<4; i++){
		for(j=0; j<4; j++){
			ship[count].xpos = x_origin + j;
			ship[count].ypos = y_origin + i;
			count++;
		}
	}
}
