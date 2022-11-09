/*   Abstract syntax tree code

     This code is used to define an AST node, 
    routine for printing out the AST
    defining an enumerated type so we can figure out what we need to
    do with this.  The ENUM is basically going to be every non-terminal
    and terminal in our language.

    Shaun Cooper February 2022

*/

/*
 *name: ast.c
 *purpose: outline specifics for ASTCreateNode and implement a print function for debugging with several helper functions 
 * Author name: Jessica Stein
 * Description:
 *	input: code from .al file
 * 	output: print routine and error messages where necessary
 * Date: 4/28/2022
 * */

#include <stdio.h>
#include "ast.h" 
#include <stdlib.h>
#include <malloc.h>
#include <stdbool.h>


//PRE: ASTNodeType
//POST: ptr to ASTnode from heap with all links set to NULL
//	MyType is set to my_type
/* uses malloc to create an ASTnode and passes back the heap address of the newley created node */
struct ASTNode * ASTCreateNode(enum ASTNodeType mytype)
{
    struct ASTNode *p;
    p = (struct ASTNode *)malloc(sizeof(struct ASTNode));
    if (mydebug) fprintf(stderr,"Creating AST Node \n");
    p->istype=mytype;
    p->s1=NULL;
    p->s2=NULL;
    p->next=NULL;
    p->size=0;//record size in memory
    p->value=0;//record numeric values
    p->name="";
    p->TF=NULL;
    return(p);
}

/* 
 *PRE: integer
 *POST: prints number of tabs according to integer passed
 *
*/

void PT(int howmany)
{
	int i=0;
	while(i<howmany){//print howmany number of tabs
		printf(" ");
		i++;
	}

}

