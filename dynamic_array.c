/*
	Dynamically growing array implementation

*/
#include <stdio.h>
#include <stdlib.h>

typedef struct{
	int *array;		/* the array to store data */
	int used;		/* current number of items in array */
	int size;		/* allocated number of values */
} Array;

enum { MEM_ERROR = -1, INIT = 1, GROW = 2 };

Array *newArray();					   /* to create new array */
int    Add     (Array *arr, int val);  /* add a value to the array */
void   Free    (Array *arr);		   /* delete array and free memory */
void   Display (Array *arr);		   /* display the array */


int main(int argc, char *argv[])
{
	Array *arr = newArray();
	Add(arr, 4);
	printf("New size: %d\n",arr->size );
	Add(arr, 5);
	Add(arr, 7);
	printf("New size: %d\n", arr->size );
	Add(arr, 7);
	printf("New size: %d\n", arr->size );
	Display(arr);
	Free(arr);
	return 0;
}

/* newArray: creates new array and allocates space : O(1) */
Array *newArray(){ 
	Array *arr = (Array *)malloc(sizeof(Array));
	arr->used = 0;
	arr->size = INIT;
	arr->array = (int *)malloc(INIT * sizeof(int));
	return arr;
}

/* Add: insert an element into the array : O(1) */
int Add(Array *arr, int val){
	if( arr->used == arr->size ) { /* if array is full to the current capacity */
		arr->size *= GROW;		/* grow the array (table doubling) */
		arr->array = (int *)realloc(arr->array, arr->size * sizeof(int));
		if( arr->array == NULL )
			return MEM_ERROR;
	}

	arr->array[arr->used] = val;
	return (arr->used)++;
}

/* Free: frees the allocated memory for an array: O(1) */
void Free(Array *arr){
	free(arr->array);
	arr->array = NULL;
	arr->used = arr->size = 0;
}

/* Display: prints the array O(n) */
void Display(Array *arr){
	for(int i=0; i<arr->used; i++)
		printf("%d ", arr->array[i]);
	printf("\n");	
}