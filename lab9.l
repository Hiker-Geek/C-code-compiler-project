/*                 Small LEX routine which returns two formal tokens (INTEGER and VARIABLE)
                   along with single string elements like '+'.
 
                    This LEX definition is the companion to the docalc.y YACC routine which
                   is a simple calculator

                    Shaun Cooper
                    January 2015
*/

/*
 *name of file: lab9.l
 *purpose of code: handle tokens for implementating rules of ALGOL-C
 *author's name: Jessica Stein
 *date: 4/15/2022
 *algorithm description:
        *input: strings of code
        *output: the actions specified in code will be performed in accordance to Algol C rules including anything that must be returned.
        *assumptions about input: none
*/

%{

int mydebug=0;
int lineno=1;
#include "ast.h"
#include "y.tab.h"
%}


%%
 /*tokens for Algol C*/
int             { return(T_INT);}
void		{ return(T_VOID);}
boolean		{ return(T_BOOLEAN);}
begin		{ return(T_BEGIN);}
end		{ return(T_END);}
of		{ return(T_OF);}
if		{ return(T_IF);}
then		{ return(T_THEN);}
else		{ return(T_ELSE);}
read		{ return(T_READ);}
return		{ return(T_RETURN);}
write		{ return(T_WRITE);}
while		{ return(T_WHILE);}
do		{ return(T_DO);}
and		{ return(T_AND);}
or		{ return(T_OR);}
true		{ return(T_TRUE);}
false		{ return(T_FALSE);}
not		{ return(T_NOT);}
 /*equality relationship tokens*/
"=="		{ return(T_EQ);}
"!="		{ return(T_NEQ);}
"<="		{ return(T_LE);}
">="		{ return(T_GE);}
\".*\"		{ yylval.string=strdup(yytext);
		return(T_QUOTED_STRING);}


 /*accept an alphanumeric string of characters that starts with any alphabetic character as an ID name*/
 /*if mydebug is turned on, print message anytime an ID is found*/
[A-Za-z_][a-zA-Z0-9_]*	{if (mydebug) 
				fprintf(stderr,"ID found\n"); 
                       	yylval.string=strdup(yytext); 
			return(T_ID);
			}
 /*accept a numeric value of any length and print message 'digit found' when detected if debugger is turned on*/
[0-9][0-9]*	{ if (mydebug) 
			fprintf(stderr, "Digit found\n");
		yylval.value=atoi((const char *)yytext); 
		return(T_NUM);
		}
 /*do nothing if compiler comes across a tab*/
[ \t]		{	}

[-,;[\]/*+%&|<>()=] 	{ return (*yytext);} /*single tokens*/

 /*comment token. do nothing if a comment is spotten*/
\/\/.*		{ /* do nothing comment */}

 /*iterate the line number in the program and go to the next line if newline character is spotted*/
\n 		{ lineno++;}

%%

int yywrap(void)
{ return 1;}


