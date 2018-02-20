/* main.c
   
   This file written 2018-02-06 by Ayub Atif 
   */

#include <pic32mx.h>
#include <stdint.h>
#include <math.h>
#include "switch.h"

/*things*/
Point shipy[SHIP_SIZE];
Point alien_1[ALIEN_SIZE];
Point alien_2[ALIEN_SIZE];
Point alien_3[ALIEN_SIZE];
Point alien_4[ALIEN_SIZE];
Point barrier_1[BARRIER_SIZE];
Point barrier_2[BARRIER_SIZE];
Point rare_alien[RARE_SIZE];

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
	init_alien(alien_1, 80, 16);
	init_alien(alien_2, 90, 8);
	init_alien(alien_3, 100, 22);
	init_alien(alien_4, 100, 6);
	init_barriers(barrier_1, barrier_2, 25);
	rare_spawn(rare_alien);
}

int main(void) {
	init();
	*lights=0x01;
	clear_disp();

	start();
	
	/*#############################*/
	
	//lights off a specific entity
	/*
	int i;
	for(i=0; i<16; i++)
			pointLight(shipy[i], 0);
	*/
	
	/*#############################*/
	
	int c1,c2,c3,cLED,cRARE;
	c1=c2=c3=cLED=cRARE=0;
	game = 1;
	while(game) {
		
		if(cLED++>70){
			/*LED++*/
			*lights = *lights + (1<<cRARE);
			if(cRARE++>7){
				/*rare_spawn(rare_alien);*/
				*lights=0x01;
				cRARE=0;
			}
			cLED=0;
		}
		
		move(shipy);
		
		if(c1++>7){
			move(alien_1);
			move(rare_alien);
			c1=0;
		}
		
		if(c2++>4){
			move(alien_2);
			c2=0;
		}
		
		if(c3++>2){
			move(alien_3);
			move(alien_4);
			persist(barrier_1, 8);
			persist(barrier_2, 8);
			c3=0;
		}
		
		/*check for bullet collisions*/
		/*set movement bounded region*/
		/*show lives at top segment*/
		
		/*#############################*/
		
	
		/*#############################*/
		
		display_update();
		delay(75000);
	}
	
	for(;;) ;
	return 0;
}
