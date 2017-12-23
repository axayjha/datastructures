/*
	Growing array implementation
	From The practice of programming by Brian Kernighan
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Nameval Nameval;
struct Nameval{
	char *name;
	int  value;
};

struct NVtab{
	int nval;			/* current number of values */
	int max;			/* allocated number of values */
	Nameval *nameval;	/* array of name-value pairs */
} nvtab;

enum { MEM_ERROR = -1, NVINIT = 1, NVGROW = 3 };

/* addname: add new name and value to nvtab */
int addname(Nameval newname)
{
	Nameval *nvp;

	if( nvtab.nameval == NULL ) { /* first time */
		nvtab.nameval = (
			Nameval *)malloc(NVINIT * sizeof(Nameval));
		if(nvtab.nameval == NULL)
			return MEM_ERROR;
		nvtab.max = NVINIT;
		nvtab.nval = 0;
	} else if ( nvtab.nval >= nvtab.max ) {  /* grow */
		nvp = (Nameval *)realloc(nvtab.nameval, 
			(NVGROW*nvtab.max)*sizeof(Nameval));
		if (nvp == NULL)
			return MEM_ERROR;
		nvtab.max *= NVGROW;
		nvtab.nameval = nvp;
	}
	nvtab.nameval[nvtab.nval] = newname;
	return nvtab.nval++;
}

/* delname: remove first matching nameval from nvtab */
int delname(char *name)
{
	int i;
	for(i = 0; i < nvtab.nval; i++)
		if( strcmp(nvtab.nameval[i].name, name) == 0 ) {
			memmove(nvtab.nameval+i, nvtab.nameval+i+1, 
					(nvtab.nval - (i+1)) * sizeof(Nameval));
			nvtab.nval--;
			return 1;
		}
	return 0;	
}

int main()
{
	Nameval n = {"akshay", 4};
	addname(n);
	printf("%s\n", nvtab.nameval[0].name );

}