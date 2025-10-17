/*
 * LED_Display.c
 *
 *  Created on: Oct 15, 2025
 *      Author: Hi
 */

#include "LED_Display.h"

//7-segments pin. If the segment is displayed it is set to 1 else 0. The number is set specifically based on the pin setup.
const uint8_t segment_code[7] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40}; //a->g
const uint8_t number_code[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};	//0->9 a->g

void LEDdisplay_ClearEn();
void LEDdisplay_ClearBuffer();
void Display7SEG(int number);
void ClearTraficLight();

/**
 * Implementation
 */

void LEDdisplay_DisplayNumber(uint8_t number, uint8_t en_pin){
	LEDdisplay_ClearEn();
	HAL_GPIO_WritePin(GPIOB, SEG_EN0_Pin << en_pin, RESET);

	LEDdisplay_ClearBuffer();
	Display7SEG(number);
}

void LEDdisplay_ClearEn(){
	for(int i = 0; i < 4; ++i)
		HAL_GPIO_WritePin(GPIOB, SEG_EN0_Pin << i, SET);
}

void LEDdisplay_ClearBuffer(){
	for(int i = 0; i < 7; ++i){
		HAL_GPIO_WritePin(GPIOA, SEG_A_Pin << i, SET);
	}
}

void Display7SEG(int number){
	HAL_GPIO_WritePin(GPIOA, SEG_A_Pin << 0, !(segment_code[0] & number_code[number]));
	HAL_GPIO_WritePin(GPIOA, SEG_A_Pin << 1, !(segment_code[1] & number_code[number]));
	HAL_GPIO_WritePin(GPIOA, SEG_A_Pin << 2, !(segment_code[2] & number_code[number]));
	HAL_GPIO_WritePin(GPIOA, SEG_A_Pin << 3, !(segment_code[3] & number_code[number]));
	HAL_GPIO_WritePin(GPIOA, SEG_A_Pin << 4, !(segment_code[4] & number_code[number]));
	HAL_GPIO_WritePin(GPIOA, SEG_A_Pin << 5, !(segment_code[5] & number_code[number]));
	HAL_GPIO_WritePin(GPIOA, SEG_A_Pin << 6, !(segment_code[6] & number_code[number]));
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

void LEDdisplay_ToggleLight(int light){
	switch(light){
	case LIGHT_RED:
		HAL_GPIO_TogglePin(RED_A_GPIO_Port, RED_A_Pin);
		HAL_GPIO_TogglePin(RED_B_GPIO_Port, RED_B_Pin);
		break;

	case LIGHT_YELLOW:
		HAL_GPIO_TogglePin(YELLOW_A_GPIO_Port, YELLOW_A_Pin);
		HAL_GPIO_TogglePin(YELLOW_B_GPIO_Port, YELLOW_B_Pin);
		break;

	case LIGHT_GREEN:
		HAL_GPIO_TogglePin(GREEN_A_GPIO_Port, GREEN_A_Pin);
		HAL_GPIO_TogglePin(GREEN_B_GPIO_Port, GREEN_B_Pin);
		break;

	default:
		break;
	};
}
