#include <stdlib.h>
#include <stdio.h>
#include "Student.h"
#include "string.h"
#include "Errors.h"


void FreeStudent(void* ptr){
	Student* ptrData = (Student*)ptr;
	if (ptrData){
		free(ptrData->surname);
		ptrData->surname = NULL;
		free(ptrData);
		ptrData = NULL;
	}
}

void* InitStudent(char* lname, int year, enum COURSE maj) {
	Student* ptrData = (Student*)malloc(sizeof(Student));
	if (!ptrData) {
		error(ALLOCATION_ERROR);
		return NULL;
	}
	if (ptrData)
	{
		size_t size = strlen(lname) + 1;
		ptrData->len = size;
		ptrData->surname = (char*)malloc(size * sizeof(char));
		if (!ptrData->surname) {
			error(ALLOCATION_ERROR);
			return NULL;
		}
		strcpy(ptrData->surname, lname);
		ptrData->birth = year;
		ptrData->crs = maj;
	}
	return (void*)(ptrData);
}

void* PushStudent(char* lastname, int year, enum COURSE maj) {
	return InitStudent(lastname, year, maj);
}

void PrintStudent(void* current) {
	Student* tmp = (Student*)current;
	if (tmp) {
		printf("------------------------------------------\n");
		printf("Student surname: %s\n", tmp->surname);
		printf("Student year of birth: %d\n", tmp->birth);
		switch (tmp->crs) {
		case ComputerScience:
			puts("Computer Science");
			break;
		case Math:
			puts("Mathematics");
			break;
		case Physics:
			puts("Physics");
			break;
		}
		puts("------------------------------------------");
		//printf("\n");
	}
}

int SurnameInStudent(void* currdata, void* searchdata){
	Student* ptrcurr = (Student*)currdata;
	Student* ptrsearch = (Student*)searchdata;

	if (strcmp(ptrcurr->surname, ptrsearch->surname) == 0)
		return 1;

	return 0;
}

int YearInStudent(void* currdata, void* searchdata){
	Student* ptrcurr = (Student*)currdata;
	Student* ptrsearch = (Student*)searchdata;

	if (ptrcurr->birth == ptrsearch->birth)
		return 1;

	return 0;
}

int CourseInStudent(void* currdata, void* searchdata){
	Student* ptrcurr = (Student*)currdata;
	Student* ptrsearch = (Student*)searchdata;

	if (ptrcurr->crs == ptrsearch->crs)
		return 1;

	return 0;
}

int SaveStudent(void* ptr, FILE* filename) {
	Student* dataptr = (Student*)ptr;

	if (fwrite(dataptr, sizeof(dataptr->birth) + sizeof(dataptr->crs) + sizeof(dataptr->len), 1, filename) != 1)
		return 0;
	if (fwrite(dataptr->surname, dataptr->len * sizeof(dataptr->surname[0]), 1, filename) != 1)
		return 0;

	return 1;
}

void* LoadStudent(FILE* filename){
	Student* tmp = (Student*)malloc(sizeof(Student));
	if (!tmp)
		error(ALLOCATION_ERROR);

	memset(tmp, 0, sizeof(Student));

	if (fread(tmp, sizeof(tmp->birth) + sizeof(tmp->crs) + sizeof(tmp->len), 1, filename) != 1)
		return 0;

	tmp->surname = (char*)malloc(tmp->len * sizeof(char));

	if (fread(tmp->surname, tmp->len * sizeof(char), 1, filename) != 1)
		return 0;

	void* dataptr = PushStudent(tmp->surname, tmp->birth, tmp->crs);
	return dataptr;

}