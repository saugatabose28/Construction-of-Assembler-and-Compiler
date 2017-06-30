#include<stdio.h>

typedef enum{PANIC} strategy;

#define IDENT 256
#define INTEGER 257
#define EOFILE 258
#define NONLITERAL 0
#define LITERAL 1
enum {SUB,ADD,DIV,MULT,END,TEXT,ASSIGN,EXIT,DATA} opcodes;
#define BLANK -1

char yytext[BUFSIZ];
FILE *yyin;
int yycolumn;
char yyline[BUFSIZ];
#define TABSIZE 100

struct entry{
	char *key;
	int literal;
	
}table[TABSIZE];
#define NOTFOUND -1
