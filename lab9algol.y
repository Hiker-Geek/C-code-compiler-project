%{

/*
 *			**** CALC ****
 *
 * This routine will function like a desk calculator
 * There are 26 integer registers, named 'a' thru 'z'
 *
 */

/* This calculator depends on a LEX description which outputs either VARIABLE or INTEGER.
   The return type via yylval is integer 

   When we need to make yylval more complicated, we need to define a pointer type for yylval 
   and to instruct YACC to use a new type so that we can pass back better values
 
   The registers are based on 0, so we substract 'a' from each single letter we get.

   based on context, we have YACC do the correct memmory look up or the storage depending
   on position

   Shaun Cooper
    January 2015

   problems  fix unary minus, fix parenthesis, add multiplication
   problems  make it so that verbose is on and off with an input argument instead of compiled in
*/
/*
 *name of code: lab7algol.y
 *purpose of code: Implement the rules for Algol-C using AST tree
 *author's name: Jessica Stein
 *date: 4/28/2022
 *algorithm description:
        *input: strings of code
        *output: Valid code will return "done parsing" and the print routine at the end of the written program and invalid code will return "syntax error" and the line number where the first error is spotted, and the program will exit.
        *assumptions about input: none
*/


	/* begin specs */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "ast.h"
#include "emit.h"
#include "symtable.h"
#include "y.tab.h"
#include <string.h>

struct ASTNode * Program=NULL;//gloabal var of tree

int yylex();/*initialize lex*/
extern int lineno;/*keeps track of line number*/
extern int mydebug;/*debugs program*/
int level=0; /*static scope level*/
int offset=0; /*offset from activation record*/
int goffset=0; /*offset from main activation, used to hold where we are when we jump into and out of function*/
int maxoffset;
int val=1;
#define FUNCTION_MIN_SIZE 2
/*
 * Pre: when program is parsing strings of code will be passed to yyerror
 * Post: if an error is found the location of that error will be returned
*/
void yyerror (s)  /* Called by yyparse on error */
     char *s;
{
  fprintf(stderr, "%s on line %d\n", s, lineno); /*prints line number of error*/
}


%}
/*  defines the start symbol, what values come back from LEX and how the operators are associated  */

%start program /*start program instead of iterating through list*/

/*
function: %union
Pre: none
Post: allows lex to return integer or 'char *' */
%union{
	int value;
	char *string;
	struct ASTNode * astnode;
	enum A_OPERATORS op;
}
%token <value> T_NUM /*integer accepts a numeric value*/
%token <string> T_ID T_QUOTED_STRING/*a variable will be identified as a string*/
%token T_INT T_VOID T_BOOLEAN T_END T_BEGIN T_OF T_IF T_THEN T_ELSE T_READ 
%token T_RETURN T_WRITE T_WHILE T_DO T_AND T_OR T_TRUE T_FALSE T_NOT T_MULTIPLY T_DIVIDE T_ADD T_SUBTRACT 
%token T_LE T_LT T_GT T_GE T_EQ T_NEQ /*token for declaring int variables*/
%type<astnode> declaration_list declaration var_declaration var_list fun_declaration param param_list params statement statement_list read_stmt write_stmt 
%type<astnode> return_stmt iteration_stmt selection_stmt local_declarations compound_stmt assignment_stmt var expression expression_stmt
%type<astnode> additive_expression simple_expression term factor args arg_list call
%type<op> type_specifier addop relop multop
%left '|'
%left '&'
%left '+' '-'
%left '*' '/' '%'
%left UMINUS


%%	/* end specs, begin rules */

program :	declaration_list{ Program = $1;} /* Program -> Declaration-list*/
	;

declaration_list : 	declaration{$$=$1;}
		| 	declaration declaration_list{$$=$1; $1 -> next=$2;}
		;
/*can declare variables and functions*/
declaration : 	var_declaration {$$ = $1;}
	    | 	fun_declaration {$$=$1;}
	;

