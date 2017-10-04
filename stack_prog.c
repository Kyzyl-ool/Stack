#include <stdio.h>
#include "stack.h"

const
	int n = 10;

int main()
{
	stack* s = stack_create();
	
	for (int i = 0; i < n; i++)
	{
		stack_put(s, i*8);
	}
	stack_print(s);
	stack_pop(s);
	stack_pop(s);
	stack_pop(s);
	stack_print(s);
	
	stack_destroy(s);
	return 0;
}
