#include <stdlib.h>
#include <stdio.h>
#include "Stack.h"
#include "Errors.h"

static Stack* first = NULL;
char file_name[] = "StackFile.bin";
FreePtr freeptr;
PrintObject display;
File save_to_file;
LoadPtr load_to_file;

void InitStack(FreePtr fr, PrintObject print, File ssave, LoadPtr lload){
	first = NULL;
	freeptr = fr;
	display = print;
	save_to_file = ssave;
	load_to_file = lload;
}

void DisplayStack(){
	Stack* tmp = first;
	if (tmp != NULL) {
		printf("                   ");
		printf("STACK");
		printf("\n\n");
		while (tmp != NULL) {
			display(tmp->object);
			tmp = tmp->next;
		}
		printf("\n\n");
	}
	else printf("Stack is empty! Push data or load from the disk!\n\n");

}

Stack* PushStack(void* ptrData) {
	Stack* next = (Stack*)malloc(sizeof(Stack));//allocating memory for new elemelnt
	if (!next) {
		error(ALLOCATION_ERROR);
		return NULL;
	}

	next->object = ptrData;
	next->next = first; // linking old and new element
	first = next; // changing head of the stack to new element

	return next;
}


void* PopStack()
{
	Stack ret;
	if (!first) {
		error(STACK_UNDERFLOW);
		return NULL;
	}
	else {
		Stack* next = first->next;
		ret.object = first->object;
		free(first);
		first = next;
		return ret.object;
	}

}

void FreeStack() {
	Stack* ptr = first, * ptrtmp = NULL;
	while (ptr) {
		(*freeptr)(ptr->object);
		ptrtmp = ptr;
		ptr = ptr->next;
		free(ptrtmp);
	}
	first = NULL;
}

void* SearchStack(void* searchdata, FindPtr search_ptr, int iffirst){
	static Stack* ptr;
	Stack* ptrtmp = NULL;
	if (first == NULL){
		error(STACK_UNDERFLOW);
		return NULL;
	}
	if (iffirst)
		ptr = first;

	while (ptr){
		if (!(*search_ptr)(ptr->object, searchdata))
			ptr = ptr->next;
		else{
			ptrtmp = ptr;
			ptr = ptr->next;
			return ptrtmp->object;
		}
	}
	return NULL;
}

void SaveStack() {
	Stack* tmp = first;
	if (tmp == NULL) {
		error(STACK_UNDERFLOW);
		return;
	}

	size_t count = 0;
	while (tmp != NULL) {
		count++;
		tmp = tmp->next;
	}
	tmp = first;

	unsigned int items = (unsigned int)count;
	__int64* file_desc = (__int64*)malloc((items + 1) * sizeof(__int64));
	if (!file_desc)
		file_err(NULL, file_desc);

	FILE* pf = fopen(file_name, "wb");
	if (!pf)
		file_err(pf, file_desc);

	if (fwrite(&items, sizeof(unsigned int), 1, pf) != 1)
		file_err(pf, file_desc);

	_fseeki64(pf, (count + 1) * sizeof(__int64), SEEK_CUR);

	size_t item_s = 0;

	while (tmp != NULL) {
		file_desc[item_s] = ftell(pf);
		item_s++;
		if (save_to_file(tmp->object, pf) != 1)
			file_err(pf, file_desc);
		tmp = tmp->next;
	}

	file_desc[item_s] = ftell(pf);

	_fseeki64(pf, sizeof(unsigned int), SEEK_SET);
	if (fwrite(file_desc, sizeof(__int64), count + 1, pf) != count + 1)
		file_err(pf, file_desc);

	if (pf) {
		fclose(pf);
		pf = NULL;
	}

	if (file_desc) {
		free(file_desc);
		file_desc = NULL;
	}
}

void LoadStack() {

	FreeStack();

	__int64* file_desc = NULL;
	unsigned int items = 0, item_s, record;


	FILE* pf = fopen(file_name, "rb");
	if (!pf)
		file_err(pf, file_desc);

	if (fread(&items, sizeof(unsigned int), 1, pf) != 1)
		file_err(pf, file_desc);

	file_desc = (__int64*)malloc((items + 1) * sizeof(__int64));
	if (!file_desc)
		file_err(pf, file_desc);

	if (fread(file_desc, sizeof(file_desc[0]), items + 1, pf) != items + 1)
		file_err(pf, file_desc);

	for (item_s = 0; item_s < items; ++item_s){
		record = items - item_s - 1;
		_fseeki64(pf, file_desc[record], SEEK_SET);

		void* ptrdata = load_to_file(pf);
		if (!PushStack(ptrdata))
		{
			file_err(pf, file_desc);
		}
	}

	if (pf) {
		fclose(pf);
		pf = NULL;
	}

	if (file_desc) {
		free(file_desc);
		file_desc = NULL;
	}
}