/*
 * Button.h
 *
 *  Created on: Oct 6, 2025
 *      Author: Hi
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "main.h"
#include "Software_Timer.h"

#include <stdint.h>

typedef enum ButtonState{
	RELEASE = 0,
	PRESSED,
	HOLD
} ButtonState_t;

void Button_Init();
void Button_ReadInput();

ButtonState_t Button_GetButtonState(uint8_t index);


#endif /* INC_BUTTON_H_ */