/*declare a variable*/
var_declaration : type_specifier var_list ';'{
			/*need to update the type in varlist and pass up to parent*/
			$$=$2;
			struct ASTNode *p;
			p = $2;
			while(p!=NULL){
				p->op=$1;
				p->symbol->Type=$1;
				p=p->s1;
			}/*end while*/
		}
		;

/*types of variables that can occur*/
var_list : 	T_ID{	struct SymbTab *p;
	 		 /*Insert if OK, then ass the pointer from insertion into the ASTnode to have reference to the symbol tbale entry*/
	 		if(Search($1, level, 0)==NULL){
	 			$$=ASTCreateNode(A_VARDEC);
				$$->symbol=Insert($1, 0, 0, level, 1, offset);
	 			$$->name=$1;/*this changes to symbol table*/
				offset += 1;/*increment offset*/
				
			}
			else{
				yyerror($1);
				yyerror("symbol table already in use ");
				exit(1);
			}
		}
	| 	T_ID '[' T_NUM ']' {
			struct SymbTab *p;
			/*Insert if OK, then ass the pointer from insertion into the ASTnode to have reference to the symbol tbale entry*/
			if(Search($1, level, 0)==NULL){/*we did not find the anme before, so we can insert it*/
				$$=ASTCreateNode(A_VARDEC);
				$$->symbol=Insert($1, 0, 2, level, $3, offset);
				$$->size=$3; /*remember dimension*/
				$$->name=$1;/*this changes to symbol table*/
				offset += $3;
			}
			else{
				yyerror($1);
				yyerror("symbol already used ");
				exit(1);
			}
		}
	| 	T_ID ',' var_list {
			 struct SymbTab *p;
			 /*Insert if OK, then ass the pointer from insertion into the ASTnode to have reference to the symbol tbale entry*/
                        if(Search($1, level, 0)==NULL){
                                $$=ASTCreateNode(A_VARDEC);
                                $$->symbol=Insert($1, 0, 0, level, 1, offset);
                                $$->name=$1;/*this changes to symbol table*/
				$$->s1=$3;/*this changes to symbol table*/
				offset += 1;/*increment offset*/
                        }
			else{
                                yyerror($1);
                                yyerror("symbol table already in use ");
                                exit(1);
                        }

		}
	| 	T_ID '[' T_NUM ']' ',' var_list{
			struct SymbTab *p;
			if(Search($1, level, 0)==NULL){/*we did not find the name before, so we can insert it*/
				$$=ASTCreateNode(A_VARDEC);
				$$->symbol=Insert($1, 0, 2, level, $3, offset);
				$$->name=$1;/*this changes to symbol table*/
                                $$->size=$3;/*remember dimensions*/
				$$->s1=$6;/*this changes to symbol table*/
				offset += $3;
			}
		}
	;

/*types of variables and functions*/
type_specifier: T_INT {$$=A_INTTYPE;}
	| 	T_VOID {$$=A_VOIDTYPE;}
	| 	T_BOOLEAN {$$=A_BOOLTYPE;}
	;

/*can declare functions*/
fun_declaration : type_specifier T_ID '('{/*we are defining a function, we need to check the name and reset the offsets. 
					We allow params productions rule to insert a pointer to the AST tree for the formal parameters.
					We need to do this because inside the compound statement we may need to know the type and length fo the formals.
					If we wait to update the symbol table after the compound statement then the checking of a recursive call will not
					know the parameter length, etc.
					Effectively, we update the symbol table to point to the formal parameters.*/

					/*if we have seen the name, then we need to error. If not, we remember the global offset.*/
					
					if(Search($2, level, 0)==NULL){
						Insert($2, $1, 1, level, 0, 0);
						goffset=offset;
						offset=FUNCTION_MIN_SIZE;
						maxoffset=0; 
					}
					else{
						yyerror($2);
						yyerror("name already used ");
						exit(1);
					}
					
				}
	       	params{
		/*update the symbol table to have a pointer to the formal parameters*/
			(Search($2, 0, 0))->fparms=$5;
		}
 		')' compound_stmt{
			$$=ASTCreateNode(A_FUNDEC);
			$$->name=$2;
			$$->op=$1;/*rememeber the declaration type*/
			$$->s1=$5; /*the parameter list*/
			$$->calctype=$1;/*remember type declaration type*/
			$$->symbol=Search($2, 0, 0);/*go get the symbol table entry*/
			$$->s2=$8;/*compound statement*/
			$$->symbol->mysize = maxoffset;	
			offset=goffset;
		}
		;

