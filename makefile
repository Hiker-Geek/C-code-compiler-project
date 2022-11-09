# *name of file: makefile
# *purpose of code: implement Algol C rules using AST
# *author's name: Jessica Stein
# *date: 4/28/2022
# *algorithm description:
#        *input: strings of code
#        *output: the actions specified in code will be performed in accordance to Algol C and MIPS rules including anything that must be returned. When turned on the debugger will identify the parts of the code. Valid code will return "done parsing" at the end of the written program and invalid code will return "syntax error" and the line number where the first error is spotted, and the program will exit.
#        *assumptions about input: none
# *changes made: deleted test case shortcuts


all:	lab9

#compile the program into an executable
lab9: lab9.l lab9algol.y ast.h symtable.c symtable.h ast.c emit.h emit.c
	yacc -d lab9algol.y
	lex lab9.l
	gcc -g -o lab9 lex.yy.c y.tab.c symtable.c ast.c emit.c
#run the program
run: 	lab9
	./lab9

#remove the program executable to 'clean' it
clean:
	rm -f y.tab.c
	rm -f y.tab.h
	rm -f lex.yy.c	
	rm -f lab9
	rm -f *.asm
