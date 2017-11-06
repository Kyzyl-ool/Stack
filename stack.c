#include "stack.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

stack* stack_Construct(int amount_of_elements)
{
	assert(amount_of_elements);
	stack* s = (stack* )calloc(1, sizeof(stack));
	s->elements = (stack_elem* )calloc(amount_of_elements, sizeof(stack_elem));
	s->kanar1 = KANAR;
	s->kanar2 = KANAR;
	s->current = 0;
	s->amount_of_elements = amount_of_elements;
	s->hashsum = s->kanar1 + s->kanar2 + amount_of_elements;
	int i = 0;
	for (i = 0; i < amount_of_elements; i++) s->elements[i] = POISON;
	
	assert(!stack_check(s));
	return s;
}

int stack_Destroy(stack* s)
{
	assert(s);
	int error_code = stack_check(s);
	for(int i = 0; i < s->current; i++) s->elements[i] = POISON;
	free(s->elements);
	free(s);
	
	return error_code;
}

int stack_Push(stack* s, stack_elem value)
{
	assert(s); isfinite(value);
	
	if (s->current < s->amount_of_elements)
	{
		s->elements[s->current] = value;
		s->current++;
		s->hashsum = stack_calc_hashsum(s);
		return stack_check(s);
	}
	else
	{
		stack_help(stack_error_message(ERROR_PUSH_TO_FULL_STACK));
		return ERROR_PUSH_TO_FULL_STACK;
	}
}

stack_elem stack_Pop(stack* s)
{
	assert(s);
	if (s->current > 0)
	{
		stack_elem value = s->elements[s->current-1];
		s->current--;
		s->elements[s->current] = POISON;
		
		s->hashsum = stack_calc_hashsum(s);
		return value;
	}
	else
	{
		stack_help(stack_error_message(ERROR_POP_FROM_EMPTY_STACK));
		return POISON;
	}
}

int	stack_calc_hashsum(stack* s)
{
	assert(s);
	int hashsum = s->kanar1 + s->kanar2 + s->current + s->amount_of_elements;
	int i = 0;
	for (i = 0; i < s->current; i++) hashsum += s->elements[i];
	
	return hashsum;
}

int	stack_check(stack* s)
{
	if (s->elements[s->current] != POISON) return 1;
	if (s->current >= s->amount_of_elements) return 6;
	for (int i = 0; i < s->current - 1; i++) if (s->elements[i] == POISON) return 2;
	if (s->hashsum != stack_calc_hashsum(s)) return 3;
	
	return STACK_OK;
}

char* stack_error_message(int error_code)
{
	
	#define RET_CODE_(code)  case code: return #code;
	
	switch (error_code)
	{
		RET_CODE_ (STACK_OK)
		RET_CODE_ (STACK_TAIL_IS_NOT_POISON)
		case STACK_ELEMENT_IS_POISON: 				return "STACK_ELEMENT_IS_POISON";
		case STACK_HASHSUM_ERROR: 					return "STACK_HASHSUM_ERROR";
		case ERROR_POP_FROM_EMPTY_STACK: 			return "ERROR_POP_TO_EMPTY_STACK";
		case ERROR_PUSH_TO_FULL_STACK: 				return "ERROR_PUSH_TO_FULL_STACK";
		case STACK_CURRENT_MORE_THAN_LENGTH: 		return "STACK_CURRENT_MORE_THAN_LENGTH";
		default:									return "STACK_UNKNOWN_ERROR";
	}
	
	#undef RET_CODE_
	
}
void stack_help(const char* message)
{
	printf("%s\n", message);
}

void stack_print_dump(stack* s)
{
	FILE* dump = fopen("stack_dump.txt", "w");
	
	fprintf(dump,
	"stack \"s\" (%s) [%p] {\n"
	"	current = %d\n\n", stack_error_message(stack_check(s)), s, s->current);
	
	for (int i = 0; i < s->current; i++) fprintf(dump, "	elements[%d]: %lg\n", i, s->elements[i]);
	fprintf(dump, "}\n");
	
	fclose(dump);
}

int terminate_message(int error)
{
	printf("\aProgram terminated with error message: %d\n" "Meow.\n", error);
	return error;
}
