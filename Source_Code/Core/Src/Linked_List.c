/*
 * Linked_List.c
 *
 *  Created on: Sep 25, 2025
 *      Author: Hi
 */
#include "Linked_List.h"

void LinkedList_Add(TimerNode_t* head, TimerNode_t* new_node){


	//Step 1: Move the new_node to the correct place
	//While loop is necessary for iterating through the list
	TimerNode_t* current_node = head;
	while(current_node->next && current_node->next->timer.counter < new_node->timer.counter){
		new_node->timer.counter -= current_node->next->timer.counter;
		current_node = current_node->next;
	}

	//Step 2: Connect the new_node to the correct place
	new_node->next = current_node->next;
	current_node->next = new_node;

	//Step 3: Update its next node if it exist
	if(new_node->next){
		new_node->next->timer.counter -= new_node->timer.counter;
	}
}

void LinkedList_PopHead(TimerNode_t* head){
	TimerNode_t* poped_node = head->next;
	head->next = poped_node->next;
}
