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

/*collection*/
Point* world[7] = {shipy, barrier_1, barrier_2, alien_1, alien_2, alien_3, rare_alien,};
Point* idiots[6] = {alien_4, alien_5, alien_6, alien_7, alien_8, alien_9};					

int game;

volatile char* lights = (volatile char*) 0xbf886110; /*PORTE*/

void delay(int cyc){
	volatile int i;
	for(i=cyc; i>0; i--);
}

/*#############################*/



/*#############################*/

void start(){
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
}

void update(){
	int i, j, len;
	
	clear_disp();
	
	for(i=0; i<7; i++){
		switch(world[i][0].id){
			case SHIP: 
				len=SHIP_SIZE; 
				for(j=0; j<len; j++)
					pointLight(&world[i][j]);
				break;
			case BARRIER_1:
			case BARRIER_2:
				len=BARRIER_SIZE;
				for(j=0; j<len; j++)
					pointLight(&world[i][j]);
				break;
			case ALIEN_1:
			case ALIEN_2:
			case ALIEN_3:
				len=ALIEN_SIZE;
				for(j=0; j<len; j++)
					pointLight(&world[i][j]);
				break;
			case RARE_ALIEN:
				len=RARE_SIZE;
				for(j=0; j<len; j++)
					pointLight(&world[i][j]);
				break;
			default: ;
		}
	}
	
	for(i=0; i<6; i++)
		for(j=0; j<ALIEN_SIZE; j++)
			pointLight(&idiots[i][j]);
	
	display_update();
}

int main(void) {
	init();
	*lights=0x00;
	clear_disp();

	start();
	
	/*#############################*/
	
	//lights off a specific entity
	/*
	int i;
	for(i=0; i<16; i++)
			pointLight(shipy[i]);
	*/
	
	/*#############################*/
	
	int c1,c2,c3,cLED,cRARE,cDOWN,rare_trigger;
	c1=c2=c3=cLED=cRARE=cDOWN=rare_trigger=0;
	game = 1;
	while(game) {
		
		if(cLED++>60){
			//LED++
			*lights += 1<<cRARE;
			if(cRARE++>7 && !rare_trigger){ // after this graphics stop glitch idk
				rare_spawn(rare_alien); //rare_alien grants power up on boom
				//rare_trigger++; //dont spawn another rare until it ded
				*lights=0x00;
				
				/*if(cDOWN++>1){
					descend(world, idiots); //DANGER
					cDOWN=0;
				}*/
				cRARE=0;
			}
			cLED=0;
		}
		
		move(shipy);
		
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
		/*show lives at top segment*/
		
		/*#############################*/
		
	
		/*#############################*/
		
		update();
		delay(20000);
	}
	
	for(;;) ;
	return 0;
}
