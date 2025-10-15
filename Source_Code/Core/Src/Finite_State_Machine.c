/*
 * Finite_State_Machine.c
 *
 *  Created on: Oct 15, 2025
 *      Author: Hi
 */

#include "Finite_State_Machine.h"

#define NUMBER_OF_EN_PIN 4

/**
 * Private member function
 */

void FiniteStateMachine_Init();
void FiniteStateMachine_Normal();
void FiniteStateMachine_ModifyRed();
void FiniteStateMachine_ModifyYellow();
void FiniteStateMachine_ModifyGreen();

void UpdateLEDBuffer();
void DisplayTraficLight(TraficLightState_t state);
void ClearTraficLight();

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

//Misc
uint8_t en_pin = 0;
uint8_t led_buffer[4];

uint8_t base_counter_red = 5;
uint8_t base_counter_yellow = 2;
uint8_t base_counter_green = 3;

uint8_t counter_A;
uint8_t counter_B;

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
		//Wait for button input to change
		break;

	case FSM_MODIFY_RED:
	case FSM_MODIFY_YELLOW:
	case FSM_MODIFY_GREEN:

	default:
		break;
	}

	//LED Blinking for all state
	if(SoftwareTimer_GetFlag(blinking_timer_id) == FLAG_ON){
		SoftwareTimer_ResetFlag(blinking_timer_id);
		HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
	}

	//LED Display for all state
//	if(SoftwareTimer_GetFlag(led_display_timer_id) == FLAG_ON){
//		SoftwareTimer_ResetFlag(blinking_timer_id);
//		LEDdisplay_DisplayNumber(led_buffer[en_pin], en_pin++);
//		if(en_pin >= NUMBER_OF_EN_PIN){
//			en_pin = 0;
//		}
//	}
}

void FiniteStateMachine_Init(){
	SoftwareTimer_Init();
	Button_TimerInit();

	blinking_timer_id = SoftwareTimer_AddNewTimer(1000);
	led_display_timer_id = SoftwareTimer_AddNewTimer(250);
	trafic_light_timer_id = SoftwareTimer_AddNewTimer(1000);

	machine_state = FSM_NORMAL;
	en_pin = 0;

	trafic_light_state = TLS_INIT;
}

void FiniteStateMachine_Normal(){
	switch(trafic_light_state){
	case TLS_INIT:
		if(1){
			trafic_light_state = TLS_GREEN_RED;
			counter_A = base_counter_green;
			counter_B = base_counter_red;
			DisplayTraficLight(TLS_GREEN_RED);
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
		if(counter_A <= 0 && counter_B <= 0){
			trafic_light_state = TLS_RED_GREEN;
			counter_A = base_counter_red;
			counter_B = base_counter_green;
			DisplayTraficLight(TLS_RED_GREEN);
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
		if(counter_A <= 0 && counter_B <= 0){
			trafic_light_state = TLS_GREEN_RED;
			counter_A = base_counter_green;
			counter_B = base_counter_red;
			DisplayTraficLight(TLS_GREEN_RED);
		}
		break;

	default:
		break;
	}

	--counter_A;
	--counter_B;
	UpdateLEDBuffer();
}

void FiniteStateMachine_ModifyRed(){

}

void FiniteStateMachine_ModifyYellow(){

}

void FiniteStateMachine_ModifyGreen(){

}


void UpdateLEDBuffer(){
	led_buffer[0] = counter_A / 10;
	led_buffer[1] = counter_A - led_buffer[0] * 10;
	led_buffer[2] = counter_B / 10;
	led_buffer[3] = counter_B - led_buffer[2] * 10;
}

void DisplayTraficLight(TraficLightState_t state){
	ClearTraficLight();
	switch(state){
	case TLS_GREEN_RED:
		HAL_GPIO_WritePin(GPIOB, GREEN_A_Pin, RESET);
		HAL_GPIO_WritePin(GPIOB, RED_B_Pin, RESET);
		break;

	case TLS_YELLOW_RED:
		HAL_GPIO_WritePin(GPIOB, YELLOW_A_Pin, RESET);
		HAL_GPIO_WritePin(GPIOB, RED_B_Pin, RESET);
		break;

	case TLS_RED_GREEN:
		HAL_GPIO_WritePin(GPIOB, RED_A_Pin, RESET);
		HAL_GPIO_WritePin(GPIOB, GREEN_B_Pin, RESET);
		break;

	case TLS_RED_YELLOW:
		HAL_GPIO_WritePin(GPIOB, RED_A_Pin, RESET);
		HAL_GPIO_WritePin(GPIOB, YELLOW_B_Pin, RESET);
		break;

	default:
		break;
	}
}

void ClearTraficLight(){
	for(int i = 0; i < 6; ++i){
		HAL_GPIO_WritePin(GPIOB, RED_A_Pin << i, SET);
	}
}
