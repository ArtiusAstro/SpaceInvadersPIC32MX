/* main.c
   
   This file written 2018-02-06 by Ayub Atif 
   */

#include <pic32mx.h>
#include <stdint.h>
#include <math.h>
#include "switch.h"

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
Point ship_bullet1;
Point ship_bullet2;
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
Point bullets[5]; //0 and 1 are ship, rest alien
Point idiot_bullets[6]; //all alien

int game;
int inverted;

volatile char* lights = (volatile char*) 0xbf886110; /*PORTE*/

void delay(int cyc){
	volatile int i;
	for(i=cyc; i>0; i--);
}

void start(){
	*lights=0x00;
	
	bullets[0] = ship_bullet1;
	bullets[1] = ship_bullet2;
	bullets[2] = alien1_bullet;
	bullets[3] = alien2_bullet;
	bullets[4] = alien3_bullet;
	
	idiot_bullets[0] = alien4_bullet;
	idiot_bullets[1] = alien5_bullet;
	idiot_bullets[2] = alien6_bullet;
	idiot_bullets[3] = alien7_bullet;
	idiot_bullets[4] = alien8_bullet;
	idiot_bullets[5] = alien9_bullet;
	
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
}

void r_u_ded(){ /*if an alien is shot, all its pixels are ded*/
	int i, j, len, ded;
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
	
}

void update(){
	int i, j, len;
	clear_disp();
	
	r_u_ded();
	
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
		
	if(ship_bullet1.on)
		pointLight(ship_bullet1);
	
	for(i=2; i<5; i++)
		pointLight(bullets[i]);

	for(i=0; i<6; i++)
		pointLight(idiot_bullets[i]);
	
	if(inverted>0)
		invert();
	else
		display_update();
}

int main(void){
	init();
	clear_disp();

	int i,c0,c1,c2,c3,cLED,cRARE,cDOWN, c1shot, c2shot, c3shot, downtime, bullet_count, highscore, lives;
	c0=c1=c2=c3=cLED=cRARE=cDOWN=bullet_count=c1shot=c2shot=c3shot=0;
	
	highscore=0; /*highscore is used in they_got_shot(), a +1 for each is fine, with a +3 for the rare or smth and endgame at 10pts*/
	downtime=0; /*checks how many times the wave descended*/
	lives=2; /*game over at 0 lives*/
	inverted=1; /*invert when rare shot down, if >0 then invert display*/
	
	start();
	
	game = 1;
	while(game){
		
		if(getbtns() == DOWN){
			if(bullet_count==0){
				ship_fire(&ship_bullet1, shipy);
				bullet_count=1;
			}
		}
		
		if(!ship_bullet1.on)
			bullet_count=0;
		
		if(cLED++>35){
			//LED++
			*lights += 1<<cRARE;
			if(cRARE++>7){ 
				rare_spawn(rare_alien); //rare_alien grants power up on boom
				*lights=0x00;
				
				if(cDOWN++>0){
					if(downtime<MAX_DOWN+1)
						descend(world, idiots); //DANGER
					downtime++;	
					if(downtime==MAX_DOWN);
						/*GAME OVER*/
					
					cDOWN=0;
				}
				cRARE=0;
			}
			cLED=0;
		}
		
		move(shipy);
		move_point(&ship_bullet1, 1);
		move_point(&ship_bullet2, 1);

		move_point(&alien1_bullet, 8);
		move_point(&alien2_bullet, 8);
		move_point(&alien3_bullet, 8);
		
		for(i=0;i<6;i++)
			move_point(&idiot_bullets[i], 8);
		
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
		
		if(c1shot++>70){
			alien_fire(&alien1_bullet, alien_1);
			alien_fire(&alien2_bullet, alien_2);
			alien_fire(&alien3_bullet, alien_3);
			c1shot=0;
		}
		if(c2shot++>140){
			alien_fire(&alien4_bullet, alien_4);
			alien_fire(&alien5_bullet, alien_5);
			alien_fire(&alien6_bullet, alien_6);
			c2shot=0;
		}
		if(c3shot++>180){
			alien_fire(&alien7_bullet, alien_7);
			alien_fire(&alien8_bullet, alien_8);
			alien_fire(&alien9_bullet, alien_9);
			c3shot=0;
		}
		
		/*#############################*/
		
		they_got_shot(&ship_bullet1, &ship_bullet2, world, idiots, &highscore);
		you_got_shot(bullets, idiot_bullets, world, &lives);
		
		if(ship_bullet1.xpos==115){
			for(i=0;i<RARE_SIZE;i++){
				if(rare_alien[i].ypos == ship_bullet1.ypos){
					inverted = inverted * -1;
					break;
				}
			}
		}
	
		/*#############################*/
		
		update();
		delay(10);
	}
	
	for(;;) ;
	return 0;
}
