/*
 * LED_Display.h
 *
 *  Created on: Oct 15, 2025
 *      Author: Hi
 */

#ifndef INC_LED_DISPLAY_H_
#define INC_LED_DISPLAY_H_

#include "main.h"
#include <stdint.h>

#define LIGHT_RED 0
#define LIGHT_YELLOW 1
#define LIGHT_GREEN 2

//TLS_A_B where A and B is the led state of each set
typedef enum TraficLightState{
	TLS_INIT = 0,
	TLS_GREEN_RED,
	TLS_YELLOW_RED,
	TLS_RED_GREEN,
	TLS_RED_YELLOW
}TraficLightState_t;

void LEDdisplay_DisplayNumber(uint8_t buffer, uint8_t en_pin);
void DisplayTraficLight(TraficLightState_t state);
void ClearTraficLight();

void LEDdisplay_ToggleLight(int light);
#endif /* INC_LED_DISPLAY_H_ */
