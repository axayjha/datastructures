/*
	A simple circular CQueue implementation
	Akshay Anand
*/

#include <stdio.h>
#include <stdlib.h>
#define SIZE 5

typedef struct{
	int data[SIZE];
	int rear, front;
} CQueue;

enum { ERROR = 0xb00b };

CQueue *newQueue();
void enqueue(CQueue *, int);
int dequeue(CQueue *);
void print(CQueue *);

int main(int argc, char *argv[])
{
	// TODO
	CQueue *q = newQueue();
	enqueue(q, 4);
	enqueue(q, 5);
	print(q);
	printf("%d\n", dequeue(q));
	printf("%d\n", dequeue(q));
	printf("%d\n", dequeue(q));
	print(q);
	enqueue(q, 1);
	enqueue(q, 2);
	enqueue(q, 3);
	enqueue(q, 4);
	dequeue(q);
	enqueue(q, 5);
	enqueue(q, 6); // this will circle around for SIZE=5
	print(q);
	return 0;
}

/* newQueue: creates new queue and allocates memory */
CQueue *newQueue()
{
	CQueue *q = (CQueue *)malloc(sizeof(CQueue));
	q->front = q->rear = -1;
	return q; 
}

/* enqueue: inserts new item at the end (the next free slot) */
void enqueue(CQueue *q, int val)
{
	if( q == NULL )		/* if memory for CQueue hasn't been allocated */
		q = newQueue();
	if( (q->rear == SIZE-1 && q->front==0) || q->rear == q->front-1 ){	/* if CQueue is full from both ends*/
		fprintf(stderr, "CQueue FULL: ERROR\n" );
		return;
	} 
	else if(q->rear == SIZE-1 && q->front > 0){	/* if CQueue is full from rear but not from front*/
		q->rear = 0;
		q->data[q->rear] = val;
	}

	else {		/* if everything's fine */
		if(q->front == -1) q->front++;
		q->data[++(q->rear)] = val;
	}		
}

/* dequeue: remove the item from the front */
int dequeue(CQueue *q)
{
	if( q == NULL || q->front == -1 ){	/* if CQueue isn't allocated or is empty */
		fprintf(stderr, "CQueue EMPTY: ERROR " );
		return ERROR;
	} 
	else if( q->rear < q->front && q->front==SIZE-1){	/* if CQueue is empty from one side */
		int val = q->data[q->front];
		q->front = 0;
		return val;
	}

	else {	 /* if everything's fine */		
		int val = q->data[q->front];
		if(q->front == q->rear) q->front = q->rear = -1;
		else q->front++;
		return val;
	}
}

/* print: displays the whole queue */
void print(CQueue *q)
{
	if( q==NULL || q->rear==-1 ){	/* if CQueue isn't allocated any memory or is empty */
		fprintf(stderr, "NULL CQueue\n" );
		return;
	}
	printf("[ ");
	if(q->rear >= q->front){	/* if hasn't circled around yet */
		for(int i=q->front; i<=q->rear; i++)
			printf("%d ", q->data[i]);
	}	
	else{		/* if list items have circled around */
		for(int i=q->front; i<SIZE; i++)
			printf("%d ", q->data[i]);
		for(int i=q->rear; i<q->front; i++)
			printf("%d ", q->data[i]);
	}
	printf("]\n");
}