/*
 * display.h
 *
 *  Created on: Oct 8, 2023
 *      Author: Admin
 */

#ifndef INC_DISPLAY_H_
#define INC_DISPLAY_H_
#define ANODE

#include "global.h"
#define ON	0
#define OFF	1
#define MAX_LED	4


void display_traffic1(int input);
void display_traffic2(int input);
void display_resetALL();
void display_toggleLed(int input, int duration);


extern int led_buffer[MAX_LED];
void led7Run();



#endif /* INC_DISPLAY_H_ */
