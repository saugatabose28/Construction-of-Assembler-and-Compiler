#include "global.h"
#include<ctype.h>
#include<string.h>
#include<stdio.h>

typedef enum {_START,_IDENT,_INIDENT,_EOF,_INT,_ININT,_EOL,_OTHER,} state;


static char curchar;
static char nextchar;
static char *p=NULL;
static int c=0;

static char
getch(){
	static int firsttime=1;
	if(firsttime){
		firsttime--;
		if((p=fgets(yyline,BUFSIZ,yyin))!=NULL){
			c=1;
			nextchar=*(p+1);
			return (curchar =*p);
		}
		else
			error("null input file\n",PANIC);
	}
	if(nextchar=='\0')
		return(curchar=nextchar='\0');
	c++;
	nextchar=*(p+2);
	return (curchar=*++p);
}

int yygettoken(){
	static int firsttime=1;
	state curstate;
	int i,done;
	
	if(firsttime){
		getch();
		firsttime--;
	}
	
	curstate=_START;
	yytext[0]='\0';
	done =0;

	while(!done){
		switch(curstate){
			case _START:
				yycolumn=c;
				if(curchar==' ' || curchar=='\t')
					;
				else if(curchar=='\0'){
					curstate=_EOF;
					done++;
				}
				else if(curchar=='\n'){
					curstate=_EOL;
					strncat(yytext,&curchar,1);
					getch();
					done++;
				}
				else if(isalpha(curchar)){
					strncat(yytext,&curchar,1);
					curstate=_INIDENT;
				}
				else if(isdigit(curchar)){
					strncat(yytext,&curchar,1);
					curstate=_ININT;
				}
				else{
					strncat(yytext,&curchar,1);
					getch();
					curstate=_OTHER;
					done++;
				}
				break;
			case _INIDENT:
				if(isalnum(curchar)){
					strncat(yytext,&curchar,1);
					break;
				}
				curstate=_IDENT;
				done++;
				break;
			case _ININT:
				if(isdigit(curchar)){
					strncat(yytext,&curchar,1);
					break;
				}
				curstate=_INT;
				done++;
		}
		if(!done){
			getch();
		}
	}
	switch(curstate){
		case _EOF:
			return EOFILE;
		case _EOL:
		case _OTHER:
			return yytext[0];
		case _IDENT:
			if(lookup(yytext)==-1)
				insert(yytext,NONLITERAL);
			else
				return IDENT;
		case _INT:
			if(lookup(yytext)==-1)
				insert(yytext,LITERAL);
			else
				return INTEGER;
			
	}
}
