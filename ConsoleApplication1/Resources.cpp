#include <stdlib.h>
#include <stdio.h>
#include "Resources.h"

void clear_buffer(){
	int chr;
	while ((chr = fgetc(stdin)) != EOF && chr != '\n');
}
