/*
 * Linked_List.h
 *
 *  Created on: Sep 25, 2025
 *      Author: Hi
 */

#ifndef INC_LINKED_LIST_H_
#define INC_LINKED_LIST_H_

#define FLAG_OFF 0
#define FLAG_ON	1

/*Struct declaration*/
typedef struct Timer Timer_t;
typedef struct TimerNode TimerNode_t;

/*Public Member Function*/
void LinkedList_Add(TimerNode_t* head, TimerNode_t* new_node);
void LinkedList_PopHead(TimerNode_t* head);

/*Private Member Function*/



/*Struct definition*/
struct Timer{
	int id;
	int base_counter;
	int counter;
	int flag;
};

struct TimerNode{
	Timer_t timer;
	TimerNode_t* next;
};


#endif /* INC_LINKED_LIST_H_ */
