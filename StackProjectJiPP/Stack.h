#pragma once
#include <stddef.h>

typedef void(*FreePtr)(void* ptr);
typedef void(*PrintData)(void* ptr);

typedef struct MyStack{
	void* data;
	MyStack* next;

}Stack;

Stack* InitStack(void* obj);
void FreeStack(void* first, FreePtr free_ptr);

void PrintStack(void* first, PrintData ptr_print);
void Push(void* parent, void* object);
void Pop(void* first, FreePtr free_ptr);


