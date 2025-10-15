/*
 * Button.c
 *
 *  Created on: Oct 6, 2025
 *      Author: Hi
 */


#include "Button.h"

#define BUTTON_PIN_STATE_PRESSED GPIO_PIN_RESET
#define BUTTON_PIN_STATE_RELEASE GPIO_PIN_SET

#define NUMBER_OF_BUTTON 3
#define KEY_PRESS_TIME (int)1000

//Private member variable
ButtonState_t interface_button_state[NUMBER_OF_BUTTON];
GPIO_PinState button_state[NUMBER_OF_BUTTON];

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

		//Button state is difference
		if(previous_state[button] == current_state[button]){
			//Switch state
			if(current_state[button] != button_state[button]){
				button_state[button] = current_state[button];
				//Switch to pressed state
				if(button_state[button] == BUTTON_PIN_STATE_PRESSED){
					//Start counting for hold state;
					SoftwareTimer_ResetFlag(button_counter_id[button]);
					interface_button_state[button] = PRESSED;
				}
			}
			//State is the same
			else{
				//Timer is up and the button_state is pressed
				if(current_state[button] == BUTTON_PIN_STATE_PRESSED &&	SoftwareTimer_GetFlag(button_counter_id[button]) == FLAG_ON){
					SoftwareTimer_ResetFlag(button_counter_id[button]);
					interface_button_state[button] = HOLD;
				}
			}
		}
	}
}

void Button_TimerInit(){
	for(int button = 0; button < NUMBER_OF_BUTTON; ++button){
		button_counter_id[button] = SoftwareTimer_AddNewTimer(KEY_PRESS_TIME);
	}
}

ButtonState_t Button_GetButtonState(uint8_t index){
	if(index < NUMBER_OF_BUTTON && index >= 0){
		ButtonState_t state = interface_button_state[index];
		if(state != RELEASE){
			interface_button_state[index] = RELEASE;
		}
		return state;
	}
	else{
		return ERROR_STATE;
	}

}

