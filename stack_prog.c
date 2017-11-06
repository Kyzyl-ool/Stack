#include <stdio.h>
#include "stack.h"

int main()
{
	stack* s = stack_Construct(10);
	if (stack_Pop(s) == POISON)
	{
		return terminate_message(ERROR_POP_FROM_EMPTY_STACK);
	}
	stack_Push(s, 5);
	stack_print_dump(s);
	stack_Destroy(s);
	
	return 0;
}
