#include <stdlib.h>
#include <stdio.h>
#include "errors.h"
#include "Stack.h"

static char* errormess[] ={
	(char*)"A!!!Memory allocation error!!!",
	(char*)"B!!!Stack underflow!!!",
	(char*)"A!!!Fatal error!!!"
};

void error(enum ERRORS num){
	puts(errormess[num] + 1);

	if (errormess[num][0] == 'A'){
		FreeStack();
		system("pause");
	}
	return;
}

void file_err(FILE* fileptr, __int64* fdesc){
	if (fileptr)
		fclose(fileptr);
	if (fdesc)
		free(fdesc);

	error(FATAL_ERR);
	system("pause");
	exit(1);
}