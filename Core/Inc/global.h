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
#define RED_GREEN 1
#define RED_YELLOW 2
#define GREEN_RED 3
#define YELLOW_RED 4

#define MOD_RED 10
#define MOD_YELLOW 11
#define MOD_GREEN 12

#define DURATION_RED  7
#define DURATION_YELLOW  2
#define DURATION_GREEN  4

#define TIMER_LED_BLINKY 250
#define TIMER_7_SEGMENT 250




#endif /* INC_GLOBAL_H_ */
