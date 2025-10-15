/*
 * LED_Display.c
 *
 *  Created on: Oct 15, 2025
 *      Author: Hi
 */

#include "LED_Display.h"

//7-segments pin. If the segment is displayed it is set to 1 else 0. The number is set specifically based on the pin setup.
uint16_t segment_pin[10] = {0x0FC0, 0x0180, 0x16C0, 0x13C0, 0x1980, 0x1B80, 0x1F80, 0x01C0, 0x1FC0, 0x1FB0};

void LEDdisplay_ClearEn();
void LEDdisplay_ClearBuffer();

/**
 * Implementation
 */

void LEDdisplay_DisplayNumber(uint8_t number, uint8_t en_pin){
	LEDdisplay_ClearEn();
	HAL_GPIO_WritePin(GPIOB, SEG_EN0_Pin << en_pin, RESET);

	LEDdisplay_ClearBuffer();
	HAL_GPIO_WritePin(GPIOA, segment_pin[number], RESET);
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
