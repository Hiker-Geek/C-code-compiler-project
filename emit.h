/*this is the emit.h file*/
/*
 *file name: emit.h
 *purpose: support emit.c in emitting MIPS code from given algol code and ast tree pointers
 *author name: Jessica Stein
 *Description:
                *input: pointer to astnode in tree and file name to print to
                *output: an assembly file with MIPS code
                *assumptions: none
 *Date: 4/28/2022
 * */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef EMIT_H
#define EMIT_H

#define WSIZE 4
#define WLOGSIZE 2
#include "ast.h"
#include "symtable.h"

//prototype for emit_call
void emit_call(struct ASTNode *p, FILE *fp);

//prototype for amit_args
void emit_args(struct ASTNode *p, FILE *fp);

//prototype for emit_header
void emit_header(struct ASTNode *p, FILE *fp);

//prototype for emit_global_strings
void emit_global_strings(struct ASTNode *p, FILE *fp);

//prototype for emit_global_variables
void emit_global_variables(struct ASTNode *p, FILE *fp);

//prototype for emit
void emit(char *label, char *command, char *comment, FILE *fp);

//prototype for emit_ident
void emit_ident(struct ASTNode *p, FILE *fp);

//prototype for emit_expr
void emit_expr(struct ASTNode *p, FILE *fp);

//prototyep for emit_ast
void emit_ast(struct ASTNode *p, FILE *fp);

//prototype for GenerateLabel
char * GenerateLabel();

//prototype for emit_write
void emit_write(struct ASTNode *p, FILE *fp);

//prototype for emit_function
void emit_function(struct ASTNode *p, FILE *fp);

//prototype for emit_assign
void emit_assign(struct ASTNode *p, FILE *fp);

//prototype for emit_read
void emit_read(struct ASTNode *p, FILE *fp);

//prototype for emit_while
void emit_while(struct ASTNode *p, FILE *fp);

//prototype for emit_if
void emit_if(struct ASTNode *p, FILE *fp);
#endif
