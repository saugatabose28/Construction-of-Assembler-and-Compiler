compile: error.o lex.o table.o code.o main.o
	cc -O -o compile error.o lex.o table.o main.o code.o
main.o: global.h
	cc -c -O main.c
code.o: global.h
	cc -c -O code.c
error.o:global.h
	cc -c -O error.c	
lex.o:	global.h
	cc -c -O lex.c
table.o: global.h
	cc -c -O table.c
