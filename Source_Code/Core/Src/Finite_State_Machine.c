/*
 * Finite_State_Machine.c
 *
 *  Created on: Oct 15, 2025
 *      Author: Hi
 */

#include "Finite_State_Machine.h"

#define NUMBER_OF_EN_PIN 4

#define BUTTON_SELECT 0
#define BUTTON_MODIFY 1
#define BUTTON_SET 2

/**
 * Private member function
 */

void FiniteStateMachine_Init();
void FiniteStateMachine_Normal();
void FiniteStateMachine_ModifyRed();
void FiniteStateMachine_ModifyYellow();
void FiniteStateMachine_ModifyGreen();
void FiniteStateMachine_ToggleLight();

void UpdateLEDBuffer();
void UpdateBaseCounter();
void BalanceBaseCounter(int priority_light);

/**
 * Private variable
*/
//States
MachineState_t machine_state = FSM_INIT;
TraficLightState_t trafic_light_state = TLS_INIT;

//Timer id
int blinking_timer_id;
int led_display_timer_id;
int trafic_light_timer_id;
int modify_restrict_timer_id;

//Misc
uint8_t en_pin = 0;
uint8_t led_buffer[4] = {0, 0, 0, 0};

uint8_t base_counter_red = 99;
uint8_t base_counter_yellow = 2;
uint8_t base_counter_green = 97;

uint8_t modifiable_base_counter;

uint8_t counter_A;
uint8_t counter_B;

int first_init = 1;

void FiniteStateMachine_Run(){
	switch(machine_state){
	case FSM_INIT:
		FiniteStateMachine_Init();
		break;

	case FSM_NORMAL:
		if(SoftwareTimer_GetFlag(trafic_light_timer_id) == FLAG_ON){
			SoftwareTimer_ResetFlag(trafic_light_timer_id);
			FiniteStateMachine_Normal();
		}

		//Wait for button input to change state
		if(Button_GetButtonState(BUTTON_SELECT) == PRESSED){
			machine_state = FSM_MODIFY_RED;
			modifiable_base_counter = base_counter_red;
			led_buffer[0] = 0;
			led_buffer[1] = 2;
			led_buffer[2] = base_counter_red / 10;
			led_buffer[3] = base_counter_red - led_buffer[2] * 10;
			ClearTraficLight();
		}
		break;

	case FSM_MODIFY_RED:
		FiniteStateMachine_ModifyRed();
		//Check if set_button is pressed
		if(machine_state == FSM_INIT)
			break;

		if(Button_GetButtonState(BUTTON_SELECT) == PRESSED){
			machine_state = FSM_MODIFY_YELLOW;
			modifiable_base_counter = base_counter_yellow;
			led_buffer[0] = 0;
			led_buffer[1] = 3;
			led_buffer[2] = base_counter_yellow / 10;
			led_buffer[3] = base_counter_yellow - led_buffer[2] * 10;
			ClearTraficLight();
		}
		break;

	case FSM_MODIFY_YELLOW:
		FiniteStateMachine_ModifyYellow();
		//Check if set_button is pressed
		if(machine_state == FSM_INIT)
			break;

		if(Button_GetButtonState(BUTTON_SELECT) == PRESSED){
			machine_state = FSM_MODIFY_GREEN;
			modifiable_base_counter = base_counter_green;
			led_buffer[0] = 0;
			led_buffer[1] = 4;
			led_buffer[2] = base_counter_green / 10;
			led_buffer[3] = base_counter_green - led_buffer[2] * 10;
			ClearTraficLight();
		}
		break;
	case FSM_MODIFY_GREEN:
		FiniteStateMachine_ModifyGreen();
		//Check if set_button is pressed
		if(machine_state == FSM_INIT)
			break;

		if(Button_GetButtonState(BUTTON_SELECT) == PRESSED){
			machine_state = FSM_NORMAL;
			trafic_light_state = TLS_INIT;
			ClearTraficLight();
		}
		break;

	default:
		break;
	}

	//LED Blinking for all state
	if(SoftwareTimer_GetFlag(blinking_timer_id) == FLAG_ON){
		SoftwareTimer_ResetFlag(blinking_timer_id);
		FiniteStateMachine_ToggleLight();
	}

	//7-Segments LED Display for all state
	if(SoftwareTimer_GetFlag(led_display_timer_id) == FLAG_ON){
		SoftwareTimer_ResetFlag(led_display_timer_id);
		LEDdisplay_DisplayNumber(led_buffer[en_pin], en_pin);
		++en_pin;
		if(en_pin >= NUMBER_OF_EN_PIN){
			en_pin = 0;
		}
	}
	Button_Process();
}

