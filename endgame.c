/* endgame.c
   
   This file written 2018-02-06 by Ayub Atif 
   */

#include <pic32mx.h>
#include <stdint.h>
#include <math.h>
#include "switch.h"

/*things*/
Point shipy[SHIP_SIZE];
Point boss[ALIEN_SIZE];
Point ship_bullet1;

void start_end(){	
	init_ship(shipy, 5, 16);
	init_alien(boss, 90, 12);
}

void update_end(){
	int i;
	clear_disp();

	for(i=0; i<SHIP_SIZE; i++)
		pointLight(shipy[i]);
	
	for(i=0; i<ALIEN_SIZE; i++)
		pointLight(boss[i]);
	
	invert();
}

int endgame_phase(void){
	clear_disp();

	int i,j,c0, win;
	win=c0=0;
	
	start_end();
	
	if(getbtns() == DOWN){
		for(i=0;i<SHIP_SIZE;i++)
			move_point(&shipy[i], 1);
		if(shipy[3].xpos==90){
			for(i=0;i<ALIEN_SIZE;i++){
				if(boss[i].ypos == shipy[10].ypos){
					win=1;
					for(j=0; j<ALIEN_SIZE; j++)
						boss[j].on=0;
					break;
				}
			}
		}
		if(shipy[0].xpos==120)
			if(win)
				return 1;
			return 0; /*gameover*/
	}
	
	move(shipy);
	
	if(c0++>1){
		move(boss);
		c0=0;
	}
	
	update_end();

	return 1;
}
