/* switch.h
   
   This file written 2018-02-06 by Ayub Atif 
   */

#ifndef SWITCH_H
#define SWITCH_H

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

/*####################################################################*/

#define UP 1 
#define LEFT 2 //standard
#define RIGHT 4 //standard
#define DOWN 8 //wave descends

/*####################################################################*/

#define SHIP 0
#define BARRIER_1 1
#define BARRIER_2 2
#define RARE_ALIEN 3
#define ALIEN_1 4
#define ALIEN_2 5
#define ALIEN_3 6
#define ALIEN_4 7
#define ALIEN_5 8
#define ALIEN_6 9
#define ALIEN_7 10
#define ALIEN_8 11
#define ALIEN_9 12

#define SHIP_SIZE 16
#define ALIEN_SIZE 12
#define RARE_SIZE 9
#define BARRIER_SIZE 14

/*####################################################################*/

typedef struct {
        int xpos, ypos, id, on;
} Point;

/*####################################################################*/

int getbtns();

void init();

/*####################################################################*/

int mod_loop(int, int);

int kill(Point *point);

uint8_t spi_send_recv(uint8_t);

void display_update();

void clear_disp();

void set_pixel(int x, int y, int on);

int get_pixel(int x, int y);

/*####################################################################*/

void pointLight(Point *point);

void move_point(Point *point, int ai);

/*####################################################################*/

void move(Point *thing);

void descend(Point** world, Point** idiots);

void fire(Point *boi);

void init_ship(Point *ship, int x_origin, int y_origin);

void init_barriers(Point *barrier_1, Point *barrier_2, int x_origin);

void init_alien(Point* alien, int x_origin, int y_origin);

void rare_spawn(Point *ship);

/*####################################################################*/

#endif
