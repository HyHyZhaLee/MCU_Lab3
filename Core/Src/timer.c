/*
 * timer.c
 *
 *  Created on: Oct 23, 2023
 *      Author: Admin
 */

# include "global.h"

void HAL_TIM_PeriodElapsedCallback ( TIM_HandleTypeDef * htim )
{
	if ( htim -> Instance == TIM2 ) {
		button_reading() ;
		timerRun();
	}

}