/*parameters for functions*/
params : T_VOID{$$=NULL;}
       | param_list{$$=$1;}
	;

/*a function van have one or more parameters set*/
param_list: param{ $$=$1;}

	  | param ',' param_list{
                        $$=$1;
			$$->next=$3;}

	;

/*types of parameters that can be declared*/
param : 	type_specifier T_ID {/*symbol table function level add/check*/
      			if(mydebug) Display();
			 if(Search($2, level+1, 0)==NULL){
			 	$$=ASTCreateNode(A_PARAM);
				$$->name=$2;
				$$->op=$1;
				$$->calctype=$1;
				$$->symbol=Insert($2, $1, 0, level+1, 1, offset);
				mydebug && printf("in param insert %s %d\n", $2, level+1);

				if(mydebug) Display;
				$$->size=0;/*not an array*/
				offset+=1;

			}
			else{
				yyerror($2);
				yyerror("symbol already used ");
				exit(1);
			}
		}
      | 	type_specifier T_ID '[' ']'{
			 if(mydebug) Display();
                         if(Search($2, level+1, 0)==NULL){
                                $$=ASTCreateNode(A_PARAM);
                                $$->name=$2;
                                $$->op=$1;
                                $$->calctype=$1;
                                $$->symbol=Insert($2, $1, 2, level+1, 1, offset);
				mydebug && printf("in param insert %s %d\n", $2, level+1);

                                if(mydebug) Display;
                                $$->size=0;/*not an array*/
				offset+=1;
                        }
                        else{
                                yyerror($2);
                                yyerror("symbol already used ");
                                exit(1);
                        }
		}
      ;

/*language requires for the beginning and ending of a routine to be declared*/
compound_stmt : T_BEGIN {level++;}
	      		local_declarations 
			statement_list 
		T_END{
			$$=ASTCreateNode(A_BLOCK);
			$$->s1=$3;
			$$->s2=$4;
			
			Display();
			if(offset>maxoffset) maxoffset=offset; 
			offset=offset-Delete(level);
			level--;}
	      ;

/*local declarations*/
local_declarations: var_declaration local_declarations {$$=$1; $$->next=$2;}
		 |	/*empty*/{$$ = NULL;}
		 ;

/*zero or more statments can occur*/
statement_list : /*empty*/{$$=NULL;}
	       | statement statement_list{$$=$1; $$->next=$2;}
		;

/*language statement types include expression, compund, selection, iteration, assignment, return, read, and write*/
statement : expression_stmt{$$=$1;}
	  | compound_stmt {$$=$1;}
	  | selection_stmt{$$=$1;}
          | iteration_stmt{$$=$1;}
          | assignment_stmt{$$=$1;}
          | return_stmt{$$=$1;}
	  | read_stmt{$$=$1;}
          | write_stmt{$$=$1;}
	  ;

/*can be an expression or a semi-colon to end the code line*/
expression_stmt : expression ';' {$$=ASTCreateNode(A_EXPR);
					$$->s1=$1;
				}
				
                | ';'{$$=ASTCreateNode(A_EXPR);}  
                ;

