/*
 * global.h
 *
 *  Created on: Oct 23, 2023
 *      Author: Admin
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include "display.h"
#include "software_timer.h"
#include "main.h"
#include "input_reading.h"
#include "fsm_automatic.h"

#define INIT	0
#define RED 1
#define YELLOW 2
#define GREEN 3

#define MODE_AUTO 10
#define MODE_RED 11
#define MODE_YELLOW 12
#define MODE_GREEN 13

#define DURATION_RED  7
#define DURATION_YELLOW  2
#define DURATION_GREEN  4

#define TIMER_LED_BLINKY 250
#define TIMER_7_SEGMENT 250




#endif /* INC_GLOBAL_H_ */
