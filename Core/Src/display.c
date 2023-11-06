/*
 * display.c
 *
 *  Created on: Oct 8, 2023
 *      Author: Admin
 */
#include "display.h"
#ifdef CATHODE
uint8_t segmentNumber[10]={
	0x3f,
	0x06,
	0x5b,
	0x4f,
	0x66,
	0x6d,
	0x7d,
	0x07,
	0x7f,
	0x4f
};
#endif

#ifdef	ANODE
uint8_t segmentNumber[10]={
	0xc0,
	0xf9,
	0xa4,
	0xb0,
	0x99,
	0x92,
	0x82,
	0xf8,
	0x80,
	0x90
};
#endif

void display7SEG(int number){
	HAL_GPIO_WritePin(SEG0_GPIO_Port, SEG0_Pin, (segmentNumber[number]>>0)&0x01);
	HAL_GPIO_WritePin(SEG1_GPIO_Port, SEG1_Pin, (segmentNumber[number]>>1)&0x01);
	HAL_GPIO_WritePin(SEG2_GPIO_Port, SEG2_Pin, (segmentNumber[number]>>2)&0x01);
	HAL_GPIO_WritePin(SEG3_GPIO_Port, SEG3_Pin, (segmentNumber[number]>>3)&0x01);
	HAL_GPIO_WritePin(SEG4_GPIO_Port, SEG4_Pin, (segmentNumber[number]>>4)&0x01);
	HAL_GPIO_WritePin(SEG5_GPIO_Port, SEG5_Pin, (segmentNumber[number]>>5)&0x01);
	HAL_GPIO_WritePin(SEG6_GPIO_Port, SEG6_Pin, (segmentNumber[number]>>6)&0x01);
}
int index_led = 0;
int led_buffer[MAX_LED] = {1,2,3,4};
void update7SEG(int index){
	switch(index){
	case 0:
		// Display the first 7 SEG with led_buffer [0]
		HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, ON);
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, OFF);
		HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, OFF);
		HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, OFF);
		display7SEG(led_buffer[0]);
		break;
	case 1:
		// Display the second 7 SEG with led_buffer [1]
		HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, OFF);
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, ON);
		HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, OFF);
		HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, OFF);
		display7SEG(led_buffer[1]);
		break;
	case 2:
		// Display the second 7 SEG with led_buffer [2]
		HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, OFF);
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, OFF);
		HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, ON);
		HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, OFF);
		display7SEG(led_buffer[2]);
		break;
	case 3:
		// Display the second 7 SEG with led_buffer [3]
		HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, OFF);
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, OFF);
		HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, OFF);
		HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, ON);
		display7SEG(led_buffer[3]);
		break;
	default: break;
	}
}

void display_resetALL(){
	HAL_GPIO_WritePin(LED_RED1_GPIO_Port, LED_RED1_Pin, OFF);
	HAL_GPIO_WritePin(LED_YELLOW1_GPIO_Port, LED_YELLOW1_Pin, OFF);
	HAL_GPIO_WritePin(LED_GREEN1_GPIO_Port, LED_GREEN1_Pin, OFF);

	HAL_GPIO_WritePin(LED_RED2_GPIO_Port, LED_RED2_Pin, OFF);
	HAL_GPIO_WritePin(LED_YELLOW2_GPIO_Port, LED_YELLOW2_Pin, OFF);
	HAL_GPIO_WritePin(LED_GREEN2_GPIO_Port, LED_GREEN2_Pin, OFF);

	index_led = 0;
	for(int i = 0; i<MAX_LED; i++) led_buffer[i] = 0;
}


void display_traffic1(int input){
	switch(input){
		case RED:
			HAL_GPIO_WritePin(LED_RED1_GPIO_Port, LED_RED1_Pin, ON);
			HAL_GPIO_WritePin(LED_YELLOW1_GPIO_Port, LED_YELLOW1_Pin, OFF);
			HAL_GPIO_WritePin(LED_GREEN1_GPIO_Port, LED_GREEN1_Pin, OFF);
			break;
		case YELLOW:
			HAL_GPIO_WritePin(LED_RED1_GPIO_Port, LED_RED1_Pin, OFF);
			HAL_GPIO_WritePin(LED_YELLOW1_GPIO_Port, LED_YELLOW1_Pin, ON);
			HAL_GPIO_WritePin(LED_GREEN1_GPIO_Port, LED_GREEN1_Pin, OFF);
			break;
		case GREEN:
			HAL_GPIO_WritePin(LED_RED1_GPIO_Port, LED_RED1_Pin, OFF);
			HAL_GPIO_WritePin(LED_YELLOW1_GPIO_Port, LED_YELLOW1_Pin, OFF);
			HAL_GPIO_WritePin(LED_GREEN1_GPIO_Port, LED_GREEN1_Pin, ON);
			break;
		default:
			break;
	}
}
void display_traffic2(int input){
	switch(input){
		case RED:
			HAL_GPIO_WritePin(LED_RED2_GPIO_Port, LED_RED2_Pin, ON);
			HAL_GPIO_WritePin(LED_YELLOW2_GPIO_Port, LED_YELLOW2_Pin, OFF);
			HAL_GPIO_WritePin(LED_GREEN2_GPIO_Port, LED_GREEN2_Pin, OFF);
			break;
		case YELLOW:
			HAL_GPIO_WritePin(LED_RED2_GPIO_Port, LED_RED2_Pin, OFF);
			HAL_GPIO_WritePin(LED_YELLOW2_GPIO_Port, LED_YELLOW2_Pin, ON);
			HAL_GPIO_WritePin(LED_GREEN2_GPIO_Port, LED_GREEN2_Pin, OFF);
			break;
		case GREEN:
			HAL_GPIO_WritePin(LED_RED2_GPIO_Port, LED_RED2_Pin, OFF);
			HAL_GPIO_WritePin(LED_YELLOW2_GPIO_Port, LED_YELLOW2_Pin, OFF);
			HAL_GPIO_WritePin(LED_GREEN2_GPIO_Port, LED_GREEN2_Pin, ON);
			break;
		default:
			break;
	}
}

void display_toggleLed(int input, int duration){
	if(timer_flag[1]){
		setTimer(duration, 1);
		switch(input){
			case RED:
				HAL_GPIO_TogglePin(LED_RED1_GPIO_Port, LED_RED1_Pin);
				HAL_GPIO_TogglePin(LED_RED2_GPIO_Port, LED_RED2_Pin);
				break;
			case YELLOW:
				HAL_GPIO_TogglePin(LED_YELLOW1_GPIO_Port, LED_YELLOW1_Pin);
				HAL_GPIO_TogglePin(LED_YELLOW2_GPIO_Port, LED_YELLOW2_Pin);
				break;
			case GREEN:
				HAL_GPIO_TogglePin(LED_GREEN1_GPIO_Port, LED_GREEN1_Pin);
				HAL_GPIO_TogglePin(LED_GREEN2_GPIO_Port, LED_GREEN2_Pin);
				break;
		}
	}
}

void led7Run(){
	update7SEG(index_led++);
	if(index_led >= MAX_LED) index_led = 0;
}
