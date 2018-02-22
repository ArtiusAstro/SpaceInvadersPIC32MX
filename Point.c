/* point.c
   
   This file written 2018-02-14 by Ayub Atif 
   */

#include "switch.h"
#include <pic32mx.h>
#include <stdint.h>

void spooky() {
        int i;
        for (i = 0; i < 32; i++) {
                set_pixel(127, i, 1);
        }
        display_update();
}

int mod_loop(int n, int N) {
	int r = n % N;
	return (r < 0) ? (r + N) : r;
}

int kill(Point point){
	return (point.ypos<0 || point.ypos>31 || point.xpos<0 || point.xpos>127) ? 1 : 0;
}

void pointLight(Point point){
	set_pixel(point.xpos, point.ypos, point.on);
}

void move_point(Point *point, int ai) {
	if(point->on){
		
		int btns = getbtns();

		if(ai)
			btns = ai; /*if automated, go somewhere*/

		/*UP to DOWN is defined in header*/
		switch (btns) {
			case UP: if(point->id==SHIP_BULLET) 
						point->xpos++; 
					 break;
			case LEFT: (point->ypos--); break;
			case RIGHT: (point->ypos++); break;
			case DOWN: if(point->id==ALIEN_BULLET) 
						point->xpos--; 
					 break;
			default:	;
		}
		
		if(kill(*point)){
			switch (point->id){
				case ALIEN_BULLET:
				case SHIP_BULLET:
					point->on=0;
					point->xpos=mod_loop(point->xpos, 128); 
					break;
				case RARE_ALIEN: //point->on=0;
				default:
					//point->xpos=mod_loop(point->xpos, 128); not needed rn, probs 4 bullet
					point->ypos=mod_loop(point->ypos, 32);
				}
		}
		
	}
}

void they_got_shot(Point ship_bullet1, Point ship_bullet2, Point** ship_barriers_rare_aliens1_3, Point **aliens4_9)
{
	int i, j, len, boom1, boom2;
	boom1=boom2=0;
	for(i=1;i<7;i++){ //skip the ship
		if(boom1 && boom2)
			break;
		switch (ship_barriers_rare_aliens1_3[i][0].id){
			case BARRIER_1:
			case BARRIER_2:
				len=BARRIER_SIZE;
				break;
			case ALIEN_1:
			case ALIEN_2:
			case ALIEN_3:
			case ALIEN_4:
			case ALIEN_5:
			case ALIEN_6:
			case ALIEN_7:
			case ALIEN_8:
			case ALIEN_9:
				len=ALIEN_SIZE;
				break;
			case RARE_ALIEN:
				len=RARE_SIZE;
				break;
			default: ;
		}
		for(j=0;j<len;j++){
			if(boom1)
				break;
			if(ship_barriers_rare_aliens1_3[i][j].on){
				if(ship_barriers_rare_aliens1_3[i][j].xpos==ship_bullet1.xpos && ship_barriers_rare_aliens1_3[i][j].ypos==ship_bullet1.ypos){
					ship_bullet1.on=0;
					ship_barriers_rare_aliens1_3[i][j].on=0;
					boom1=1;
				}
			}
		}
		for(j=0;j<len;j++){
			if(boom2)
				break;
			if(ship_barriers_rare_aliens1_3[i][j].on){
				if(ship_barriers_rare_aliens1_3[i][j].xpos==ship_bullet2.xpos && ship_barriers_rare_aliens1_3[i][j].ypos==ship_bullet2.ypos){
					ship_bullet2.on=0;
					ship_barriers_rare_aliens1_3[i][j].on=0;
					boom2=1;
				}
			}
		}
	}	
		
	for(i=0;i<ALIEN_SIZE;i++){
		if(boom1 && boom2)
			break;
		for(j=0;j<len;j++){
			if(boom1)
				break;
			if(aliens4_9[i][j].on){
				if(aliens4_9[i][j].xpos==ship_bullet1.xpos && aliens4_9[i][j].ypos==ship_bullet1.ypos){
					ship_bullet1.on=0;
					aliens4_9[i][j].on=0;
					boom1=1;
				}
			}
		}
		for(j=0;j<len;j++){
			if(boom2)
				break;
			if(aliens4_9[i][j].on){
				if(aliens4_9[i][j].xpos==ship_bullet2.xpos && aliens4_9[i][j].ypos==ship_bullet2.ypos){
					ship_bullet2.on=0;
					aliens4_9[i][j].on=0;
					boom2=1;
				}
			}
		}	
	}
}
void you_got_shot(Point *shipbul12_alienbul1_3, Point *alienbul4_9, Point **ship_barrier12, int *lives)
{
	int i, j, k, len;
	for(i=0;i<3;i++){
		if(ship_barrier12[i][0].id==SHIP)
			len=SHIP_SIZE;
		else
			len=BARRIER_SIZE;
		for(j=0;j<len;j++){
			for(k=2;k<5;k++){
				if(ship_barrier12[i][j].on){
					if(ship_barrier12[i][j].xpos==shipbul12_alienbul1_3[k].xpos && ship_barrier12[i][j].ypos==shipbul12_alienbul1_3[k].ypos){
						shipbul12_alienbul1_3[k].on=0;
						if(ship_barrier12[i][0].id==SHIP)
							*lives--;
						else
							ship_barrier12[i][j].on=0;
						break;
					}
				}
			}
			for(k=0;k<6;k++){
				if(ship_barrier12[i][j].on){
					if(ship_barrier12[i][j].xpos==alienbul4_9[k].xpos && ship_barrier12[i][j].ypos==alienbul4_9[k].ypos){
						alienbul4_9[k].on=0;
						if(ship_barrier12[i][0].id==SHIP)
							*lives--;
						else
							ship_barrier12[i][j].on=0;
						break;
					}
				}
			}
		}

}
		
		
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
}