void FiniteStateMachine_Init(){
	if(first_init == 1){
		SoftwareTimer_Init();
		Button_TimerInit();
		first_init = 0;

		blinking_timer_id = SoftwareTimer_AddNewTimer(250);
		led_display_timer_id = SoftwareTimer_AddNewTimer(125);
		trafic_light_timer_id = SoftwareTimer_AddNewTimer(1000);
		modify_restrict_timer_id = SoftwareTimer_AddNewTimer(250);
	}


	machine_state = FSM_NORMAL;
	trafic_light_state = TLS_INIT;
	en_pin = 0;

	HAL_GPIO_WritePin(GPIOA, LED_Pin|SEG_A_Pin|SEG_B_Pin|SEG_C_Pin
	                          |SEG_D_Pin|SEG_E_Pin|SEG_F_Pin|SEG_G_Pin, GPIO_PIN_RESET);

	HAL_GPIO_WritePin(GPIOB, RED_A_Pin|YELLOW_A_Pin|GREEN_A_Pin|RED_B_Pin
	                          |YELLOW_B_Pin|GREEN_B_Pin|SEG_EN0_Pin|SEG_EN1_Pin
	                          |SEG_EN2_Pin|SEG_EN3_Pin, GPIO_PIN_RESET);
}

void FiniteStateMachine_Normal(){
	switch(trafic_light_state){
	case TLS_INIT:
		if(1){
			counter_A = base_counter_green;
			counter_B = base_counter_red;
			trafic_light_state = TLS_GREEN_RED;
			if(counter_A <= 0){
				counter_A = base_counter_yellow;
				trafic_light_state = TLS_YELLOW_RED;
				DisplayTraficLight(TLS_YELLOW_RED);
			}
			else{
				trafic_light_state = TLS_GREEN_RED;
				DisplayTraficLight(TLS_GREEN_RED);
			}
		}
		break;

	case TLS_GREEN_RED:
		if(counter_A <= 0){
			trafic_light_state = TLS_YELLOW_RED;
			counter_A = base_counter_yellow;
			DisplayTraficLight(TLS_YELLOW_RED);
		}
		break;

	case TLS_YELLOW_RED:
		if(counter_A <= 0 || counter_B <= 0){
			counter_A = base_counter_red;
			counter_B = base_counter_green;
			if(counter_B <= 0){
				counter_B = base_counter_yellow;
				trafic_light_state = TLS_RED_YELLOW;
				DisplayTraficLight(TLS_RED_YELLOW);
			}
			else{
				trafic_light_state = TLS_RED_GREEN;
				DisplayTraficLight(TLS_RED_GREEN);
			}
		}
		break;

	case TLS_RED_GREEN:
		if(counter_B <= 0){
			trafic_light_state = TLS_RED_YELLOW;
			counter_B = base_counter_yellow;
			DisplayTraficLight(TLS_RED_YELLOW);
		}
		break;

	case TLS_RED_YELLOW:
		if(counter_A == 0 || counter_B == 0){
			counter_A = base_counter_green;
			counter_B = base_counter_red;

			if(counter_A <= 0){
				counter_A = base_counter_yellow;
				trafic_light_state = TLS_YELLOW_RED;
				DisplayTraficLight(TLS_YELLOW_RED);
			}
			else{
				trafic_light_state = TLS_GREEN_RED;
				DisplayTraficLight(TLS_GREEN_RED);
			}
		}
		break;

	default:
		break;
	}
	UpdateLEDBuffer();
	--counter_A;
	--counter_B;
}

