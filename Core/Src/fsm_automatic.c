/*
 * fsm_automatic.c
 *
 *  Created on: Nov 6, 2023
 *      Author: Admin
 */

#include "fsm_automatic.h"
int STATUS1 = INIT;
int STATUS2 = INIT;
int TRAFFIC_MODE = MODE_AUTO;


int duration_RED = DURATION_RED;
int duration_YELLOW = DURATION_YELLOW;
int duration_GREEN = DURATION_GREEN;

int LED_RED_temp = DURATION_RED;
int duration_YELLOW_temp = DURATION_YELLOW;
int duration_GREEN_temp = DURATION_GREEN;

int counter1, counter2;

void fsm_reset(){
	counter1 = 0;
	counter2 = 0;
	STATUS1 = INIT;
	STATUS2 = INIT;
	display_resetALL();
	LED_RED_temp = duration_RED;
	duration_YELLOW_temp = duration_YELLOW;
	duration_GREEN_temp = duration_GREEN;
}
void fsm_automatic(){
	led_buffer[1] = counter1%10;
	led_buffer[0] = (counter1-led_buffer[1])/10;
	led_buffer[3] = counter2%10;
	led_buffer[2] = (counter2-led_buffer[3])/10;

	switch(STATUS1){
		case INIT:
			STATUS1 = RED;
			counter1 = duration_RED;
			break;
		case RED:
			if(counter1<0){
				STATUS1 = GREEN;
				counter1 = duration_GREEN;
			}
			display_traffic1(RED);
			break;
		case GREEN:
			if(counter1<0){
				STATUS1 = YELLOW;
				counter1 = duration_YELLOW;
			}
			display_traffic1(GREEN);
			break;
		case YELLOW:
			if(counter1<0){
				STATUS1 = RED;
				counter1 = duration_RED;
			}
			display_traffic1(YELLOW);
			break;
	}

	switch(STATUS2){
		case INIT:
			STATUS2 = GREEN;
			counter2 = duration_GREEN;
			break;
		case RED:
			if(counter2<0){
				STATUS2 = GREEN;
				counter2 = duration_GREEN;
			}
			display_traffic2(RED);
			break;
		case GREEN:
			if(counter2<0){
				STATUS2 = YELLOW;
				counter2 = duration_YELLOW;
			}
			display_traffic2(GREEN);
			break;
		case YELLOW:
			if(counter2<0){
				STATUS2 = RED;
				counter2 = duration_RED;
			}
			display_traffic2(YELLOW);
			break;
	}
}
void fsm_run(){
	switch (TRAFFIC_MODE) {
		case MODE_AUTO:
			fsm_automatic();
			break;
		case MODE_RED:
			display_toggleLed(RED, TIMER_LED_BLINKY);
			led_buffer[0] = 0;
			led_buffer[1] = 1;
			led_buffer[3] = LED_RED_temp%10;
			led_buffer[2] = (LED_RED_temp - led_buffer[3])/10;
			break;
		case MODE_YELLOW:
			display_toggleLed(YELLOW, TIMER_LED_BLINKY);
			led_buffer[0] = 0;
			led_buffer[1] = 1;
			led_buffer[3] = duration_YELLOW_temp%10;
			led_buffer[2] = (duration_YELLOW_temp - led_buffer[3])/10;
			break;
		case MODE_GREEN:
			display_toggleLed(GREEN, TIMER_LED_BLINKY);
			led_buffer[0] = 0;
			led_buffer[1] = 1;
			led_buffer[3] = duration_GREEN_temp%10;
			led_buffer[2] = (duration_GREEN_temp - led_buffer[3])/10;
			break;
		default:
			break;
	}

	if(timer_flag[0]){
		setTimer(1000, 0);
		if(counter1>=0) counter1--;
		if(counter2>=0) counter2--;
	}
	if(timer_flag[2]){
		setTimer(TIMER_7_SEGMENT, 2);
		led7Run();
	}

}
void fsm_for_input_processing(void){
	if(is_button_pressed(0)){
		TRAFFIC_MODE++;
		if(TRAFFIC_MODE>MODE_GREEN) TRAFFIC_MODE = MODE_AUTO;
		fsm_reset();
	}
	if(is_button_pressed(1)){
		switch (TRAFFIC_MODE) {
			case MODE_AUTO:
				break;
			case MODE_RED:
				LED_RED_temp++;
				break;
			case MODE_YELLOW:
				duration_YELLOW_temp++;
				break;
			case MODE_GREEN:
				duration_GREEN_temp++;
				break;
			default:
				break;
		}
	}
	if(is_button_pressed(2)){
		duration_RED = LED_RED_temp;
		duration_YELLOW = duration_YELLOW_temp;
		duration_GREEN = duration_GREEN_temp;
		TRAFFIC_MODE++;
		if(TRAFFIC_MODE>MODE_GREEN) TRAFFIC_MODE = MODE_AUTO;
		fsm_reset();
	}
	fsm_run();
}

