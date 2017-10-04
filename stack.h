typedef int stack_elem_type;
struct stack_elem
{
	stack_elem_type value;
	struct stack_elem* next;
};

typedef struct stack_elem stack_elem;

struct stack
{
	stack_elem* first;
	stack_elem* current;
	int i;
};
typedef struct stack stack;

stack* stack_create();
void stack_destroy(stack* s);
void stack_put(stack* s, stack_elem_type value);
stack_elem_type stack_pop(stack* s);
int stack_ok(stack* s);
void stack_dump(stack* s);
void stack_print(stack* s);
