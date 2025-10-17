/*
 * Software_Timer.h
 *
 *  Created on: Sep 25, 2025
 *      Author: Hi
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

#include <stdint.h>
#include <stdlib.h>

#include "main.h"
#include "Linked_List.h"

/*Public Member Function*/
void SoftwareTimer_Init();
int SoftwareTimer_AddNewTimer(int time_amount);		//return the id of the timer
void SoftwareTimer_SetNewTimer(int id, int time_amount);
const int SoftwareTimer_GetFlag(int id);
void SoftwareTimer_ResetFlag(int id);
void SoftwareTimer_Step();

#endif /* INC_SOFTWARE_TIMER_H_ */