/*selection statements are branching statements of if, them, and else types*/
selection_stmt	: T_IF expression T_THEN statement T_ELSE statement {
	       								
	       								$$=ASTCreateNode(A_IF);
	       								$$->s1=$2;
									$$->s2=ASTCreateNode(A_THEN);
									$$->s2->s1=$4;
									$$->s2->s2=$6;
									
								} 
	        | T_IF expression T_THEN statement{$$=ASTCreateNode(A_IF);
							$$->s1=$2;
							$$->s2=ASTCreateNode(A_THEN);
							$$->s2->s1=$4;
							
					} 
           	;

/*language rule for an iterative loop, which only includes a while statement, not a for statement*/
iteration_stmt : T_WHILE expression T_DO statement {$$=ASTCreateNode(A_WHILE);
	       						$$->s1=$2;
							$$->s2=$4;
						} 
               ;

/*can return a result or can return nothing*/
return_stmt : T_RETURN expression ';'{$$=ASTCreateNode(A_RETURN);
	    				 $$->s1=$2;
					} 
            | T_RETURN ';'{$$=ASTCreateNode(A_RETURN);} 
            ;

/*read just reads variables*/
read_stmt :  T_READ var ';'{$$=ASTCreateNode(A_READ); 
	  			$$->s1=$2; 
			} 
          ;

/*write just writes an expression into memory*/
write_stmt : T_WRITE expression ';'{$$=ASTCreateNode(A_WRITE);
	                                $$->name = NULL;
	   				$$->s1=$2;
					} 
	   | T_WRITE T_QUOTED_STRING ';' {$$=ASTCreateNode(A_WRITE);/*4/21/22 with addition of T_QUOTED_STRING write supports writing strings*/
					$$->name=$2;
					$$->label=GenerateLabel();
					}
           ;

/*assign a value to a variable, most likely an integer or boolean type*/
assignment_stmt : var '=' simple_expression ';'{
						if($1->calctype!=$3->calctype){
							yyerror(" assignment types do not match ");
							exit(1);
						}
						$$=ASTCreateNode(A_ASSIGN);
						/*Assignment statement we leave left alone so that it can be strung with other statements*/
							$$->s1=$1;
							$$->s2=$3;
							$$->name=CreateTemp();
							$$->symbol=Insert($$->name,A_INTTYPE,0,level,1,offset);
							offset++;
						} 
		;

/*expression piggy backs off simple_expression*/
expression : simple_expression {$$=$1;}
	   ;

var : T_ID {
    		/*we want to create a NODE called IDENTIFIER with a pointer to the SYMBOL table*/
		struct SymbTab *p;
		if((p=Search($1, level, 1)) != NULL) {
    			$$=ASTCreateNode(A_IDENT); 
    			$$->name=$1; /*change this to pointer to symbol table*/
			$$->symbol=p;
			$$->calctype=p->Type;
			printf("Type for VAR is %d\n", p->Type);
			if(p->IsAFunc != 0){ /*changed on 4/11/2022 to handle cases when a scalar is passed that shouldn't be passed*/
				yyerror($1);
				yyerror("variable is not a scalar, syntax error ");
				exit(1);
			}
		}
		else{
			yyerror($1);
			yyerror("undeclared variable ");
			exit(1);
		}
	}/*print name of ID whenever encountered*/
    | T_ID '[' expression ']'{	
				struct SymbTab *p;
				if((p=Search($1, level, 1)) != NULL){
					$$=ASTCreateNode(A_IDENT);
					$$->name=$1;/*change this to pointer to symbol table*/
					$$->s1=$3;
					$$->calctype=p->Type; /*inherit the type*/
					$$->symbol=p;
					if(p->IsAFunc != 2){/*changed on 4/11/2022 for clarity and ensurance that symbol always points to p*/
						yyerror($1);
						yyerror("not an array, type mismatch");
						exit(1);
					}
			     	}
				else{
					yyerror($1);
					yyerror("undeclared variable ");
					exit(1);
				}
			}
    ;

