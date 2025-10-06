/*
 * Software_Timer.c
 *
 *  Created on: Sep 25, 2025
 *      Author: Hi
 */

#include "Software_Timer.h"



TimerNode_t* head;
TimerNode_t* timers[16] = {};
int timer_count = 0;

/**
 * Initialize Dummy Node
 * Must be called before enter infinite loop
 * Must be called before using any other function
 */
void SoftwareTimer_Init(){
	head = (TimerNode_t*)malloc(sizeof(TimerNode_t));
	head->next = NULL;
	head->timer = (Timer_t){0, 0, FLAG_OFF};
}

/**
 * Must only be called when new timer is needed
 * Should only be used outside of infinite loop
 */
int SoftwareTimer_AddNewTimer(int time_amount){
	//Step 1: Create a new timer
	Timer_t new_timer = {timer_count, time_amount, time_amount, FLAG_OFF};

	//Step 2: Create a new timer_node
	TimerNode_t* new_node = (TimerNode_t*)malloc(sizeof(TimerNode_t));
	new_node->timer = new_timer;

	//Step 3: Add the node into the array for reference
	timers[timer_count] = new_node;

	//Step 4: Add to the linked list
	LinkedList_Add(head, new_node);
	return timer_count++;
}

void SoftwareTimer_SetNewTimer(int id, int time_amount){
	timers[id]->timer.base_counter = time_amount;
}

const int SoftwareTimer_GetFlag(int id){
	return timers[id]->timer.flag;
}

void SoftwareTimer_ResetFlag(int id){
	timers[id]->timer.flag = FLAG_OFF;
	timers[id]->timer.counter = timers[id]->timer.base_counter;
	LinkedList_Add(head, timers[id]);
}

void SoftwareTimer_Step(){
	TimerNode_t* node = head->next;
	if(node->timer.counter > 0){
		node->timer.counter--;
	}

	if(node->timer.counter <= 0){
		int id = node->timer.id;
		timers[id]->timer.flag = FLAG_ON;
		LinkedList_PopHead(head);
	}
}
