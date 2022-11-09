/*   Abstract syntax tree code


 Header file   
 Shaun Cooper January 2022

 * author name: Jessica Stein
 * file name: ast.h
 * file purpose: H header file for abstract syntax tree
 * Date: 4/28/22
 * Description:
 * 	Input: code
 * 	output: print routine and 'done parsing'
 * 	assumptions: none

*/

#include <stdio.h>
#include <malloc.h> 
#include <stdbool.h>
#include "symtable.h"
#ifndef AST_H
#define AST_H
extern int mydebug;

/* define the enumerated types for the AST.  THis is used to tell us what 
sort of production rule we came across */

//enum which allows us to distinguish which node type
enum ASTNodeType
{ 
	A_VARDEC,
	A_FUNDEC,
	A_READ,
	A_PARAM,
	A_EXPR,
	A_BLOCK,
	A_WHILE,
	A_NUM,
	A_WRITE,
	A_IDENT,
	A_RETURN,
	A_BOOL,
	A_CALL,
	A_IF,
	A_THEN,
	A_ASSIGN,
	A_ARGS

}; //end 

enum A_OPERATORS {
   A_PLUS,
   A_MINUS,
   A_TIMES,
   A_DIVIDE,
   A_BOOLTYPE,
   A_VOIDTYPE,
   A_INTTYPE,
   A_NOT,
   A_OR,
   A_AND,
   A_LE,
   A_LT,
   A_GT,
   A_GE,
   A_EQ,
   A_NEQ
};//end

/* define a type AST node which will hold pointers to AST structs that will
   allow us to represent the parsed code 
*/

//main stat structure of AST
struct ASTNode {
	enum ASTNodeType istype;
	enum A_OPERATORS op, calctype;
	char * name; 
	char * label;
	struct ASTNode *s1, *s2, *next;
	int size;
	int value;
	bool TF;
	struct SymbTab *symbol;

};
/*  Print out the abstract syntax tree */
void ASTprint(int level, struct ASTNode *p);

//prototype
struct ASTNode * ASTCreateNode(enum ASTNodeType mytype);

//prototype for ASTprintOp moved here on 4/29/22 for neatness
void ASTprintOp(enum A_OPERATORS);
#endif
