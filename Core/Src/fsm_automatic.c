/*
 * fsm_automatic.c
 *
 *  Created on: Nov 6, 2023
 *      Author: Admin
 */

#include "fsm_automatic.h"
int STATUS = INIT;

int duration_RED = DURATION_RED;
int duration_YELLOW = DURATION_YELLOW;
int duration_GREEN = DURATION_GREEN;

int duration_RED_temp = DURATION_RED;
int duration_YELLOW_temp = DURATION_YELLOW;
int duration_GREEN_temp = DURATION_GREEN;

int counter1, counter2;

void fsm_for_input_processing(void){
	switch (STATUS) {
		//Case INIT
		case INIT:
			initTimer(1000);
			setTimer(2000, 0);
			initButton();
			STATUS = RED_GREEN;
			counter1 = duration_RED;
			counter2 = duration_GREEN;
			led_buffer[1] = counter1%10;
			led_buffer[0] = (counter1-led_buffer[1])/10;
			led_buffer[3] = counter2%10;
			led_buffer[2] = (counter2-led_buffer[3])/10;
			break;

		//CASE RED_GREEN
		case RED_GREEN:
			display_traffic1(RED);
			display_traffic2(GREEN);
			//Timer condition
			if(counter2<0) {
				STATUS = RED_YELLOW;
				counter2 = duration_YELLOW;
			}
			//Button condition
			if(is_button_pressed(0)){
				STATUS = MOD_RED;
				resetALL();
			}
			break;
		case RED_YELLOW:
			display_traffic1(RED);
			display_traffic2(YELLOW);
			//Timer condition
			if(counter2<0) {
				STATUS = GREEN_RED;
				counter1 = duration_GREEN;
				counter2 = duration_RED;
			}
			//Button condition
			if(is_button_pressed(0)){
				STATUS = MOD_RED;
				resetALL();
			}
			break;
		case GREEN_RED:
			display_traffic1(GREEN);
			display_traffic2(RED);
			//Timer condition
			if(counter1<0) {
				STATUS = YELLOW_RED;
				counter1 = duration_YELLOW;
			}
			//Button condition
			if(is_button_pressed(0)){
				STATUS = MOD_RED;
				resetALL();
			}
			break;
		case YELLOW_RED:
			display_traffic1(YELLOW);
			display_traffic2(RED);
			//Timer condition
			if(counter1<0) {
				STATUS = RED_GREEN;
				counter1 = duration_RED;
				counter2 = duration_GREEN;
			}
			//Button condition
			if(is_button_pressed(0)){
				STATUS = MOD_RED;
				resetALL();
			}
			break;
		case MOD_RED:
			toggleLed(RED, TIMER_LED_BLINKY);
			if(is_button_pressed(0)){
				STATUS = MOD_YELLOW;
				duration_RED_temp = duration_RED;
				resetALL();
			}
			if(is_button_pressed(1)){
				duration_RED_temp++;
			}
			if(is_button_pressed(2)){
				STATUS = MOD_YELLOW;
				duration_RED = duration_RED_temp;
				resetALL();
			}
			led_buffer[1] = 1;
			led_buffer[3] = duration_RED_temp%10;
			led_buffer[2] = (duration_RED_temp-led_buffer[3])/10;
			break;
		case MOD_YELLOW:
			toggleLed(YELLOW, TIMER_LED_BLINKY);
			if(is_button_pressed(0)){
				STATUS = MOD_GREEN;
				duration_YELLOW_temp = duration_YELLOW;
				resetALL();
			}
			if(is_button_pressed(1)){
				duration_YELLOW_temp++;
			}
			if(is_button_pressed(2)){
				STATUS = MOD_GREEN;
				duration_YELLOW = duration_YELLOW_temp;
				resetALL();
			}
			led_buffer[1] = 1;
			led_buffer[3] = duration_YELLOW_temp%10;
			led_buffer[2] = (duration_YELLOW_temp-led_buffer[3])/10;
			break;
		case MOD_GREEN:
			toggleLed(GREEN, TIMER_LED_BLINKY);
			if(is_button_pressed(0)){
				STATUS = RED_GREEN;
				counter1 = duration_RED;
				counter2 = duration_GREEN;
				resetALL();
			}

			if(is_button_pressed(1)){
				duration_GREEN_temp++;
			}
			if(is_button_pressed(2)){
				STATUS = RED_GREEN;
				duration_GREEN = duration_GREEN_temp;
				counter1 = duration_RED;
				counter2 = duration_GREEN;
				resetALL();
			}
			led_buffer[1] = 1;
			led_buffer[3] = duration_GREEN_temp%10;
			led_buffer[2] = (duration_GREEN_temp-led_buffer[3])/10;
			break;
		default:
			break;
	}
	//Run the automatic 7 segment led
	if(STATUS == RED_GREEN || STATUS == RED_YELLOW || STATUS == GREEN_RED || STATUS == YELLOW_RED){
		led_buffer[1] = counter1%10;
		led_buffer[0] = (counter1-led_buffer[1])/10;
		led_buffer[3] = counter2%10;
		led_buffer[2] = (counter2-led_buffer[3])/10;
	}
	//Run the timer 1s for counter of each road
	if(timer_flag[0]){
		setTimer(1000, 0);
		if(counter1>=0) counter1--;
		if(counter2>=0) counter2--;
		HAL_GPIO_TogglePin(TOGGLE_LED_GPIO_Port, TOGGLE_LED_Pin);
	}
	//Run the led blinky in manual mod
	if(timer_flag[2]){
		setTimer(TIMER_LED_BLINKY,2);
		led7Run();
	}

}
