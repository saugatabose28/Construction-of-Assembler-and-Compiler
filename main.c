#include "global.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define STACK 100

int opandstk[STACK],optorstk[STACK];
int topoptor=-1,topopand=-1;
int curtoken;

stmts(){
	if(curtoken=='\n' || curtoken==EOFILE)
		return 1;
	if(curtoken==IDENT){
		if(stmt())
			if(stmts())
				return 1;
	}
	error("end of file or end of line or identifier expected.",PANIC);
}
stmt(){
	int rhs;
	if(curtoken==IDENT){
		pushopand(lookup(yytext));
		curtoken=yygettoken();
		if(curtoken=='='){
			pushoptor(ASSIGN);
			curtoken=yygettoken();
			if(express()){
				if(curtoken==';'){
					curtoken=yygettoken();
					rhs=popopand();
					emit(popoptor(),popopand(),rhs);
					return 1;
				}
				error("';' expected.",PANIC);
			}
			
		}
		error("'=' expected.",PANIC);
	}
	error("identifier expected.",PANIC);
}
express(){
	if(curtoken==IDENT || curtoken==INTEGER || curtoken=='('){
		if(term() && expresses())
			return 1;
	}
	error("identifier,integer or '(' expected.",PANIC);
}
expresses(){
	int lhs,rhs,temp;
	if(curtoken==')' || curtoken==';')
		return 1;
	if(curtoken=='-' || curtoken=='+'){
		if(curtoken=='-')
			pushoptor(SUB);
		else
			pushoptor(ADD);
		curtoken=yygettoken();
		if (term()){
			rhs=popopand();
			lhs=popopand();
			temp=mktmp();
			emit(ASSIGN,temp,lhs);
			emit(popoptor(),temp,rhs);
			pushopand(temp);
			if(expresses())
				return 1;
		}
	}
	error("')',';','-' or '+'expected.",PANIC);
}
term(){
	if(curtoken==IDENT || curtoken==INTEGER || curtoken=='(')
		if(factor() && terms())
			return 1;
	error("identifier,integer or '(' expected.",PANIC);
}
terms(){
	int lhs,rhs,temp;
	if(curtoken=='/' || curtoken=='*'){
		if(curtoken=='/')
			pushoptor(DIV);
		else
			pushoptor(MULT);
		curtoken=yygettoken();
		if (factor()){
			rhs=popopand();
			lhs=popopand();
			temp=mktmp();
			emit(ASSIGN,temp,lhs);
			emit(popoptor(),temp,rhs);
			pushopand(temp);
			if(terms())
				return 1;
		}
		
	}
	else if(curtoken=='-' || curtoken=='+'|| curtoken==')' || curtoken==';')
		return 1;
	error("'/','*','-','+',';'or ')'expected.",PANIC);
}
factor(){
	if(curtoken=='('){
		curtoken=yygettoken();
		if (express()){
			if(curtoken==')'){
				curtoken=yygettoken();
				return 1;
			}
			error("')' expected",PANIC);
		}
		
	}
	if(curtoken==INTEGER || curtoken==IDENT){
		pushopand(lookup(yytext));
		curtoken=yygettoken();
		return 1;
	}
	error("'(',integer or identifier expected",PANIC);
}
pushopand(i) int i;{
	if(++topopand==STACK)
		error("internal error: operand stack overflow",PANIC);
	opandstk[topopand]=i;
}
int 
popopand(){
	if(topopand==-1)
		error("internal error: operand stack underflow",PANIC);
	return (opandstk[topopand--]);
}
pushoptor(i) int i;{
	if(++topoptor==STACK)
		error("internal error: operator stack overflow",PANIC);
	opandstk[topoptor]=i;
}
int 
popoptor(){
	if(topoptor==-1)
		error("internal error: operator stack underflow",PANIC);
	return (opandstk[topoptor--]);
}
int 
mktmp(){
	static int seed=0;
	char name[BUFSIZ];
	sprintf(name,"-xxx%d",seed++);
	return (insert(name,NONLITERAL));
}
main(argc,argv) int argc;char *argv[];{

	char msg[BUFSIZ];
	char *sp;
	
	if(argc!=2){
		sprintf(msg,"usage: %s filename",argv[0]);
		error(msg,PANIC);
	}
	emit(TEXT,BLANK,BLANK);
	curtoken=yygettoken();
	if(stmts()){
		if(curtoken=='\n' || curtoken==EOFILE){
			curtoken=yygettoken();
			if(curtoken==EOFILE){
				emit(EXIT,insert("0"),BLANK);
				data();
			}
		}
	}
	else
		error("end of file or end of line expected.",PANIC);
	exit(0);
}

