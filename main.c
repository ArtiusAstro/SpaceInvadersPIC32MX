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

void update(){
	int i, j, len, ded;
	
	clear_disp();
	
	for(i=0; i<7; i++){
		switch(world[i][0].id){
			case SHIP: 
				len=SHIP_SIZE; 
				for(j=0; j<len; j++)
					pointLight(world[i][j]);
				break;
			case BARRIER_1:
			case BARRIER_2:
				len=BARRIER_SIZE;
				for(j=0; j<len; j++)
					if(world[i][j].on)
						pointLight(world[i][j]);
				break;
			case ALIEN_1:
			case ALIEN_2:
			case ALIEN_3:
				len=ALIEN_SIZE;
				ded=0;
				for(j=0; j<len; j++)
					if(!world[i][j].on){
						ded++;
						break;
					}
				if(!ded)	
					for(j=0; j<len; j++)
						pointLight(world[i][j]);
				break;
			case RARE_ALIEN:
				len=RARE_SIZE;
				ded=0;
				for(j=0; j<len; j++)
					if(!world[i][j].on){
						ded++;
						break;
					}
				if(!ded)	
					for(j=0; j<len; j++)
						pointLight(world[i][j]);
				break;
			default: ;
		}
	}
	
	for(i=0; i<6; i++){
		ded=0;
		for(j=0; j<ALIEN_SIZE; j++)
			if(!idiots[i][j].on){
				ded++;
				break;
			}
		if(!ded)
			for(j=0; j<ALIEN_SIZE; j++)
				pointLight(idiots[i][j]);
			
	}
		
	if(ship_bullet1.on)
		pointLight(ship_bullet1);	
	
	display_update();
}

int main(void){
	init();
	clear_disp();

	start();
	
	int i,c0,c1,c2,c3,cLED,cRARE,cDOWN,rare_trigger,bullet_count;
	c0=c1=c2=c3=cLED=cRARE=cDOWN=rare_trigger=bullet_count=0;
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
		
		if(!rare_alien[0].on) /*check if rare shot down*/
			rare_trigger++;
		
		if(cLED++>120){
			//LED++
			*lights += 1<<cRARE;
			if(cRARE++>7){ 
				if(rare_trigger)
					rare_spawn(rare_alien); //rare_alien grants power up on boom // after this graphics stop glitch idk
					rare_trigger=0;
					
				*lights=0x00;
				
				/*if(cDOWN++>1){
					descend(alien_1, alien_2, alien_3, alien_4, alien_5, alien_6, alien_7, alien_8, alien_9); //DANGER
					cDOWN=0;
				}*/
				cRARE=0;
			}
			cLED=0;
		}
		
		move(shipy);
		move_point(&ship_bullet1, 1);
		move_point(&ship_bullet2, 1);
		
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
		
		/*check for bullet collisions*/
		/*set movement bounded region*/  /*OK*/
		/*lives system*/
		
		/*#############################*/
		
		they_got_shot(ship_bullet1, ship_bullet2, world, idiots);
		//you_got_shot(bullets, idiot_bullets, world)
	
		/*#############################*/
		
		update();
		delay(1000);
	}
	
	for(;;) ;
	return 0;
}
