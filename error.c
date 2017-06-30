#include<stdio.h>
#include<stdlib.h>
#include "global.h"

error(msg,recovery) char *msg;strategy recovery;{

	if(yycolumn)
		fprintf(stderr,"in column %d: \n",yycolumn);
	fprintf(stderr,"%s\n",msg);

	switch(recovery){
		case PANIC:
			exit(1);
		default:
			error("internal error- bad recovery\n",PANIC);
	}
}
