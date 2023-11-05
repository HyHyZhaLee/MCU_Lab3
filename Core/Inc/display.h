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

#define RED 0
#define YELLOW 1
#define GREEN 2


void display_traffic1(int input);
void display_traffic2(int input);
void toggleLed(int input, int duration);
void resetALL();

extern int led_buffer[MAX_LED];
void led7Run();



#endif /* INC_DISPLAY_H_ */