void FiniteStateMachine_ModifyRed(){
	UpdateBaseCounter();
	if(Button_GetButtonState(BUTTON_SET) == PRESSED){
		base_counter_red = modifiable_base_counter;
		BalanceBaseCounter(LIGHT_RED);
		machine_state = FSM_INIT;
	}
}

void FiniteStateMachine_ModifyYellow(){
	UpdateBaseCounter();
	if(Button_GetButtonState(BUTTON_SET) == PRESSED){
		base_counter_yellow = modifiable_base_counter;
		BalanceBaseCounter(LIGHT_YELLOW);
		machine_state = FSM_INIT;
	}
}

void FiniteStateMachine_ModifyGreen(){
	UpdateBaseCounter();
	if(Button_GetButtonState(BUTTON_SET) == PRESSED){
		base_counter_green = modifiable_base_counter;
		BalanceBaseCounter(LIGHT_GREEN);
		machine_state = FSM_INIT;
	}
}


void UpdateLEDBuffer(){
	led_buffer[0] = counter_A / 10;
	led_buffer[1] = counter_A - led_buffer[0] * 10;
	led_buffer[2] = counter_B / 10;
	led_buffer[3] = counter_B - led_buffer[2] * 10;
}

void FiniteStateMachine_ToggleLight(){
	HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
	switch(machine_state){
	case FSM_MODIFY_RED:
		LEDdisplay_ToggleLight(LIGHT_RED);
		break;

	case FSM_MODIFY_YELLOW:
		LEDdisplay_ToggleLight(LIGHT_YELLOW);
		break;

	case FSM_MODIFY_GREEN:
		LEDdisplay_ToggleLight(LIGHT_GREEN);
		break;

	default:
		break;
	}
}

/**
 * This function is used for all modify states
 * The only different thing between state is modifiable_base_counter is set to the next state when the state is switched
 * The handling when set_button is pressed is in its respective state
 */
void UpdateBaseCounter(){
	switch(Button_GetButtonState(BUTTON_MODIFY)){
	case PRESSED:
		modifiable_base_counter++;
		if(modifiable_base_counter > 99){
			modifiable_base_counter = 1;
		}
		break;

	default:
		break;
	}

	led_buffer[2] = modifiable_base_counter / 10;
	led_buffer[3] = modifiable_base_counter - led_buffer[2] * 10;
}

void BalanceBaseCounter(int priority_light){
	switch(priority_light){
	case LIGHT_RED:
		base_counter_green = base_counter_red - base_counter_yellow;
		//Balance underflow
		//if red > 0 -> yellow = 1 green = red - yellow
		//base_counter_green is unsigned so underflow would just throw it to 2^8 - 1 - red - yellow
		//That limit will always larger that 99
		if(base_counter_green > 99){
			base_counter_yellow = 1;
			base_counter_green = base_counter_red - base_counter_yellow;
		}
		break;

	case LIGHT_YELLOW:
		base_counter_red = base_counter_green + base_counter_yellow;
		//Red overflow
		//If yellow == 99 -> green = 0 else red = 99 -> green = red - yellow
		if(base_counter_red > 99){
			if(base_counter_yellow == 99){
				base_counter_green = 0;
				base_counter_red = 99;
			}
			else{
				base_counter_red = 99;
				base_counter_green = base_counter_red - base_counter_yellow;
			}
		}
		break;

	case LIGHT_GREEN:
		base_counter_red = base_counter_green + base_counter_yellow;
		if(base_counter_red > 99){
			if(base_counter_green == 99){
				base_counter_yellow = 0;
				base_counter_red = 99;
			}
			else{
				base_counter_red = 99;
				base_counter_yellow = base_counter_red - base_counter_green;
			}
		}
		break;

	default:
		break;
	}
}