/*simple expression is either additive expression or an equality relationship statement between two additive ecpressions*/
simple_expression : additive_expression{$$=$1;}
                  | additive_expression relop additive_expression{ /*type checking*/
									if($1->calctype != $3->calctype){
										yyerror(" additive type mismatch ");
										exit(1);
									}
									$$=ASTCreateNode(A_EXPR);
									$$->s1=$1;
									$$->op=$2;
									$$->s2=$3;
									$$->calctype=$3->calctype;
									$$->name=CreateTemp();
									$$->symbol=(Insert($$->name, A_INTTYPE, 0, level, 1, offset));
									offset++;
								}
                  ;

/*relop means relational operators*/
relop   : T_LE {$$=A_LE;}
        | '<' {$$=A_LT;}
        | '>' {$$=A_GT;}
        | T_GE {$$=A_GE;}
        | T_EQ {$$=A_EQ;}
        | T_NEQ {$$=A_NEQ;}
        ;

/*numbers, bookeans, expressions, and variables are called or called to add or subtract with*/
additive_expression : term{$$=$1;}
                    | additive_expression addop term {
							/*type checking*/
							if($1->calctype != $3->calctype){
								yyerror(" additive expression type mismatch ");
								exit(1);
							}
							$$=ASTCreateNode(A_EXPR);
							$$->s1=$1;
							$$->op=$2;
							$$->s2=$3;
							$$->name=CreateTemp();
							$$->calctype=A_INTTYPE;
							$$->symbol=Insert($$->name, A_INTTYPE, 0, level, 1, offset);
							offset++;
							}
                    ;

/*addop is addition and subtraction*/
addop   :       '+' {$$=A_PLUS;}
        |       '-' {$$=A_MINUS;}
        ;

/*term is a factor or a factor with a multiplication or division operation, or setting up for a conditional statement*/
term    :       factor {$$=$1;}
                 /*4/1/2022 changed node type to A_EXPR as A_TERM was unnecessary when A_EXPR already handles complex cases like this in ASTprint*/
        |       term multop factor{			 /*type checking*/
                                                        if($1->calctype != $3->calctype){
                                                                yyerror(" additive expression type mismatch ");
                                                                exit(1);
                                                        }
							if(($2==A_TIMES || $2==A_DIVIDE)&& $1->calctype!=A_INTTYPE){
								yyerror(" term and multop type mismatch TIMES/DIVIDE");
								exit(1);
							}
							if(($2==A_AND || $2==A_OR) && $1->calctype!=A_BOOLTYPE){
								yyerror(" term and multop type mismatch AND/OR");
                                                                exit(1);
	
							}
                                                        $$=ASTCreateNode(A_EXPR);
                                                        $$->s1=$1;
                                                        $$->op=$2;
                                                        $$->s2=$3;
                                                        $$->name=CreateTemp();
                                                        $$->calctype=A_INTTYPE;
                                                        $$->symbol=Insert($$->name, A_INTTYPE, 0, level, 1, offset);
							offset++;
                                        }
        
;

/*multop is multiplication and division, or conditional statement combining two terms or having to choose between two terms occurring*/
multop  :       '*' {$$=A_TIMES;}
        |       '/' {$$=A_DIVIDE;}
        |       T_AND{$$=A_AND;} 
        |       T_OR{$$=A_OR;}
        ;

/*factors include numbers, variables, expressions, boolean values, or setting up for a conditional/relationship statement where it must specifically be NOT something*/
factor  :       '(' expression ')' {$$=$2;}
	|       T_NUM {$$=ASTCreateNode(A_NUM);
			$$->value=$1;
			$$->calctype=A_INTTYPE;
			}
        |       var {$$=$1;} 
	|	call {$$=$1;}
        |       T_TRUE {$$=ASTCreateNode(A_BOOL);
				$$->value=1;
				$$->TF=true;
				$$->calctype=A_BOOLTYPE;
			}
        |       T_FALSE {$$=ASTCreateNode(A_BOOL);
				$$->value=0;
				$$->TF=false;
				$$->calctype=A_BOOLTYPE;
			}
        |       T_NOT factor {
				 if($2->calctype != A_BOOLTYPE){
                                                                yyerror(" additive expression type mismatch ");
                                                                exit(1);
                                                        }

				$$=ASTCreateNode(A_EXPR);
				$$->name=CreateTemp();
				$$->symbol=Insert($$->name,A_INTTYPE,0,level,1,offset);
				$$->op=A_NOT;
				$$->s1=$2;
				offset++;
				}
        ;

