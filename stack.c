#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "stack.h"

const
	int STACK_LENGTH_ERROR = 1;

stack* stack_create()
{
	stack* s = (stack* )malloc(sizeof(stack));
	assert(s);
	s->i = 0;
	s->first = NULL;
	s->current = NULL;
		
	return s;
}

void stack_destroy(stack* s)
{
	assert(s);
	free(s);
}

void stack_put(stack* s, stack_elem_type value)
{
	assert(s);
	
	if (s->i == 0)
	{
		s->first = (stack_elem* )malloc(sizeof(stack_elem));
		s->current = s->first;
	}
	else
	{
		s->current->next = (stack_elem* )malloc(sizeof(stack_elem));
		s->current = 	s->current->next;
	}
	s->i++;
	s->current->value = value;
}

stack_elem_type stack_pop(stack* s)
{
	if (s->i == 1)
	{
		stack_elem_type value = s->first->value;
		free(s->first);
		s->first = NULL;
		s->current = NULL;
		s->i = 0;
		return value;
	}
	else
	{
		stack_elem_type value = s->current->value;
		stack_elem* i = s->first;
		while (i->next != s->current) i = i->next;
		free(s->current);
		s->current = i;
		s->i--;
		return value;
	}
}

int stack_ok(stack* s)
{
	assert(s);
	
	int n = s->i, j = 0;
	stack_elem* i = s->first;
	while (i != s->current)
	{
		i = i->next;
		j++;
	}
	if (n != j)
	{
		return STACK_LENGTH_ERROR;
	}
	
	return 0;
}

void stack_dump(stack* s)
{
	
}

void stack_print(stack* s)
{
	assert(s);
	
	printf("Stack contains:\n");
	stack_elem* i = s->first;
	int n = 1;
	while (i != s->current)
	{
		printf("%d: %d\n", n, i->value);
		i = i->next;
		n++;
	}
	printf("%d: %d\n", n, i->value);
}
