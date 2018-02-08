/* main.c
   
   This file written 2018-02-06 by Ayub Atif 
   */

#include <pic32mx.h>
#include <stdlib.h>
#include <stdint.h>
#include "graphics.h"

int main(void) {
	
	spi_init();
	display_init();
	display_string(0, "shit its 1am");
	display_string(1, "0123456789ABCDEF");
	display_string(2, "KTH");
	display_string(3, "Ayub/Wajd proj");
	display_update();
	
	for(;;);
	return 0;
}
