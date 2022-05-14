// StackProjectJiPP.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//
#include <stdio.h>
#include "Student.h"
#include "Stack.h"

int main()
{

	Student* my_stud = InitStudent();
	//PrintStudent(my_stud);
	fflush(stdin);
	Stack* top = InitStack(my_stud);
	//PrintStack(my, PrintStudent);
	Student* my_stud2 = InitStudent();
	Push(top, my_stud2);
	PrintStack(top, PrintStudent);

	return 0;
}

