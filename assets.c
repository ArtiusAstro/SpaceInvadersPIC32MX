/* assets.c
   
   This file written 2018-02-16 by Ayub Atif 
   */
   
#include "switch.h"
#include <pic32mx.h>
#include <stdint.h>

int alien_count=0;

void move(Point *thing){
	int i, len, ai; /*AI left=2 right=4*/
	
	/*ship may not go beyond [512]*/
	if(thing[0].id==SHIP)
		if((getbtns()==LEFT && thing[0].ypos<1) || (getbtns()==RIGHT && thing[SHIP_SIZE-1].ypos>30))
			return;
	
	switch(thing[0].id){
		case SHIP: 
			ai=0;
			len=SHIP_SIZE; break;
			
		case ALIEN_1:
		case ALIEN_2:
		case ALIEN_3:
		case ALIEN_7:
		case ALIEN_8:
		case ALIEN_9:
			ai=2;
			len=ALIEN_SIZE; break;
		case RARE_ALIEN:
			ai=2;
			len=RARE_SIZE; break;
			
		case ALIEN_4:
		case ALIEN_5:
		case ALIEN_6:
			ai=4;
			len=ALIEN_SIZE; break;
		
		case SHIP_BULLET:
			ai=1;
			break;
			
		case ALIEN_BULLET:
			ai=8;
		default: ;
	}
	
	for(i=0; i<len; i++)
			move_point(&thing[i], ai);
}

void descend(Point** world, Point** idiots){ //broken
	int i, j;
	
	for(i=4; i<7; i++){
		for(j=0; j<ALIEN_SIZE; j++)
			world[i][j].xpos+=-10;
	}

	for(i=0; i<6; i++){
		for(j=0; j<ALIEN_SIZE; j++)
			idiots[i][j].xpos+=-10;
	}
}

void ship_fire(Point *bullet, Point* thing){
	/*banzaiiiiii*/
	bullet->id=SHIP_BULLET;
	bullet->xpos=6;
	bullet->ypos=thing[9].ypos;
	bullet->on=1;
}

void init_ship(Point *ship, int x_origin, int y_origin){
	int i, j, len;
	len=0;
	
	for(i=0; i<4; i++){
		for(j=0; j<4; j++){
			ship[len].id = SHIP;
			ship[len].xpos = x_origin + j;
			ship[len].ypos = y_origin + i;
			ship[len].on = 1;
			len++;
		}
	}
	
}

void init_barriers(Point *barrier_1, Point *barrier_2, int x_origin){
	int i, j, len;
	len = 0;
	
	for(i=0; i<7; i++){
		for(j=0; j<2; j++){
			barrier_1[len].id = BARRIER_1;
			barrier_1[len].xpos = x_origin + j;
			barrier_1[len].ypos = 4 + i;
			barrier_1[len].on = 1;
			len++;
		}
	}
	
	len=0;
	
	for(i=0; i<7; i++){
		for(j=0; j<2; j++){
			barrier_2[len].id = BARRIER_2;
			barrier_2[len].xpos = x_origin + j;
			barrier_2[len].ypos = 19 + i;
			barrier_2[len].on = 1;
			len++;
		}
	}
	
}

void init_alien(Point *alien, int x_origin, int y_origin){
	alien_count += 1;
	int i, len;
	len=0;
	
	for(i=0; i<4; i++){
		alien[len].xpos = x_origin;
		alien[len].ypos = y_origin + i;
		alien[len].on = 1;
		len++;
	}

	for(i=1; i<4; i++){
		alien[len].xpos = x_origin + i;
		alien[len].ypos = y_origin;
		alien[len].on = 1;
		len++;
	}

	for(i=1; i<4; i++){
		alien[len].xpos = x_origin + 3;
		alien[len].ypos = y_origin + i;
		alien[len].on = 1;
		len++;
	}

	for(i=1; i<3; i++){
		alien[len].xpos = x_origin + i;
		alien[len].ypos = y_origin + 3;
		alien[len].on = 1;
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
			case 4:
				for(i=0; i<len; i++)
					alien[i].id = ALIEN_4; 
				break;
			case 5: 
				for(i=0; i<len; i++)
					alien[i].id = ALIEN_5; 
				break;
			case 6: 
				for(i=0; i<len; i++)
					alien[i].id = ALIEN_6; 
				break;
			case 7: 
				for(i=0; i<len; i++)
					alien[i].id = ALIEN_7; 
				break;
			case 8:
				for(i=0; i<len; i++)
					alien[i].id = ALIEN_8; 
				break;
			case 9:
				for(i=0; i<len; i++)
					alien[i].id = ALIEN_9; 
				break;
			default:	;
		}
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
		rare[len].on = 1;
		len++;
	}
	
	for(i=0; i<5; i++){
		if(i==2) continue;
		rare[len].id = RARE_ALIEN; 
		rare[len].xpos = x_origin - i + 4;
		rare[len].ypos = y_origin + i;
		rare[len].on = 1;
		len++;
	}
	
}
