#pragma once

typedef enum {
	ComputerScience,
	Math,
	Physics
}COURSE;

typedef struct MyStudent {
	char *surname;
	int birth;
	COURSE crs;
}Student;



Student* InitStudent();
void PrintStudent(void* current);
void FreeStudent(void* current);