/*call is never types out, but instead includes calling functions like so: foo(9) or doo()*/
call	:	T_ID '(' args ')' {
     				struct SymbTab *p;
				if((p=Search($1, 0, 0)) != NULL){
					if(p->IsAFunc != 1){
						yyerror($1);
						yyerror("Function name not defined ");
						exit(1);
					}
				/*now we check that the parameter list of the function are the same as the argument list*/
					if(CompareFormals(p->fparms, $3) != 1){
						yyerror($1);
						yyerror("parameter type or in-length mismatch between formals and actuals ");
						exit(1);
					}
     					$$=ASTCreateNode(A_CALL);
					$$->name=$1;
					$$->s1=$3;
					$$->calctype=p->Type;
					$$->symbol=p;
				}
				else{/*symbol not found*/
					yyerror($1);
					yyerror("Function name not defined ");
					exit(1);
				}
			}
     	;

/*outlines what arguments will be passed to the parameters of a function when called*/
args	:	{$$=NULL;}
     	|	arg_list{$$=$1;}
	;

/*arguments to be passed include an expression or a list of expressions (types are outlined in 'factor' rule, bust can be a variable, boolean value, number, expression of some kind, or specifically not something)*/
/*on 4/1/2022 node type changed to A_ARGS as the arguments passed needs to be pointed out in ASTprint output*/
arg_list : 	expression{
	 			$$=ASTCreateNode(A_ARGS);
	 			$$->s1=$1;
				$$->calctype=$1->calctype;
				$$->next=NULL;
				$$->name=CreateTemp();
                                $$->symbol=Insert($$->name,A_INTTYPE,0,level,1,offset);
                                offset++;
	
			}
	 |	expression ',' arg_list{
						$$=ASTCreateNode(A_ARGS); 
						$$->s1=$1;
						$$->calctype=$1->calctype;
						$$->next=$3;
						$$->name=CreateTemp();
						$$->symbol=Insert($$->name,A_INTTYPE,0,level,1,offset);
						offset++;
					}
	 ;

%%	/*end of rules, start of program */

/*begin parsing*/
/*
*PRE: arguments from command line, and an algol c file to parse
*POST: an asm output file and possibly ast tree and symbol table for debugging
*/
int main(int argc, char *argv[])
{ 
	int c = 1;
	FILE *fp=NULL;
	char s[100];

	while(c<argc){/*while there are still arguments to be passed*/
		if(strcmp(argv[c], "-d")==0) mydebug = 1;/*with inclusion of -d in command line mydebug is set to 1*/
		if(strcmp(argv[c], "-o")==0){/*if -o is included name the file, create an asm file named what comes after the o*/
			strcpy(s, argv[c+1]);
			strcat(s, ".asm");
			fp = fopen(s, "w");
			if(fp==NULL){
				printf("Can't open %s\n", s);
				exit(1);
			}
		}
	c++;/*iterate through command line argument*/
	}
	if(fp==NULL){/*didn't provide a file name for the asm file*/
		printf("Must provide a -o file name\n");
		exit(1);
	}
	
	yyparse();
	if(mydebug){/*if mydebug is set to one, then we print the ast tree and the symbol table*/
		printf("\n\nparsing complete\n");
		Display();
		ASTprint(0, Program);
	}
	/*following code runs emit.c to create an .asm file from algol code*/
	emit_header(Program, fp);
	emit_ast(Program, fp);
}
