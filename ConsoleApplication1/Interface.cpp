#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Interface.h"
#include "Student.h"
#include "Stack.h"
#include "Errors.h"
#include "Resources.h"

#pragma warning (disable : 4996)

void Menu(){
	InitStack(FreeStudent, PrintStudent, SaveStudent, LoadStudent);
	int option;
	while (1) {
		Display();
		Show_menu();
		scanf("%d", &option);
		clear_buffer();
		switch (option) {
		case 0: Push();
			break;
		case 1: Pop();
			break;
		case 2: Clear();
			break;
		case 3: Find();
			break;
		case 4: Save();
			break;
		case 5: Load();
			break;
		case 6: Clear();
			return;
		default:
			puts("That option does not exists");
		};

	}
}

void Show_menu(){
	puts("0 - Push");
	puts("1 - Pop");
	puts("2 - Clean Stack");
	puts("3 - Find");
	puts("4 - Save to file");
	puts("5 - Load from file");
	puts("6 - Exit");
}

void Show_courses() {
	puts("0 - ComputerScience");
	puts("1 - Math");
	puts("2 - Physics");
}

void Display() {
	DisplayStack();
}

void Push(){
	char surname[256];
	int year, course;
	printf("Input surname:\n");
	scanf_s("%s", surname, (unsigned)sizeof(surname));
	clear_buffer();
	printf("Input year of birth:\n");
	scanf("%d", &year);
	clear_buffer();
	printf("Choose course:\n");
	Show_courses();
	scanf("%d", &course);
	clear_buffer();
	printf("\n");

	void* ptrData = PushStudent(surname, year, (COURSE)course);
	if (!PushStack(ptrData))
		error(ALLOCATION_ERROR);

}

void Pop(){
	void* tmp = PopStack();
	if (tmp != NULL) {
		printf("\n\nData popped:\n");
		PrintStudent(tmp);
		printf("\n");
	}
	FreeStudent(tmp);
}

void Clear(){
	FreeStack();
}

void Find(){
	int choose;
	printf("\nChoose what you want to find:\n");
	puts("0 - Surname\n1 - Year of Birth\n2 - Course");
	scanf("%d", &choose);
	clear_buffer();
	switch (choose)
	{
	case 0: Find_surname();
		break;
	case 1: Find_year();
		break;
	case 2: Find_course();
		break;
	default:
		printf("This number does not exist \n");
	};
}

void Find_surname(){
	char lnsearch[256];
	printf("Input lastname:\n");
	scanf_s("%s", lnsearch, (unsigned)sizeof(lnsearch));

	Student* searchdata = (Student*)malloc(sizeof(Student));

	if (!searchdata){
		error(ALLOCATION_ERROR);
		return;
	}

	memset(searchdata, 0, sizeof(Student));
	size_t size = strlen(lnsearch) + 1;
	searchdata->surname = (char*)malloc(size * sizeof(char));

	if (!searchdata->surname){
		error(ALLOCATION_ERROR);
		return;
	}
	strcpy(searchdata->surname, lnsearch);

	void* ptrsearch = SearchStack(searchdata, SurnameInStudent, 1);

	if (ptrsearch){
		printf("Data found: \n");
		PrintStudent(ptrsearch);
	}
	else
		printf("No data found!");

	while (ptrsearch){
		ptrsearch = SearchStack(searchdata, SurnameInStudent, 0);
		if (ptrsearch)
			PrintStudent(ptrsearch);
	}
	printf("\n");

	FreeStudent(searchdata);
}

void Find_year(){
	int yearsearch;
	printf("Input year: ");
	scanf("%d", &yearsearch);
	clear_buffer();

	Student* searchdata = (Student*)malloc(sizeof(Student));

	if (!searchdata) {
		error(ALLOCATION_ERROR);
		return;
	}

	memset(searchdata, 0, sizeof(Student));

	searchdata->birth = yearsearch;

	void* ptrsearch = SearchStack(searchdata, YearInStudent, 1);

	if (ptrsearch) {
		printf("Data found: \n");
		PrintStudent(ptrsearch);
	}
	else
		printf("No data found!");

	while (ptrsearch) {
		ptrsearch = SearchStack(searchdata, YearInStudent, 0);
		if (ptrsearch)
			PrintStudent(ptrsearch);
	}
	printf("\n\n");

	FreeStudent(searchdata);

}

void Find_course(){
	int coursesearch;
	printf("Choose major:\n");
	Show_courses();
	scanf("%d", &coursesearch);
	clear_buffer();
	Student* searchdata = (Student*)malloc(sizeof(Student));

	if (!searchdata) {
		error(ALLOCATION_ERROR);
		return;
	}

	memset(searchdata, 0, sizeof(Student));
	searchdata->crs = (COURSE)coursesearch;

	void* ptrsearch = SearchStack(searchdata, CourseInStudent, 1);

	if (ptrsearch) {
		printf("Data found: \n");
		PrintStudent(ptrsearch);
	}
	else
		printf("No data found!");

	while (ptrsearch) {
		ptrsearch = SearchStack(searchdata, CourseInStudent, 0);
		if (ptrsearch)
			PrintStudent(ptrsearch);
	}
	printf("\n");

	FreeStudent(searchdata);
}

void Save() {
	SaveStack();
}


void Load() {
	LoadStack();
}