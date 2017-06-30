#include "global.h"
#include<stdlib.h>
#include<stdio.h>

int tabsize=0;

int
lookup(s) char *s;{
	register  int i;
	for(i=0;i<tabsize;i++)
		if(!strcmp(table[i].key,s))
			return i;
	return NOTFOUND;
}

int
insert(s,lit) char *s;int lit;{
	char *p;
	if(tabsize==TABSIZE)
		error("internal error: symbol table overflow",PANIC);
	p=(char *)malloc(strlen(s)+1);
	strcpy(p,s);
	table[tabsize].key=p;
	table[tabsize].literal=lit;
	return(tabsize++);
}

