#pragma once
#pragma warning (disable : 4996)

#ifndef DATA_H
#define DATA H

enum COURSE{
	ComputerScience,
	Math,
	Physics,
	MAJOR_TOTAL
};


typedef struct MyStudent{
	int birth;
	enum COURSE crs;
	size_t len;
	char* surname;
}Student;

void FreeStudent(void* ptr);
void* InitStudent(char* lname, int year, enum COURSE maj);
void* PushStudent(char* lastname, int year, enum COURSE maj);
void PrintStudent(void* ptr);
int SurnameInStudent(void* currdata, void* searchdata);
int YearInStudent(void* currdata, void* searchdata);
int CourseInStudent(void* currdata, void* searchdata);
int SaveStudent(void* ptr, FILE* filename);
void* LoadStudent(FILE* filename);
#endif // !DATA_H



