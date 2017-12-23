/*
	A simple stack implementation
	Akshay Anand
*/

#include <stdio.h>
#include <stdlib.h>

#define SIZE 50

typedef struct {
	int data[SIZE];		/* array to store data linearly */
	int top;			/* top of the stack */
} Stack;

enum { ERROR = 0xb00b };

Stack *newStack();
void push(Stack *, int);
int  pop(Stack *);


int main(int argc, char *argv[])
{
	// TODO
	Stack *st1 = newStack();
	push(st1, 4);
	push(st1, 5);
	printf("%d\n", pop(st1));
	printf("%d\n", pop(st1));
	printf("%d\n", pop(st1));
	return 0;
}

/* newStack: creates new stack and allocates memory */
Stack *newStack()
{
	Stack *st = (Stack *)malloc(sizeof(Stack));
	st->top = -1;
	return st;
}

/* push: pushes an element on top of the stack */
void push(Stack *st, int val)
{
	if(st==NULL)		/* if stack hasn't been allocated memory */
		st = newStack();

	if(st->top == SIZE-1 ){		/* if all allocated memory used up */
		fprintf(stderr, "STACK OVERFLOW\n" );
		return;
	} else			 /* if everything's fine */
		st->data[++(st->top)] = val;
}

/* pop: removes and returns the element on the top of the stack */
int pop(Stack *st)
{	

	if(st == NULL || st->top == -1){	/* if stack isn't allocated memory or if its empty */
		fprintf(stderr, "STACK UNDERFLOW: " );
		return ERROR;
	} else{ 	/* if everything's fine */
		return st->data[(st->top)--];
	}
}