/*
 * Button.c
 *
 *  Created on: Oct 6, 2025
 *      Author: Hi
 */


#include "Button.h"

#define NUMBER_OF_BUTTON 3

//Private member variable
ButtonState_t button_state[NUMBER_OF_BUTTON];

/**
 * This will help update button_state
 *	If prev != current -> RELEASE
 *	If prev == current -> PRESSED
 *	If PRESSED >1s -> HOLD
 */
GPIO_PinState previous_state[NUMBER_OF_BUTTON];
GPIO_PinState current_state[NUMBER_OF_BUTTON];

int button_counter_id[NUMBER_OF_BUTTON];

void Button_ReadInput(){
	for(int button = 0; button < NUMBER_OF_BUTTON; ++button){
		previous_state[button] = current_state[button];
		current_state[button] = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0 << button);

		if(previous_state[button] != current_state[button]){
			if(button_state[button] == PRESSED || button_state[button] == HOLD){
				SoftwareTimer_ResetFlag(button_counter_id[button]);
			}
			button_state[button] = RELEASE;
		}

		if(previous_state[button] == current_state[button]){

		}
	}
}

void Button_StateMachine(){

}
