#include "Student.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#pragma warning (disable : 4996)



Student* InitStudent(){

    int length=8, n = 0;
    char c;
    Student* my_student = (Student*)malloc(sizeof(Student));
    if (!my_student)
        return NULL;

    /*printf("Specify number of characters in surname: ");
    scanf("%d", &length);*/
    printf("%d", length);

    my_student->surname = (char*)malloc((length + 1) * sizeof(char));
    if (my_student->surname)
        memset(my_student->surname, 0, length * sizeof(char));

    printf("Specify surname: ");
    gets_s(my_student->surname, length+1);
    printf("Specify year of birth: ");
    scanf("%d", &my_student->birth);

    return my_student;
}

void PrintStudent(void* current){
    Student* tmp = (Student*)current;
    if (tmp) {
        printf("Student surname: %s\n", tmp->surname);
        printf("Student year of birth: %d\n", tmp->birth);
    }
    if (tmp)
        free(tmp);
    tmp = NULL;
}

void FreeStudent(void* ptr){
    Student* obj = (Student*)ptr;
    if (obj)
        free(obj);
    obj = NULL;
}
