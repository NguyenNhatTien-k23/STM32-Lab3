/*
 * Finite_State_Machine.h
 *
 *  Created on: Oct 15, 2025
 *      Author: Hi
 */

#ifndef INC_FINITE_STATE_MACHINE_H_
#define INC_FINITE_STATE_MACHINE_H_

#include <stdint.h>

#include "Software_Timer.h"
#include "Button.h"
#include "LED_Display.h"

typedef enum FSMachineState{
	FSM_INIT = 0,
	FSM_NORMAL,
	FSM_MODIFY_RED,
	FSM_MODIFY_YELLOW,
	FSM_MODIFY_GREEN
} MachineState_t;

//TLS_A_B where A and B is the led state of each set
typedef enum TraficLightState{
	TLS_INIT = 0,
	TLS_GREEN_RED,
	TLS_YELLOW_RED,
	TLS_RED_GREEN,
	TLS_RED_YELLOW
}TraficLightState_t;

void FiniteStateMachine_Run();



#endif /* INC_FINITE_STATE_MACHINE_H_ */
