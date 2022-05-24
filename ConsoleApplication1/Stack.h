#pragma once

#ifndef MY_STACK_H
#define MY_STACK_H
#pragma warning (disable : 4996)


typedef struct My_Stack {
	void* object; //pointer to data
	struct My_Stack* next; //pointer to next element
}Stack;

typedef void(*FreePtr)(void* pdata);
typedef void(*PrintObject)(void* pdata);
typedef int(*File)(void* pdata, FILE* file);
typedef void* (*LoadPtr)(FILE* file);
typedef int(FindPtr)(void* currdata, void* searchdata);

void InitStack(FreePtr ptr, PrintObject display, File save, LoadPtr load);
void DisplayStack();
Stack* PushStack(void* ptrData);
void* PopStack();
void FreeStack();
void* SearchStack(void* searchdata, FindPtr search_ptr, int iffirst);
void SaveStack();
void LoadStack();

#endif