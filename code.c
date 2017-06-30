#include "global.h"
static char *optable[]={"sub","add","div","mult",".end",".text","assign","exit",".data"};

emit(opcode,op1,op2) int opcode,op1,op2;{
	printf("%-6s %-6s %-6s %-6s\n","",optable[opcode],op1==-1?"":table[op1].key,op2==-1?"":table[op2].key);
}
data(){
	register int i;
	emit(DATA,BLANK,BLANK);
	for(i=0;i<TABSIZE;i++)
		if(!table[i].literal)
			printf("%-6s %-6s\n",table[i].key,"int");
	emit(END,BLANK,BLANK);
}
