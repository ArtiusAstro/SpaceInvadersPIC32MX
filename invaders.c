/* invaders.c
   
   This file written 2018-02-06 by Ayub Atif 
   */

#include <pic32mx.h>
#include <stdint.h>
#include <math.h>
#include "switch.h"

volatile char* lights = (volatile char*) 0xbf886110; /*PORTE*/

int invaders_phase(){
	/*things*/
	Point shipy[SHIP_SIZE];
	Point barrier_1[BARRIER_SIZE];
	Point barrier_2[BARRIER_SIZE];
	Point alien_1[ALIEN_SIZE];
	Point alien_2[ALIEN_SIZE];
	Point alien_3[ALIEN_SIZE];
	Point alien_4[ALIEN_SIZE];
	Point alien_5[ALIEN_SIZE];
	Point alien_6[ALIEN_SIZE];
	Point alien_7[ALIEN_SIZE];
	Point alien_8[ALIEN_SIZE];
	Point alien_9[ALIEN_SIZE];
	Point rare_alien[RARE_SIZE];
	Point ship_bullet;
	Point alien1_bullet;
	Point alien2_bullet;
	Point alien3_bullet;
	Point alien4_bullet;
	Point alien5_bullet;
	Point alien6_bullet;
	Point alien7_bullet;
	Point alien8_bullet;
	Point alien9_bullet;

	/*collection*/
	Point* world[7] = {shipy, barrier_1, barrier_2, rare_alien, alien_1, alien_2, alien_3};
	Point* idiots[6] = {alien_4, alien_5, alien_6, alien_7, alien_8, alien_9};
	Point *bad_bullets[9] = {&alien1_bullet, &alien2_bullet, &alien3_bullet, &alien4_bullet, 
								&alien5_bullet, &alien6_bullet, &alien7_bullet, 
									&alien8_bullet, &alien9_bullet};

	int i,j,len,ded,c0,c1,c2,c3,cLED,cRARE,cDOWN, c1shot, c2shot, c3shot, c4shot, c5shot, c6shot,
			downtime, bullet_count, highscore, lives, game, win, inverted, sw;
			
	ded=c0=c1=c2=c3=cLED=cRARE=cDOWN=bullet_count=c1shot=c2shot=c3shot=win=0;
	
	highscore=0; /*highscore is used in they_got_shot(), a +1 for each is fine, with a +3 for the rare or smth and endgame at 10pts*/
	downtime=0; /*checks how many times the wave descended*/
	lives=5; /*game over at 0 lives*/
	inverted=1; /*invert when rare shot down, if >0 then invert display*/
	game=1;
	

	//start_invaders
	*lights=0x00;
	
	init_ship(shipy, 5, 16);
	init_barriers(barrier_1, barrier_2, 18);
	init_alien(alien_1, 100, 2);
	init_alien(alien_2, 100, 12);
	init_alien(alien_3, 100, 22);
	init_alien(alien_4, 90, 4);
	init_alien(alien_5, 90, 14);
	init_alien(alien_6, 90, 24);
	init_alien(alien_7, 80, 2);
	init_alien(alien_8, 80, 12);
	init_alien(alien_9, 80, 22);
	rare_spawn(rare_alien);
	
	while(game){
		sw=getsw(); //when first switch on, difficulty up
		
		if(lives==0)
			game=0;
		
		*lights = 1<<(lives-1);
		
		if(getbtns() == DOWN){
			if(bullet_count==0){
				ship_fire(&ship_bullet, shipy);
				bullet_count=1;
			}
		}
		
		if(!ship_bullet.on)
			bullet_count=0;
		
		if(cLED++>35){
			if(cRARE++>7){ 
				rare_spawn(rare_alien); //rare_alien grants power up on boom
				
				if(cDOWN++>0){
					if(downtime<MAX_DOWN+3)
						descend(world, idiots); //DANGER
					downtime++;	
					if(downtime==MAX_DOWN+2)
						game=0;
					
					cDOWN=0;
				}
				cRARE=0;
			}
			cLED=0;
		}
		
		move(shipy);
		move_point(&ship_bullet, 1);

		move_point(&alien1_bullet, 8);
		move_point(&alien2_bullet, 8);
		move_point(&alien3_bullet, 8);
		move_point(&alien4_bullet, 8);
		move_point(&alien5_bullet, 8);
		move_point(&alien6_bullet, 8);
		move_point(&alien7_bullet, 8);
		move_point(&alien8_bullet, 8);
		move_point(&alien9_bullet, 8);
		
		
		if(c1++>2){
			move(alien_1);
			move(alien_2);
			move(alien_3);
			c1=0;
		}
		if(c2++>4){
			move(alien_4);
			move(alien_5);
			move(alien_6);
			c2=0;
		}
		if(c3++>6){
			move(alien_7);
			move(alien_8);
			move(alien_9);
			move(rare_alien);
			c3=0;
		}
		
		if(c1shot++>200){
			if(alien_1[0].on)
			alien_fire(&alien1_bullet, alien_1);
			c1shot=0;
		}
		if(!sw){
			if(c2shot++>290){
				if(alien_9[0].on)
				alien_fire(&alien9_bullet, alien_9);
				if(alien_2[0].on)
				alien_fire(&alien2_bullet, alien_2);
				c2shot=0;
			}
		}
		if(c3shot++>330){
			if(alien_5[0].on)
			alien_fire(&alien5_bullet, alien_5);
			if(alien_7[0].on)
			alien_fire(&alien7_bullet, alien_7);
			c3shot=0;
		}
		if(!sw){
			if(c4shot++>400){
				if(alien_4[0].on)
				alien_fire(&alien4_bullet, alien_4);
				if(alien_3[0].on)
				alien_fire(&alien3_bullet, alien_3);
				c2shot=0;
			}
		}
		if(c5shot++>550){
			if(alien_6[0].on)
			alien_fire(&alien6_bullet, alien_6);
			if(alien_8[0].on)
			alien_fire(&alien8_bullet, alien_8);
			c3shot=0;
		}
		
		they_got_shot(&ship_bullet, world, idiots, &highscore);
		you_got_shot(bad_bullets, world, &lives, &inverted); 
		
		if(ship_bullet.xpos==115){
			for(i=0;i<RARE_SIZE;i++){
				if(rare_alien[i].ypos == ship_bullet.ypos){
					inverted = inverted * -1;
					break;
				}
			}
		}
		
		//update_invaders()
		clear_disp();
		
		//void r_u_ded(){ /*if an alien is shot, all its pixels are ded*/
		for(i=3; i<7; i++){
			switch(world[i][0].id){
				case ALIEN_1:
				case ALIEN_2:
				case ALIEN_3:
					len=ALIEN_SIZE;
					break;
				case RARE_ALIEN:
					len=RARE_SIZE;
					break;
				default: ;
			}
			ded=0;
			for(j=0; j<len; j++){
				if(!world[i][j].on)
					ded=1;
			}
			if(ded){
				for(j=0; j<len; j++)
					world[i][j].on=0;
			}
		}
		
		for(i=0; i<6; i++){
			ded=0;
			for(j=0; j<ALIEN_SIZE; j++){
				if(!idiots[i][j].on)
					ded=1;
			}
			if(ded){
				for(j=0; j<ALIEN_SIZE; j++)
					idiots[i][j].on=0;
			}
		}
		
		for(i=0; i<7; i++){
			switch(world[i][0].id){
				case SHIP: 
					len=SHIP_SIZE; 
					break;
				case BARRIER_1:
				case BARRIER_2:
					len=BARRIER_SIZE;
					break;
				case ALIEN_1:
				case ALIEN_2:
				case ALIEN_3:
					len=ALIEN_SIZE;
					break;
				case RARE_ALIEN:
					len=RARE_SIZE;
					break;
				default: ;
			}
			for(j=0; j<len; j++)
					pointLight(world[i][j]);
		}
		
		for(i=0; i<6; i++){
			for(j=0; j<ALIEN_SIZE; j++)
				pointLight(idiots[i][j]);
		}
			
		pointLight(ship_bullet);
		
		pointLight(alien1_bullet);
		pointLight(alien2_bullet);
		pointLight(alien3_bullet);
		
		pointLight(alien4_bullet);
		pointLight(alien5_bullet);
		pointLight(alien6_bullet);
		pointLight(alien7_bullet);
		pointLight(alien8_bullet);
		pointLight(alien9_bullet);
		
		if(!alien_1[0].on && !alien_2[0].on && !alien_3[0].on && !alien_4[0].on && !alien_5[0].on && !alien_6[0].on && !alien_7[0].on && !alien_8[0].on && !alien_9[0].on){
			game=0; //endgame
			win=1;
		}
		
		delay(10000);
	}
	
	if(win)
		return 4;
	return 1;
}
