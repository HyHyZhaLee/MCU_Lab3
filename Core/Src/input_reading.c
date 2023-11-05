/*
 * input_reading.c
 *
 *  Created on: Oct 23, 2023
 *      Author: Admin
 */

#include "input_reading.h"
// we aim to work with more than one buttons
#define N0_OF_BUTTONS 	3
// timer interrupt duration is 10ms , so to pass 3 second ,
// we need to jump to the interrupt service routine 300 time
#define DURATION_FOR_LONG_PRESS 	300
#define BUTTON_IS_PRESSED 	GPIO_PIN_RESET
#define BUTTON_IS_RELEASED 	GPIO_PIN_SET
// we define 4 buffers for debouncing
static GPIO_PinState buttonBuffer0[N0_OF_BUTTONS];
static GPIO_PinState buttonBuffer1[N0_OF_BUTTONS];
static GPIO_PinState buttonBuffer2[N0_OF_BUTTONS];
static GPIO_PinState buttonBuffer3[N0_OF_BUTTONS];
// we define a flag for a button pressed and a flag for button long pressed
static uint8_t flagForButtonPress[N0_OF_BUTTONS];
static uint8_t flagForButtonLongPress[N0_OF_BUTTONS];
// we define counter for automatically decreasing.
static uint16_t counterForButtonLongPress[N0_OF_BUTTONS];

void initButton(){
    for (int i = 0; i < N0_OF_BUTTONS; i++) {
        buttonBuffer0[i] = BUTTON_IS_RELEASED;
        buttonBuffer1[i] = BUTTON_IS_RELEASED;
        buttonBuffer2[i] = BUTTON_IS_RELEASED;
        buttonBuffer3[i] = BUTTON_IS_RELEASED;

        flagForButtonLongPress[i] = 0;
        flagForButtonPress[i] = 0;
        counterForButtonLongPress[i] = DURATION_FOR_LONG_PRESS;
    }
}

void button_reading(void) {
    for (int i = 0; i < N0_OF_BUTTONS; i++) {
        buttonBuffer2[i] = buttonBuffer1[i];
        buttonBuffer1[i] = buttonBuffer0[i];
        switch (i) {
            case 0:
                buttonBuffer0[i] = HAL_GPIO_ReadPin(BUTTON_0_GPIO_Port, BUTTON_0_Pin);
                break;
            case 1:
                buttonBuffer0[i] = HAL_GPIO_ReadPin(BUTTON_1_GPIO_Port, BUTTON_1_Pin);
                break;
            case 2:
                buttonBuffer0[i] = HAL_GPIO_ReadPin(BUTTON_2_GPIO_Port, BUTTON_2_Pin);
                break;
        }
        if ((buttonBuffer1[i] == buttonBuffer0[i]) && (buttonBuffer1[i] == buttonBuffer2[i])) {
            if (buttonBuffer2[i] != buttonBuffer3[i]) {
                buttonBuffer3[i] = buttonBuffer2[i];
                if (buttonBuffer3[i] == BUTTON_IS_PRESSED) {
                    counterForButtonLongPress[i] = DURATION_FOR_LONG_PRESS;
                    flagForButtonPress[i] = 1;
                }
            } else {
                counterForButtonLongPress[i]--;
                if (counterForButtonLongPress[i] == 0) {
                    counterForButtonLongPress[i] = DURATION_FOR_LONG_PRESS;
                    flagForButtonLongPress[i] = 1;
                }
            }
        }
    }
}

//Checking a button is pressed or not
unsigned char is_button_pressed ( uint8_t index ){
    if( index >= N0_OF_BUTTONS ) return 0;
    if(flagForButtonPress[index] == 1){
    	flagForButtonPress[index] = 0;
    	return 1;
    }
    return 0;
}
//Checking a button is long pressed
unsigned char is_button_long_pressed( unsigned char index ){
    if( index >= N0_OF_BUTTONS ) return 0;
    if(flagForButtonLongPress[index] == 1){
    	flagForButtonLongPress[index] = 0;
    	return 1;
    }
    return 0;
}
