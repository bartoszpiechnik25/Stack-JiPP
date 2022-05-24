#pragma once

#ifndef ERRORS_H
#define ERRORS_H

enum ERRORS {
	ALLOCATION_ERROR,
	STACK_UNDERFLOW,
	FATAL_ERR, 
};

void error(enum ERRORS num);
void file_err(FILE* fileptr, __int64* fdesc);

#endif

