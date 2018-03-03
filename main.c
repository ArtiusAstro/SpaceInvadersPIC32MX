/* main.c

   This file written 2018-02-06 by Ayub Atif
   */

#include <pic32mx.h>
#include <stdint.h>
#include <math.h>
#include "switch.h"

volatile char* lights = (volatile char*) 0xbf886110; /*PORTE*/
char textbuffer[4][16];

static const uint8_t const font[] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 94, 0, 0, 0, 0,
	0, 0, 4, 3, 4, 3, 0, 0,
	0, 36, 126, 36, 36, 126, 36, 0,
	0, 36, 74, 255, 82, 36, 0, 0,
	0, 70, 38, 16, 8, 100, 98, 0,
	0, 52, 74, 74, 52, 32, 80, 0,
	0, 0, 0, 4, 3, 0, 0, 0,
	0, 0, 0, 126, 129, 0, 0, 0,
	0, 0, 0, 129, 126, 0, 0, 0,
	0, 42, 28, 62, 28, 42, 0, 0,
	0, 8, 8, 62, 8, 8, 0, 0,
	0, 0, 0, 128, 96, 0, 0, 0,
	0, 8, 8, 8, 8, 8, 0, 0,
	0, 0, 0, 0, 96, 0, 0, 0,
	0, 64, 32, 16, 8, 4, 2, 0,
	0, 62, 65, 73, 65, 62, 0, 0,
	0, 0, 66, 127, 64, 0, 0, 0,
	0, 0, 98, 81, 73, 70, 0, 0,
	0, 0, 34, 73, 73, 54, 0, 0,
	0, 0, 14, 8, 127, 8, 0, 0,
	0, 0, 35, 69, 69, 57, 0, 0,
	0, 0, 62, 73, 73, 50, 0, 0,
	0, 0, 1, 97, 25, 7, 0, 0,
	0, 0, 54, 73, 73, 54, 0, 0,
	0, 0, 6, 9, 9, 126, 0, 0,
	0, 0, 0, 102, 0, 0, 0, 0,
	0, 0, 128, 102, 0, 0, 0, 0,
	0, 0, 8, 20, 34, 65, 0, 0,
	0, 0, 20, 20, 20, 20, 0, 0,
	0, 0, 65, 34, 20, 8, 0, 0,
	0, 2, 1, 81, 9, 6, 0, 0,
	0, 28, 34, 89, 89, 82, 12, 0,
	0, 0, 126, 9, 9, 126, 0, 0,
	0, 0, 127, 73, 73, 54, 0, 0,
	0, 0, 62, 65, 65, 34, 0, 0,
	0, 0, 127, 65, 65, 62, 0, 0,
	0, 0, 127, 73, 73, 65, 0, 0,
	0, 0, 127, 9, 9, 1, 0, 0,
	0, 0, 62, 65, 81, 50, 0, 0,
	0, 0, 127, 8, 8, 127, 0, 0,
	0, 0, 65, 127, 65, 0, 0, 0,
	0, 0, 32, 64, 64, 63, 0, 0,
	0, 0, 127, 8, 20, 99, 0, 0,
	0, 0, 127, 64, 64, 64, 0, 0,
	0, 127, 2, 4, 2, 127, 0, 0,
	0, 127, 6, 8, 48, 127, 0, 0,
	0, 0, 62, 65, 65, 62, 0, 0,
	0, 0, 127, 9, 9, 6, 0, 0,
	0, 0, 62, 65, 97, 126, 64, 0,
	0, 0, 127, 9, 9, 118, 0, 0,
	0, 0, 38, 73, 73, 50, 0, 0,
	0, 1, 1, 127, 1, 1, 0, 0,
	0, 0, 63, 64, 64, 63, 0, 0,
	0, 31, 32, 64, 32, 31, 0, 0,
	0, 63, 64, 48, 64, 63, 0, 0,
	0, 0, 119, 8, 8, 119, 0, 0,
	0, 3, 4, 120, 4, 3, 0, 0,
	0, 0, 113, 73, 73, 71, 0, 0,
	0, 0, 127, 65, 65, 0, 0, 0,
	0, 2, 4, 8, 16, 32, 64, 0,
	0, 0, 0, 65, 65, 127, 0, 0,
	0, 4, 2, 1, 2, 4, 0, 0,
	0, 64, 64, 64, 64, 64, 64, 0,
	0, 0, 1, 2, 4, 0, 0, 0,
	0, 0, 48, 72, 40, 120, 0, 0,
	0, 0, 127, 72, 72, 48, 0, 0,
	0, 0, 48, 72, 72, 0, 0, 0,
	0, 0, 48, 72, 72, 127, 0, 0,
	0, 0, 48, 88, 88, 16, 0, 0,
	0, 0, 126, 9, 1, 2, 0, 0,
	0, 0, 80, 152, 152, 112, 0, 0,
	0, 0, 127, 8, 8, 112, 0, 0,
	0, 0, 0, 122, 0, 0, 0, 0,
	0, 0, 64, 128, 128, 122, 0, 0,
	0, 0, 127, 16, 40, 72, 0, 0,
	0, 0, 0, 127, 0, 0, 0, 0,
	0, 120, 8, 16, 8, 112, 0, 0,
	0, 0, 120, 8, 8, 112, 0, 0,
	0, 0, 48, 72, 72, 48, 0, 0,
	0, 0, 248, 40, 40, 16, 0, 0,
	0, 0, 16, 40, 40, 248, 0, 0,
	0, 0, 112, 8, 8, 16, 0, 0,
	0, 0, 72, 84, 84, 36, 0, 0,
	0, 0, 8, 60, 72, 32, 0, 0,
	0, 0, 56, 64, 32, 120, 0, 0,
	0, 0, 56, 64, 56, 0, 0, 0,
	0, 56, 64, 32, 64, 56, 0, 0,
	0, 0, 72, 48, 48, 72, 0, 0,
	0, 0, 24, 160, 160, 120, 0, 0,
	0, 0, 100, 84, 84, 76, 0, 0,
	0, 0, 8, 28, 34, 65, 0, 0,
	0, 0, 0, 126, 0, 0, 0, 0,
	0, 0, 65, 34, 28, 8, 0, 0,
	0, 0, 4, 2, 4, 2, 0, 0,
	0, 120, 68, 66, 68, 120, 0, 0,
};

