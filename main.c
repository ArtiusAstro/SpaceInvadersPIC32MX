/* main.c
   
   This file written 2018-02-06 by Ayub Atif 
   */

#include <pic32mx.h>
#include <stdint.h>
#include <math.h>
#include "switch.h"

void delay(int cyc){
	volatile int i;
	for(i=cyc; i>0; i--);
}

int main(void){
	int phase;
	phase=1;
	init();
	
	for(;;){
		switch(phase){
			case 0: /*title*/
			//phase = title_phase();
			break;
			
			case 1: /*invaders*/
			phase = invaders_phase();
			break;
			
			case 2: /*pause*/
			//phase = pause_phase();
			break;
			
			case 4: /*endgame*/
			phase = endgame_phase();
			break;
		}
		delay(10);
	}

	return 0;
}
