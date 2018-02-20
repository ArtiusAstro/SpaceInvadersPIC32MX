/* assets.c
   
   This file written 2018-02-16 by Ayub Atif 
   */
   
#include "switch.h"
#include <pic32mx.h>
#include <stdint.h>

int alien_count=0;

void move(Point *thing){
	int i, len, ai; /*AI left=2 right=4*/
	
	switch(thing[0].id){
		case 0: 
			ai=0;
			len=SHIP_SIZE; break;
		case 3:
			ai=2;
			len=ALIEN_SIZE; break;
		case 4:
			ai=4;
			len=ALIEN_SIZE; break;
		case 5: 
			ai=2;
			len=ALIEN_SIZE; break;
		case 6:
			ai=2;
			len=RARE_SIZE; break;
		default: ;
	}
	
	for(i=0; i<len; i++)
			move_point(&thing[i], ai);
}

void persist(Point *thing, int len){
	int i;
	for(i=0; i<len; i++)
			pointLight(thing[i], 1);
}

void fire(Point *boi){
	
	/*             */
	
}

void init_ship(Point *ship, int x_origin, int y_origin){
	int i, j, len;
	len=0;
	
	for(i=0; i<4; i++){
		for(j=0; j<4; j++){
			ship[len].id = SHIP;
			ship[len].xpos = x_origin + j;
			ship[len].ypos = y_origin + i;
			len++;
		}
	}
	
	for(i=0; i<len; i++)
			pointLight(ship[i], 1);
	
}

void init_barriers(Point *barrier_1, Point *barrier_2, int x_origin){
	int i, j, len;
	len = 0;
	
	for(i=0; i<4; i++){
		for(j=0; j<2; j++){
			barrier_1[len].id = BARRIER_1;
			barrier_1[len].xpos = x_origin + j;
			barrier_1[len].ypos = 6 + i;
			len++;
		}
	}
	
	for(i=0; i<len; i++)
			pointLight(barrier_1[i], 1);

	len=0;
	
	for(i=0; i<4; i++){
		for(j=0; j<2; j++){
			barrier_2[len].id = BARRIER_2;
			barrier_2[len].xpos = x_origin + j;
			barrier_2[len].ypos = 20 + i;
			len++;
		}
	}
	
	for(i=0; i<len; i++)
			pointLight(barrier_2[i], 1);
	
}

void init_alien(Point *alien, int x_origin, int y_origin){
	alien_count = alien_count + 1;
	int i, len;
	len=0;
	
	for(i=0; i<4; i++){
		alien[len].xpos = x_origin;
		alien[len].ypos = y_origin + i;
		len++;
	}

	for(i=1; i<4; i++){
		alien[len].xpos = x_origin + i;
		alien[len].ypos = y_origin;
		len++;
	}

	for(i=1; i<4; i++){
		alien[len].xpos = x_origin + 3;
		alien[len].ypos = y_origin + i;
		len++;
	}

	for(i=1; i<3; i++){
		alien[len].xpos = x_origin + i;
		alien[len].ypos = y_origin + 3;
		len++;
	}
	
	switch(alien_count){
			case 1: 
				for(i=0; i<len; i++)
					alien[i].id = ALIEN_1; 
				break;
			case 2: 
				for(i=0; i<len; i++)
					alien[i].id = ALIEN_2; 
				break;
			case 3: 
				for(i=0; i<len; i++)
					alien[i].id = ALIEN_3; 
				break;
			default:	;
		}
	
	

	for(i=0; i<len; i++)
			pointLight(alien[i], 1);
}

void rare_spawn(Point *rare){
	int i, j, len, x_origin, y_origin;
	len=0;
	x_origin=115;
	y_origin=27;
	
	
	for(i=0; i<5; i++){
		rare[len].id = RARE_ALIEN; 
		rare[len].xpos = x_origin + i;
		rare[len].ypos = y_origin + i;
		len++;
	}
	
	for(i=0; i<5; i++){
		if(i==2) continue;
		rare[len].id = RARE_ALIEN; 
		rare[len].xpos = x_origin - i + 4;
		rare[len].ypos = y_origin + i;
		len++;
	}
	
}
