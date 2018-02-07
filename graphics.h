#ifndef graphics_h
#define graphics_h

#include <stdint.h>
 
/*A trivial for loop delay*/
void delay(int cyc);
/*spi send/recieve*/
uint8_t spi_send_recv(uint8_t data);
/*init spi*/
void spi_init();
/*init display*/
void display_init();
/*can output 4 lines of text*/
void display_string();
/*no clue*/
void display_update();

#endif
