/* graphics.c
   
   This file written 2018-02-06 by Ayub Atif 
   */

#include <pic32mx.h>
#include <stdint.h>
#include "switch.h"

uint8_t pixels[512];

uint8_t spi_send_recv(uint8_t data) {
	while(!(SPI2STAT & 0x08));
	SPI2BUF = data;
        while(!(SPI2STAT & 0x01));
	return SPI2BUF;
}

void display_update() {
	int i;
	set_disp_data();

	for(i = 0; i < 512; i++) {
		spi_send_recv(pixels[i]);
	}
}

/*void invert(){
	int i;
	for(i = 0; i < 512; i++) {
		spi_send_recv(~pixels[i]);
	}
	
	display_update();
}*/

void set_pixel(int x, int y, int on) {
	
	int i = (y / 8) * 128 + x;

	uint8_t k = 1 << (y % 8);

	if (on) {
		pixels[i] |= k;
	} else {
		pixels[i] &= ~k;
	}
}

int get_pixel(int x, int y) {
        int i = (y / 8) * 128 + x;
        return (pixels[i] >> (y % 8)) & 0x1;
}

void clear_disp() {
	int x, y;
	for (y = 0; y < 32; y++) {
		for (x = 0; x < 128; x++) {
			set_pixel(x, y, 0);
		}
	}
	display_update();
}
