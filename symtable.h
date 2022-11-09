/*  Symbol Table --linked list  headers
    Used for Compilers class

    Modified Spring 2015 to allow for name to pointed to by symtable, instead of copied, since the name is copied
    into the heap

    Modified to have levels.  A level 0 means global variable, other levels means in range of the function.  We
    start out our offsets at 0 (from stack pointer) for level 1,,,when we enter a functional declaration.
    We increment offset each time we insert a new variable.  A variable is considered to be valid if it is found in
    the symbol table at our level or lesser level.  If at 0, then it is global.  

    We return a pointer to the symbol table when a variable matches our creteria.

    We add a routine to remove variables at our level and above.
*/

/*
 * Author name: River Stein
 * Program name: symtable.h
 * Date: 4/28/2022
 * Purpose: define symbol table functions
 * Description:
 *	Input: code
 *	Output: none
 *	Assumptions: None
 *Changed: added more comments to identify what functions the prototypes belong to
 * */    


#ifndef _SYMTAB 
#define _SYMTAB

#include "ast.h"

extern int mem;
//prototype for Display
void Display();
//prototype for Delete
int Delete();
//prototype for CompareFormals
int CompareFormals();
//prototype for FetchAddr
int FetchAddr (char *lab);
//prototype for SymbTab
struct SymbTab
{
     char *name;
     int offset; /* from activation record boundary */
     int mysize;  /* number of words this item is 1 or more */
     int level;  /* the level where we found the variable */
     enum A_OPERATORS Type;  /* the type of the symbol */
     int IsAFunc;  /* the element is a function */
     struct ASTNode * fparms; /* pointer to parameters of the function in the AST */

     struct SymbTab *next;
};

//prototype for Insert
struct SymbTab * Insert(char *name, enum A_OPERATORS Type, int isafunc, int  level, int mysize, int offset);
//prototype for Search
struct SymbTab * Search(char name[], int level, int recur );


static struct SymbTab *first=NULL;   /* global pointers into the symbol table */
//prototype for CreateTemp
char * CreateTemp();



#endif

