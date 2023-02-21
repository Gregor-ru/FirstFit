#include "framework.h"
#include "functions.h"

void main(void)
{
	int* array;
	array = my_malloc(6);
	my_free(array);

}
