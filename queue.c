/*
	A simple linear queue implementation
	Akshay Anand
*/

#include <stdio.h>
#include <stdlib.h>
#define SIZE 50

typedef struct{
	int data[SIZE];
	int rear, front;
} Queue;

enum { ERROR = 0xb00b };

Queue *newQueue();
void enqueue(Queue *, int);
int dequeue(Queue *);
void print(Queue *);

int main(int argc, char *argv[])
{
	// TODO
	Queue *q = newQueue();
	enqueue(q, 4);
	enqueue(q, 5);
	print(q);
	printf("%d\n", dequeue(q));
	printf("%d\n", dequeue(q));
	printf("%d\n", dequeue(q));
	print(q);
	enqueue(q, 4);
	enqueue(q, 5);
	print(q);
	return 0;
}

Queue *newQueue()
{
	Queue *q = (Queue *)malloc(sizeof(Queue));
	q->front = q->rear = -1;
	return q; 
}

void enqueue(Queue *q, int val)
{
	if( q == NULL )		/* if memory for queue hasn't been allocated */
		q = newQueue();
	if( q->rear == SIZE-1 ){	/* if all of allocated memory is used up */
		fprintf(stderr, "QUEUE FULL: ERROR\n" );
		return;
	} else {		/* if everything's fine */
		if(q->front == -1) q->front++;
		q->data[++(q->rear)] = val;
	}		
}

int dequeue(Queue *q)
{
	if( q == NULL || q->front == -1 ){	/* if queue isn't allocated or is empty */
		fprintf(stderr, "QUEUE EMPTY: ERROR " );
		return ERROR;
	} else {	 /* if everything's fine */		
		int val = q->data[q->front++];
		if(q->front > q->rear) q->front = q->rear = -1;
		return val;
	}
}

void print(Queue *q)
{
	if( q==NULL || q->rear==-1 ){	/* if queue isn't allocated any memory or is empty */
		fprintf(stderr, "NULL QUEUE\n" );
		return;
	}
	printf("[ ");
	for(int i=q->front; i<=q->rear; i++)
		printf("%d ", q->data[i]);
	printf("]\n");
}