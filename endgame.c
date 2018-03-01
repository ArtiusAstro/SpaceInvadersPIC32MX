/* endgame.c
   
   This file written 2018-02-06 by Ayub Atif 
   */

#include <pic32mx.h>
#include <stdint.h>
#include <math.h>
#include "switch.h"

int endgame_phase(){
	/*things*/
	Point shipy[SHIP_SIZE];
	Point boss[ALIEN_SIZE];
	Point ship_bullet1;

	int i,j,c0, c1, win, game, shot;
	win=c0=c1=0;
	
	game=1;
	shot=0; //ship has been shot
	
	//start_end();
	init_ship(shipy, 5, 16);
	init_alien(boss, 80, 12);
	
	while(game){
		if(getbtns() == DOWN)
			shot=1;
			
		if(shot)
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
			game=0;
	
		if(c1++>20)
			move(shipy);
		
		if(c0++>1){
			move(boss);
			c0=0;
		}
		
		//void update_end()
		clear_disp();

		for(i=0; i<SHIP_SIZE; i++)
			pointLight(shipy[i]);
		
		for(i=0; i<ALIEN_SIZE; i++)
			pointLight(boss[i]);
		
		display_update();

		delay(10000);
	}
	if(win)
		return 1;
	return 4; /*gameover*/
}
