/* main.c

   This file written 2018-02-06 by Ayub Atif 
   
   */

#include <pic32mx.h>
#include <stdint.h>
#include <math.h>
#include "switch.h"

Point ship[16];
//Point alien[25];

int game;

void delay(int cyc){
	int i;

	for(i = cyc; i > 0; i--);
}

/*#############################*/



/*#############################*/

void start(){
	init_ship(5, 16);
	//init_alien(5, 80);
	//init_barriers
}

int main(void) {
	init();
	clear_disp();

	start();
	
	/*#############################*/
	
	
	/*#############################*/
	
	game = 1;
	while(game) {
		
		move(ship);
		
		/*#############################*/
		
	
		/*#############################*/
		
		display_update();
		delay(100000);
	}
	
	for(;;) ;
	return 0;
}
