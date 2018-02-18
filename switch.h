/* graphics.h
   
   This file written 2018-02-06 by Ayub Atif 

   */

#ifndef HEADER_FILE
#define HEADER_FILE

#include <pic32mx.h>
#include <stdint.h> 

#define DISPLAY_VDD PORTFbits.RF6
#define DISPLAY_VBATT PORTFbits.RF5
#define DISPLAY_COMMAND_DATA PORTFbits.RF4
#define DISPLAY_RESET PORTGbits.RG9

#define DISPLAY_VDD_PORT PORTF
#define DISPLAY_VDD_MASK 0x40
#define DISPLAY_VBATT_PORT PORTF
#define DISPLAY_VBATT_MASK 0x20
#define DISPLAY_COMMAND_DATA_PORT PORTF
#define DISPLAY_COMMAND_DATA_MASK 0x10
#define DISPLAY_RESET_PORT PORTG
#define DISPLAY_RESET_MASK 0x200

#define UP 1
#define LEFT 2
#define RIGHT 4
#define DOWN 8

/*a pixel*/
typedef struct {
        int xpos;
        int ypos;
} Point;

void init();

void set_pixel(int, int, int);

uint8_t spi_send_recv(uint8_t);

void display_update();

void set_disp_data();

void clear_disp();

void move_point(Point*);

int mod(int, int);

#endif