// PRE: ptr to ASTNode
// POST: formatted output of the AST
/*  Print out the abstract syntax tree */
void ASTprint (int level, struct ASTNode *p)
{
   if (p == NULL ) return;
   else
     { 
      PT(level); //indent
      switch (p->istype) {//make settings for all types/cases of ASTNode
        case A_VARDEC : //variable declaration
		PT(level);	
		printf("Variable ");
		ASTprintOp(p->op);//get the operators
		printf(" %s ",  p->name);
		if(p->size > 1)//do we have an array
			printf("[%d] ", p->size);
		printf("has offset %d", p->symbol->offset);
		printf("\n");
		//call recursively
		ASTprint(level, p->s1);
		ASTprint(level, p->next);
                break;
       case A_FUNDEC : //function declaration
		   ASTprintOp(p->op);
		   printf(" FUNCTION %s size %d\n", p->name, p->symbol->mysize);
		   PT(level+2);
		   printf("symbol table name %s offset %d level %d\n", p->symbol->name, p->symbol->offset, p->symbol->level);
		   PT(level+2);
		   printf("(");
		     if(p->s1==NULL){//check if s1 is void type
			     printf("VOID");
			}
		     else{//it wasn't void
			     printf("\n");
			     ASTprint(level, p->s1); // print out the block
			     PT(level+2);
			}
		     printf(")\n");
		     ASTprint(level+2, p->s2);//compound statement
		     ASTprint(level, p->next);
                    break;
        case A_BLOCK : //block statement beginning to end
                        printf("BLOCK STATEMENT \n");
                        PT(level+1);
                        printf("BEGIN\n");
                        ASTprint(level+1, p->s1);
                        ASTprint(level+1, p->s2);
                        PT(level+1);
                        printf("END\n");
                        ASTprint(level, p->next);
                        break;

        case A_PARAM :  PT(level+3); //pass parameters
		    	printf("PARAMETER ");
 		        ASTprintOp(p->op);
			printf(" %s", p->name);
			printf("\n");
      			ASTprint(level, p->next);			
                     break;
       case A_READ : //read statement
			PT(level+2);
                        printf("READ\n");
                        ASTprint(level+1, p->s1); //VAR
			ASTprint(level, p->next);//statement next connected
                        break;
	case A_IDENT : //identifier for variables
			level = level+3;
			PT(level);
                        printf("IDENTIFIER %s has offset %d\n", p->name, p->symbol->offset);
			if(p->s1 != NULL){//we have an array
				PT(level*2+3);
				printf("Array Reference [\n");
                        	ASTprint(level+3, p->s1); //VAR
				PT(level*2+3);
				printf("] end array\n");
			}
                        break;
	case A_NUM : 	PT(level+3); //report numeric values
			printf("Number with value %d\n", p->value);
			ASTprint(level+1, p->s1);
			break;
	case A_WRITE : //write statements
			PT(level+2);
			printf("WRITE STATEMENT\n");
			ASTprint(level+1, p->s1);
			ASTprint(level, p->next);
			break;
	case A_RETURN : //return statement
			PT(level+1);
                        printf("RETURN STATEMENT\n");
                        ASTprint(level+1, p->s1);
                        ASTprint(level, p->next);
                        break;
	case A_EXPR: //expressions
			PT(level + 3);
			printf("EXPRESSION ");
			if(p->s1==NULL)//s1 is null
				printf("empty");
			else//s1 not null
				ASTprintOp(p->op);
			printf("\n");
			ASTprint(level+3, p->s1);
			if(p->op != A_NOT)//we do not have a not statement
				ASTprint(level+3, p->s2);
			ASTprint(level+3, p->next);
			break;
	case A_BOOL: //boolean
			PT(level+3);
			printf("BOOLEAN of type %s\n", p->TF ? "true" : "false");
			break;
	case A_CALL: //call functions
			PT(level+2);
			printf("CALL %s", p->name);
			printf("( \n");
			ASTprint(level, p->s1);
			printf("\n");
			PT(level*2);
			printf(" )END CALL\n");
			ASTprint(level, p->next);
			break;
	case A_ASSIGN: //assign values
			PT(level+2);
			printf("ASSIGNMENT\n");
			ASTprint(level, p->s1);
			printf("\n");
			ASTprint(level, p->s2);
			printf("\n");
			ASTprint(level, p->next);
			break;
       case A_WHILE :  //while statement
			PT(level+2);
			printf("WHILE STATEMENT \n");
                     	ASTprint(level+2, p->s1);
		     	printf("\n");
                     	ASTprint(level+2, p->s2);
		     	printf("\n");
		     	ASTprint(level, p->next);
                     	break;
	case A_IF : //if statement
		     	PT(level+2);
		     	printf("IF STATEMENT \n");
		     	ASTprint(level+1, p->s1);
		     	ASTprint(level+1, p->s2);
		     	ASTprint(level+1, p->next);
		     	break;
	case A_THEN : //then statement
		     	PT(level+2);
		     	printf("THEN STATEMENT \n");
		     	ASTprint(level+1, p->s1);
			printf("\n");
			PT(level+5);
			if(p->s2 != NULL){//there is something in the else statement we must do
				//PT(level+);
				printf("ELSE STATEMENT\n");
		     		ASTprint(level+1, p->s2);
			}
			ASTprint(level, p->next);
		     	break;
	case A_ARGS : 
			PT(level+1);
		      	printf("ARGUMENTS\n");
		      	ASTprint(level+1, p->s1);
		      	ASTprint(level+1, p->next);
			break;

	default:  fprintf(stderr, "WARNING UNKNOWN type in ASTprint\n");
                   fprintf(stderr, "WARNING FIX FIX FIX\n");
       }
     }

}

/*
 *PRE: enum A_OPERATORS
 *POST: print out the name of the operator
 */
void ASTprintOp(enum A_OPERATORS myOp){
	switch(myOp){//handle the operator types and print them out
		default: 
			fprintf(stderr, "FIX FIX ASTPrint Operator\n");
		case A_INTTYPE : printf("INT");
				break;
		case A_VOIDTYPE : printf("VOID");
				  break;
		case A_BOOLTYPE : printf("BOOLEAN");
				 break;
		case A_PLUS : printf("PLUS");
			      break;
		case A_MINUS : printf("MINUS");
			       break;
		case A_DIVIDE : printf("DIVIDE");
				break;
		case A_TIMES : printf("TIMES");
			       break;
		case A_AND : printf("AND");
			     break;
		case A_OR : printf("OR");
			    break;
		case A_LT : printf("LESS THAN");
			    break;
		case A_LE : printf("LESS THAN OR EQUAL");
                            break;
		case A_GT : printf("GREATER THAN");
                            break;
		case A_GE : printf("GREATER THAN OR EQUAL");
                            break;
		case A_EQ : printf("EQUAL TO");
                            break;
		case A_NEQ : printf("NOT EQUAL TO");
                            break;
		case A_NOT : printf("NOT");
			     break;

	}//of switch
}//of A_OP
/* dummy main program so I can compile for syntax error independently   
int main()
{ 
}
}/* */