void display_string(int line, char *s) {
	int i;
	if(line < 0 || line >= 4)
		return;
	if(!s)
		return;

	for(i = 0; i < 16; i++)
		if(*s) {
			textbuffer[line][i] = *s;
			s++;
		} else
			textbuffer[line][i] = ' ';
}

void delay(int cyc){
	volatile int i;
	for(i=cyc; i>0; i--);
}

void start(){

}

void r_u_ded(){ /*if an alien is shot, all its pixels are ded*/

}

void update(){

}

void update_string(){
	int i, j, k;
	int c;
	for(i = 0; i < 4; i++) {
		DISPLAY_COMMAND_DATA_PORT &= ~DISPLAY_COMMAND_DATA_MASK;
		spi_send_recv(0x22);
		spi_send_recv(i);

		spi_send_recv(0x0);
		spi_send_recv(0x10);

		DISPLAY_COMMAND_DATA_PORT |= DISPLAY_COMMAND_DATA_MASK;

		for(j = 0; j < 16; j++) {
			c = textbuffer[i][j];
			if(c & 0x80)
				continue;

			for(k = 0; k < 8; k++)
				spi_send_recv(font[c*8 + k]);
		}
	}
}
char score_as_char[3];
void num2string(int num){
	char digs[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
	int num2, num3;

	num2 = 0;
	num3 = 0;
	while (num > 99) {
		num = num - 100;
		num3++;
	}

	while (num > 9) {
		num = num - 10;
		num2++;
	}

	score_as_char[0] = digs[num3];
	score_as_char[1] = digs[num2];
	score_as_char[2] = digs[num];
}

int main(void){
	int highscore;
	highscore=0; /*highscore is used in they_got_shot()*/
	int current_score;
	current_score=0;
	for(;;){

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
	Point boss[ALIEN_SIZE];
	Point ship_bullet1;
	Point ship_bullet2;
	Point alien1_bullet;
	Point alien2_bullet;
	Point alien3_bullet;
	Point alien4_bullet;
	Point alien5_bullet;
	Point alien6_bullet;
	Point alien7_bullet;
	Point alien8_bullet;
	Point alien9_bullet;

	/*collection*/
	Point* world[7] = {shipy, barrier_1, barrier_2, rare_alien, alien_1, alien_2, alien_3};
	Point* idiots[6] = {alien_4, alien_5, alien_6, alien_7, alien_8, alien_9};
	Point *bad_bullets[9] = {&alien1_bullet, &alien2_bullet, &alien3_bullet, &alien4_bullet,
								&alien5_bullet, &alien6_bullet, &alien7_bullet,
									&alien8_bullet, &alien9_bullet};

	init();
	clear_disp();

	int game;
	int inverted;
	int diff;

	int i,j,len,ded,c0,c1,c2,c3,cLED,cRARE,cDOWN, c1shot, c2shot, c3shot, c4shot, c5shot,
	 			downtime, bullet_count, lives, first_shot_delay;
	c0=c1=c2=c3=cLED=cRARE=cDOWN=bullet_count=c1shot=c2shot=c3shot=0;

	downtime=0; /*checks how many times the wave descended*/
	lives=10; /*game over at 0 lives*/
	inverted=1; /*invert when rare shot down, if >0 then invert display*/
	diff=1;
	first_shot_delay=1;
	int win, shot; //win is for endgame win, and shot is for firing endgame shot

	*lights=0x00;

	if(current_score>highscore)
			highscore=current_score;

	int title;
	int end;
	end=0;
	char score[12];
	title=1;
	game = 1;
	while(title){
		if(getsw()==0x3){
			game=0;
			end=1;
			title=0;
		}
		if(getbtns()==DOWN)
			title=0;
		num2string(highscore);
		score[0] = 'H';
		score[1] = '-';
		score[2] = 'S';
		score[3] = 'c';
		score[4] = 'o';
		score[5] = 'r';
		score[6] = 'e';
		score[7] = ':';
		score[8] = ' ';
		for(i=0;i<3;i++){
			score[9+i] = score_as_char[i];
		}
		display_string(0,"Nin Switch 2.0"); //title
		display_string(1, score); //Highscore is: score
		display_string(2,"SW1 ON 4 ez mode"); //diff is controlled with SW3
		display_string(3,"btn4 to START"); //press btn4 to start

		update_string();
	}

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
	rare_spawn(rare_alien);

	init();
	clear_disp();
	while(game){

		while(getsw()&0x8){
			if(getsw()&0x4)
				*lights = current_score;
			else
				*lights = lives;
			if(!(getsw()&0x8))
				break;
			}

		if(lives==0){
			delay(6000000);
			game=0;
		}

		if(getsw()&0x4)
			*lights = current_score;
		else
			*lights = lives;

		if(getbtns() == DOWN){
			if(bullet_count==0){
				ship_fire(&ship_bullet1, shipy);
				bullet_count=1;
			}
		}

		if(!ship_bullet1.on)
			bullet_count=0;

		if(cLED++>35){
			if(cRARE++>7){
				rare_spawn(rare_alien); //rare_alien grants power up on boom

				if(cDOWN++>0){
					if(downtime<MAX_DOWN+1)
						descend(world, idiots); //DANGER
					downtime++;
					if(downtime==MAX_DOWN+1)
						game=0; /*GAME OVER*/
					cDOWN=0;
				}
				cRARE=0;
			}
			cLED=0;
		}

		move(shipy);
		move_point(&ship_bullet1, 1);

		move_point(&alien1_bullet, 8);
		move_point(&alien2_bullet, 8);
		move_point(&alien3_bullet, 8);
		move_point(&alien4_bullet, 8);
		move_point(&alien5_bullet, 8);
		move_point(&alien6_bullet, 8);
		move_point(&alien7_bullet, 8);
		move_point(&alien8_bullet, 8);
		move_point(&alien9_bullet, 8);


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

	if(!(getsw()&0x1)){
		if(c1shot++>80){
			alien_fire(&alien1_bullet, alien_1);
			alien_fire(&alien4_bullet, alien_4);
			c1shot=0;
		}
		if(c2shot++>200){
			alien_fire(&alien2_bullet, alien_2);
			alien_fire(&alien6_bullet, alien_6);
			c2shot=0;
		}
	}
		if(c3shot++>260){
			alien_fire(&alien3_bullet, alien_3);
			alien_fire(&alien7_bullet, alien_7);
			c3shot=0;
		}
		if(c4shot++>300){
			alien_fire(&alien5_bullet, alien_5);
			alien_fire(&alien8_bullet, alien_8);
			c4shot=0;
		}
		if(c5shot++>400){
			alien_fire(&alien9_bullet, alien_9);
			c5shot=0;
		}

		/*#############################*/

		if(ship_bullet1.xpos==115 && rare_alien[0].on){
			for(i=0;i<RARE_SIZE;i++){
				if(rare_alien[i].ypos == ship_bullet1.ypos){
					inverted = inverted * -1;
					break;
				}
			}
		}

		they_got_shot(&ship_bullet1, world, idiots, &current_score);
		you_got_shot(bad_bullets, world, &lives, &inverted);


		/*#############################*/

	clear_disp();

	for(i=3; i<7; i++){
		switch(world[i][0].id){
			case ALIEN_1:
			case ALIEN_2:
			case ALIEN_3:
				len=ALIEN_SIZE;
				break;
			case RARE_ALIEN:
				len=RARE_SIZE;
				break;
			default: ;
		}
		ded=0;
		for(j=0; j<len; j++){
			if(!world[i][j].on)
				ded=1;
		}
		if(ded){
			for(j=0; j<len; j++)
				world[i][j].on=0;
		}
	}

	for(i=0; i<6; i++){
		ded=0;
		for(j=0; j<ALIEN_SIZE; j++){
			if(!idiots[i][j].on)
				ded=1;
		}
		if(ded){
			for(j=0; j<ALIEN_SIZE; j++)
				idiots[i][j].on=0;
		}
	}

	for(i=0; i<7; i++){
		switch(world[i][0].id){
			case SHIP:
				len=SHIP_SIZE;
				break;
			case BARRIER_1:
			case BARRIER_2:
				len=BARRIER_SIZE;
				break;
			case ALIEN_1:
			case ALIEN_2:
			case ALIEN_3:
				len=ALIEN_SIZE;
				break;
			case RARE_ALIEN:
				len=RARE_SIZE;
				break;
			default: ;
		}
		for(j=0; j<len; j++)
				pointLight(world[i][j]);
	}

	for(i=0; i<6; i++){
		for(j=0; j<ALIEN_SIZE; j++)
			pointLight(idiots[i][j]);
	}

	if(ship_bullet1.on)
		pointLight(ship_bullet1);

	for(i=2; i<9; i++)
		pointLight(*bad_bullets[i]);

	if(!alien_1[0].on && !alien_2[0].on && !alien_3[0].on && !alien_4[0].on && !alien_5[0].on &&
				!alien_6[0].on && !alien_7[0].on && !alien_8[0].on && !alien_9[0].on){
				end=1;
				game=0;
				delay(400000);
			}

	if(inverted>0)
		invert();
	else
		display_update();

		delay(10);
	}

	if(end){
		//boss intro
		display_string(0,"The Nin Switch's"); //title
		display_string(1," enemy is here! "); //Highscore is: score
		display_string(2,"----A Lawyer----"); //diff is controlled with SW3
		display_string(3,"Only ONE chance!"); //press btn4 to start

		update_string();
		delay(25000000);

		//start_end
		init();
		clear_disp();

		win=c0=c1=0;
		shot=0; //ship has been fired at 1

		//start_end();
		init_ship(shipy, 5, 16);
		init_alien(boss, 80, 12);
	}

	while(end){

		if(getsw()==6)
			end=0;

		if(!shot)
			if(getbtns() == DOWN)
				shot=1;

		if(shot){
			if(c1++>15){
				for(i=0;i<SHIP_SIZE;i++)
					move_point(&shipy[i], 1);
			}
		}

		move(shipy);

		if(shipy[14].xpos==80){
			for(i=0;i<ALIEN_SIZE;i++){
				if(boss[i].ypos == shipy[10].ypos){
					win=1;
					for(j=0; j<ALIEN_SIZE; j++)
						boss[j].on=0;
					break;
				}
			}
		}
		if(shipy[0].xpos==120)
			end=0;

		if(c0++>1){
			move(boss);
			c0=0;
		}

		//void update_end()
		clear_disp();

		for(i=0; i<SHIP_SIZE; i++)
			pointLight(shipy[i]);

		for(i=0; i<ALIEN_SIZE; i++)
			pointLight(boss[i]);

		display_update();

		delay(10);
	}

	if(win){
		//gameover screen
		display_string(0,"     SUCCESS"); //title
		display_string(1,"----------------"); //Highscore is: score
		display_string(2,"   We defeated  "); //diff is controlled with SW3
		display_string(3," the evil lawyer!"); //press btn4 to start

		update_string();
		delay(20000000);
	}

	else{
		//gameover screen
		display_string(0,"    GAMEOVER"); //title
		display_string(1,"----------------"); //Highscore is: score
		display_string(2,""); //diff is controlled with SW3
		display_string(3,"Neva givvu uppu!"); //press btn4 to start

		update_string();
		delay(22000000);
	}
}
	return 0;
}
