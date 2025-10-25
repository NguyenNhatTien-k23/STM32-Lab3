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
#define KEY_PRESS_TIME (int)500

//Private member variable
ButtonState_t interface_button_state[NUMBER_OF_BUTTON];
GPIO_PinState button_state[NUMBER_OF_BUTTON];

int pressed_flag[NUMBER_OF_BUTTON] = {0, 0, 0};
int hold_flag[NUMBER_OF_BUTTON] = {0, 0, 0};

int IsPressed(int index);
int IsHeld(int index);

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

		//Button state is the same -> Acctual Input
		if(previous_state[button] == current_state[button]){
			//If switch state happen
			if(current_state[button] != button_state[button]){
				button_state[button] = current_state[button];
				//Switch to pressed state
				if(button_state[button] == BUTTON_PIN_STATE_PRESSED){
					//Start counting for hold state;
					if(SoftwareTimer_GetFlag(button_counter_id[button]) == FLAG_ON){
						SoftwareTimer_ResetFlag(button_counter_id[button]);
					}
					pressed_flag[button] = 1;
				}
			}
			//State is the same
			else{
				//Timer is up and the button_state is pressed
				if(SoftwareTimer_GetFlag(button_counter_id[button]) == FLAG_ON){
					if(button_state[button] == BUTTON_PIN_STATE_PRESSED){
						SoftwareTimer_ResetFlag(button_counter_id[button]);
						hold_flag[button] = 1;
					}
				}
			}
		}
	}
}

void Button_TimerInit(){
	for(int button = 0; button < NUMBER_OF_BUTTON; ++button){
		button_counter_id[button] = SoftwareTimer_AddNewTimer(1);
		SoftwareTimer_SetNewTimer(button_counter_id[button], KEY_PRESS_TIME);
	}
}

void Button_Process(){
	for(int i = 0; i < NUMBER_OF_BUTTON; ++i){
		switch(interface_button_state[i]){
		case RELEASE:
			if(IsPressed(i)){
				interface_button_state[i] = PRESSED;
			}
			break;

		case PRESSED:
			if(!IsPressed(i)){
				interface_button_state[i] = RELEASE;
			}
			else if(IsHeld(i)){
				interface_button_state[i] = HOLD;
			}
			break;

		case HOLD:
			if(!IsPressed(i)){
				interface_button_state[i] = RELEASE;
			}
			break;

		default:
			break;
		}
	}
}

ButtonState_t Button_GetButtonState(uint8_t index){
	if(index < NUMBER_OF_BUTTON && index >= 0){
		return interface_button_state[index];
	}
	else{
		return ERROR_STATE;
	}

}

int IsPressed(int index){
	if(pressed_flag[index] == 1){
		pressed_flag[index] = 0;
		return 1;
	}
	return 0;
}

int IsHeld(int index){
	if(hold_flag[index] == 1){
		hold_flag[index] = 0;
		return 1;
	}
	return 0;

}
