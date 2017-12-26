#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct hashtable hashtable;
struct hashtable{
	char *name;
	int value;
	hashtable *next;	/* in chain */
};

enum {
	NHASH = 1007,
	MULTIPLIER = 31,	/* empirically 31 and 37 are used for ASCII strings*/
};

enum tokens {
	KEYWORD = 0x0fab,
	IDENTIFIER = 0xc0c0,
	OPERATOR = 0x0b01,
};

hashtable *lookup(hashtable *table[], char *name);
uint32_t hash(char *str);
hashtable *newitem(char *name, int value);
void additem(hashtable* table[], hashtable *newp);

int main(int argc, char *argv[])
{
	hashtable *symtab[NHASH];	/* a symbol table */
	additem(symtab, newitem("int", KEYWORD));
	additem(symtab, newitem("x", IDENTIFIER));
	printf("%x\n", (lookup(symtab, "x"))->value);

	return 0;
}


/* lookup: find name in symtab, with option create */
hashtable *lookup(hashtable *symtab[], char *name){
	int h;
	hashtable *sym;

	h = hash(name);
	for(sym = symtab[h]; sym != NULL; sym = sym->next)
		if(strcmp(name, sym->name) == 0)
			return sym;
	
	return NULL;
}

/* newitem: creates new item and allocates memory */
hashtable *newitem(char *name, int value){
	hashtable *newp;
	newp = (hashtable *)malloc(sizeof(hashtable));
	newp->name = name;
	newp->value = value;
	return newp;
}

/* additem: adds item to the table at hashed location*/
void additem(hashtable* table[], hashtable *newp){
	int h;
	h=hash(newp->name);
	newp->next = table[h];
	table[h] = newp;
}


/* hash: compute hash value of the string */
uint32_t hash(char *str){
	uint32_t h;
	unsigned char *p;
	h=0;
	for(p = (unsigned char *)str; *p != '\0'; p++)
		h = MULTIPLIER * h + *p;
	return h % NHASH;
}

