/*
	Singly linked list implementation (Kernighan style)
	Akshay
*/

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <limits.h>


typedef struct node node;
struct node {
	int data;
	node *next;	
};

node *newnode(int data);
void putdata(node *nodep, int data);
void apply(node *listp, void (*fn)(node *, void *), void *arg);
void printl(node *nodep, void *arg);
void inccounter(node *nodep, void *arg);
size_t len(node *listp);
node *addfront(node *listp, int data);
node* addend(node *listp, int data);
node *insert(node *listp, int data, int position);
void print(node *headp);
node *delend(node *listp);
node *delfront(node *listp);
node *delitem(node *listp, int data);
void freeall(node *listp);
int lookup(node *listp, int data);
void sort(node *listp);



int main(int argc, char *argv[])
{
	node *list;
	list = addend(list, 5);
	list = addend(list, 2);
	list = addend(list, 4);
	list = insert(list, 7, 3);
	//sort(list);
	//list = delfront(list);
	//list = delitem(list, 4);
	print(list);

	return 0;
}


/* newnode: creates new node and allocates memory */
node *newnode(int data){
	node *nodep;
	nodep = (node *)malloc(sizeof(node));
	nodep->next = NULL;
	nodep->data = data;
	return nodep;	
}

/* 	putdata: sets node data */
void putdata(node *nodep, int data){	
	nodep->data = data;
}

/* apply: execute fn for each element of list */
void apply(node *listp, 
		void (*fn)(node *, void *), void *arg) {

	for( ; listp != NULL; listp = listp->next)
		(*fn)(listp, arg);	/* call the function */
}


/* 
printl: prints the node data
	nodep : node to print
	arg : the format in which to print

pass this function to apply to print whole list	
	apply(headp, printl, "%d ");
*/
void printl(node *nodep, void *arg){
	char *fmt;
	fmt = (char *)arg;
	printf(fmt, nodep->data);
}



void print(node *headp) {
	printf("[ ");
	apply(headp, printl, "%d ");
	printf("]\n");
}

/* 
inccounter: increment counter *arg 
use with apply to count the elements in the list
*/
void inccounter(node *nodep, void *arg){
	int *ip;

	/* nodep is unused */
	ip = (int *)arg;
	(*ip)++;
}


/* len: returns the length of the list */
size_t len(node *listp){
	size_t n = 0;
	apply(listp, inccounter, &n);
	return n;
}


/* addfront: add newp to the front of listp : O(1) */
node *addfront(node *listp, int data){
	node *nodep = newnode(data);
	nodep->next = listp;
	return nodep;
}

/* addend: append to the end of list */
node *addend(node *listp, int data){
	node *walkp = listp;
	if(listp == NULL)
		return newnode(data);

	for( ; walkp->next != NULL; walkp = walkp->next)
			;

	walkp->next = newnode(data);
    return listp;
}

/* delfront: delete the first item */
node *delfront(node *headp){
	return headp->next;
}

/* insert: insert a node at specified position */
node *insert(node *listp, int data, int position){
	if(position == 0)
		return addfront(listp, data);
		
	node *walkp = listp;
	for(int i=0; i<position-1; i++, walkp = walkp->next)
		if(walkp->next == NULL){
			fprintf(stderr, "insert: position out of range\n");
			return NULL;
		}
		
	node *newp  = newnode(data);
	newp->next  = walkp->next;
	walkp->next = newp;
	return listp;
}

/* delend: delete the last node */
node *delend(node *listp){
	node *prev, *walkp = listp;
	if(listp->next == NULL){
		free(listp);
		return NULL;
	} 

	for( ; walkp->next != NULL; walkp = walkp->next)
			prev = walkp;

	free(prev->next);	
	prev->next = NULL;
	return listp;
}

/* delitem: delete first "name" from listp */
node *delitem(node *listp, int data){
	node *p, *prev;

	prev = NULL;
	for(p = listp; p != NULL; p = p->next) {
		if(p->data = data) {
			if(prev == NULL)
				listp = p->next;
			else
				prev->next = p->next;
			free(p);
			return listp;
		}
		prev = p;
	}
	fprintf(stderr, "delitem: %d not in the list\n", data);
	return NULL; 	/* can't get here */
}

/* freeall: free all elements of listp */
void freeall(node *listp){
	node *next;
	for( ; listp != NULL; listp = next) {
		next = listp->next;
		free(listp);
	}

}

/* lookup: returns the index of first appearance of data */
int lookup(node *listp, int data){	
	int i=0;
	for(node *walkp = listp; walkp != NULL; walkp = walkp->next, i++)
		if(walkp->data == data)
			return i;
	return -1;
}

/* sort: sort the list in ascending order using modified bubble sort */
void sort(node *listp) {
	bool swapped;
	node *nodep;

	if(listp == NULL || listp->next == NULL)
		return;

	do{
		swapped = false;
		nodep = listp;

		while(nodep->next != NULL){
			if(nodep->data > nodep->next->data){
				int temp = nodep->data;
				nodep->data = nodep->next->data;
				nodep->next->data = temp;
				swapped = true;
			}
			nodep = nodep->next;
		}
	} while(swapped);
}