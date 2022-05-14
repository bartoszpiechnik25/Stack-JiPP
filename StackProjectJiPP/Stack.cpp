#include "Stack.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static Stack* first = NULL;

Stack* InitStack(void *obj){

	Stack* my_stack = (Stack*)malloc(sizeof(Stack));
	if (my_stack)
		memset(my_stack, 0, sizeof(Stack));
	my_stack->next = NULL;
	my_stack->data = obj;
	return my_stack;
}

void FreeStack(void* top, FreePtr free_ptr){
	Stack* tmp = (Stack*)malloc(sizeof(Stack));
	Stack* parent = (Stack*)top;
	while (parent) {
		tmp = parent;
		parent = parent->next;
		(*free_ptr)(tmp->data);
		if (tmp)
			free(tmp);
		tmp = NULL;
	}
}

void PrintStack(void* top, PrintData ptr_print){
	Stack* tmp = (Stack*)top;
	while (tmp) {
		(*ptr_print)(tmp);
		tmp = tmp->next;
	}
}

void Pop(void* top, FreePtr free_ptr){
	Stack* temp = (Stack*)malloc(sizeof(Stack));
	Stack* parent = (Stack*)top;
	temp = parent;
	parent = parent->next;
	(*free_ptr)(temp->data);
}

void Push(void* top, void *object){
	Stack* new_item = (Stack*)malloc(sizeof(Stack));
	new_item->data = object;
	new_item->next = first;
	first = new_item;
}