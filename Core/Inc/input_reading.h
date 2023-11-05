/*
 * input_reading.h
 *
 *  Created on: Oct 23, 2023
 *      Author: Admin
 */

#ifndef INC_INPUT_READING_H_
#define INC_INPUT_READING_H_

#include "global.h"
void initButton();
void button_reading ( void ) ;
unsigned char is_button_pressed ( unsigned char index ) ;
unsigned char is_button_long_pressed( unsigned char index ) ;
#endif /* INC_INPUT_READING_H_ */
