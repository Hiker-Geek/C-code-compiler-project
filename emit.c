
/*
 *file name: emit.c
 *purpose: emit MIPS code from given algol code and ast tree pointers
 *author name: Jessica Stein
 *Description:
 		*input: pointer to astnode in tree and file name to print to
		*output: an assembly file with MIPS code
		*assumptions: none
 *Date: 4/28/2022
 *Level to be graded at: undergraduate, on everything a-e on the rubric all the way up to function calls
*/

#include "emit.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "ast.h"
static int glabel= 0;
/*
 *PRE: pointer to node and file to print to
 *POST: create the header for every file in MIPS
 * */
void emit_header(struct ASTNode *p, FILE *fp){
	fprintf(fp, ".data #start of data section global strings\n\n");
	emit_global_strings(p, fp);
	fprintf(fp, "_NL: .asciiz \"\\n \"# New line\n");
	fprintf(fp, ".align 2 #start all global variables aligned\n\n");
	fprintf(fp, "#global variables\n");
	emit_global_variables(p, fp);
	fprintf(fp, "\n.text\n\n");
	fprintf(fp, ".globl main\n\n");
	
}//end emit header
/*
 *PRE: pointer to node and file to print to
 *POST: direct program to the correct AST node type and emit the correct MIPS routine for that node type
 * */
void emit_ast(struct ASTNode *p, FILE *fp){
	if(p==NULL) return;
	switch(p->istype){
		case A_VARDEC://varaible declaration
			emit_ast(p->next, fp);
			break;
		case A_FUNDEC://function declaration
			emit_function(p, fp);
			emit_ast(p->next, fp);
			break;
		case A_BLOCK://block statement
			emit_ast(p->s2, fp);
			emit_ast(p->next, fp);
			break;
		case A_EXPR://expression statement
			emit_expr(p, fp);
			emit_ast(p->next, fp);
			break;
		case A_WRITE://write statement
			emit_write(p, fp);
			emit_ast(p->next, fp);
			break;
		case A_IDENT://getting or declaring an identifier
			emit_ast(p->next, fp);
			break;
		case A_ASSIGN://assignment statement
			emit_assign(p, fp);
			emit_ast(p->next, fp);
			break;
		case A_READ://read statement
			emit_read(p, fp);
			emit_ast(p->next, fp);
			break;
		case A_WHILE://while statement
			emit_while(p, fp);
			emit_ast(p->next, fp);
			break;
		case A_IF://if then selection statement
			emit_if(p, fp);
			emit_ast(p->next, fp);
			break;
		case A_CALL://call to a function
			emit_call(p, fp);
			emit_ast(p->next, fp);
			break;
		case A_RETURN://return in a function--inclusion prevents errors, doesn't return anything
			emit_ast(p->next, fp);
			break;
		case A_ARGS://passing arguments to a function
			emit_args(p, fp);
			emit_ast(p->next, fp);
			break;
		default://indicates that something is broken in the program
			printf("emit_ast -- we should never be here");
			break;
	}//end switch

}
/*
 *PRE: pointer to node and file to write to
 *POST: assign a value to a variable in MIPS
 *
 * */
void emit_assign(struct ASTNode *p, FILE *fp){
	char s[100];//declare the command array for emitting commands
	emit_expr(p->s2, fp);//s2 holds the value to be assigned, so we go to emit_expr to handle it in MIPS code
        sprintf(s, "sw $a0, %d($sp)", p->symbol->offset*WSIZE);
        emit("", s, "store rhs value in memory", fp);
	emit_ident(p->s1, fp);//s1 holds the name of the identifier, so we go to emit_ident with s1 to get that name for MIPS
	sprintf(s, "lw $a1 %d($sp)", p->symbol->offset*WSIZE);
        emit("", s, "get rhs stored value", fp);
        emit("", "sw $a1 ($a0)", "ASSIGN final store", fp);//assignment command in MIPS
        fprintf(fp, "\n");
	return;
	
}
/*
 *PRE: pointer to node and file to write to
 *POST: call a function and return a value in MIPS
 * */
void emit_call(struct ASTNode *p, FILE *fp){
	char s[100];//declare the command array for emitting commands
	emit_ast(p->s1, fp);//get arguments
	sprintf(s, "subu $t0 $sp %d", p->symbol->mysize*WSIZE);
	emit("", s, "make $t0 sp the new function size", fp);
	int i = 8;//we start at 8 for memory
	for(struct ASTNode *arg = p->s1; arg; arg = arg->next){//iterating through ast pointer to pass all the arguments to MIPS   
	       	sprintf(s, "lw $t2 %d($sp)", arg->symbol->offset*WSIZE);
		emit("", s, "get value from rhs memory", fp);
		sprintf(s, "sw $t2 %d($t0)", i);
		emit("", s, "store rhs value", fp);
		i+=WSIZE;//iterate to create new space in memory for each argument
        }
	sprintf(s, "jal %s", p->name);
	emit("", s, "jump to parameter", fp);//once parameter arguments are created we jump to them
	
}

/*
 *PRE: pointer to node and file to write to
 *POST: emit the arguments to pass to a function call in MIPS
 * */
void emit_args(struct ASTNode *p, FILE *fp){
	char s[100];//declare the command array for emitting commands
	//for(struct ASTNode *arg = p->s1; arg; arg = arg->next){
        emit_expr(p->s1, fp);//get the argument types
	sprintf(s, "sw $a0 %d($sp)", p->symbol->offset*WSIZE);
	emit("", s, "store argument temporary", fp);

}
/*
 *PRE: pointer to node and file to write to
 *POST: create a while statement dependent on the outcome of an expression in MIPS
 * */

void emit_while(struct ASTNode *p, FILE *fp){
	char s[100];//declare the command array for emitting commands
	char *L1 = GenerateLabel();//create first label for while statement in MIPS
	char *L2 = GenerateLabel();//create second label for exiting while statement in MIPS
	emit(L1, "", "begin while loop", fp);//create loop label
	emit_expr(p->s1, fp);//get conditions for while loop
	sprintf(s, "beq $a0 $0 %s", L2);//check if conditions are still true
	emit("", s, "while branch out", fp);
	fprintf(fp, "\n");
	emit_ast(p->s2, fp);//get while loop contents--what it will do while in the loop
	fprintf(fp, "\n");
	sprintf(s, "j %s", L1);//do the loop again
	emit("", s, "while loop jump back", fp);
	emit(L2, "", "end while loop", fp);//create loop exit label
}
/*
 *PRE: pointer to node and file to point to
 *POST: create if then else routine in MIPS
 * */
void emit_if(struct ASTNode *p, FILE *fp){
	char s[100];//declare the command array for emitting commands
	char *L1 = GenerateLabel();//create first label for if then in MIPS
	char *L2 = GenerateLabel();//create second label for else in MIPS
	emit_expr(p->s1, fp);//get conditions for if statement from s1
	sprintf(s, "beq $a0 $0 %s", L1);//check if conditions are still true
	emit("", s, "if branch to else part", fp);
	fprintf(fp, "\n");
	emit_ast(p->s2->s1, fp);//s2 holds different ast node A_THEN, so point to A_THEN's s1 content for 'then expression'
	fprintf(fp, "\n");
	sprintf(s, "j %s", L2);
	emit("", s, "if s1 end", fp);
	fprintf(fp, "\n");
	emit(L1, "", "else target", fp);
	emit_ast(p->s2->s2, fp);//s2 holds different ast node A_THEN, so point to A_THEN's s2 content for 'else expression'
	fprintf(fp, "\n");
	emit(L2, "", "exit if statement", fp);
}
/*
 *PRE: pointer to node and file to point to
 *POST: create MIPS code for writing numbers and strings
 * */
void emit_write(struct ASTNode *p, FILE *fp){
	char s[100];//declare the command array for emitting commands
	if(p->name!=NULL){//if a string is in T_QUOTED_STRING
		emit("", "li $v0, 4", "print a string", fp);
		sprintf(s, "la $a0 %s", p->label);//get the string
		emit("", s, "print fetch string location", fp);
       	}
	else{//no string, it is a number we are writing
		emit_expr(p->s1, fp);//get the number
		emit("", "li $v0, 1", "print number", fp);
	}
	emit("", "syscall", "end", fp);

}
/*
 *PRE: pointer to node and file to point to
 *POST: create MIPS code for reading in a number
 * */
void emit_read(struct ASTNode *p, FILE *fp){
	emit_ident(p->s1, fp);//getting the identifier to read
	emit("", "li $v0 5", "read in a number", fp);
	emit("", "syscall", "now read", fp);
	emit("", "sw $v0 ($a0)", "end of read statement", fp);	
}

/*
 *PRE: pointer to node and file to point to
 *POST: create and call identifiers for arrays and scalars in MIPS
 * */
void emit_ident(struct ASTNode *p, FILE *fp){
	char s[100];//declare the command array for emitting commands
	if(p->s1!=NULL){//we have an array
		emit_expr(p->s1, fp);//we get the routine for the type of expression in s1
		emit("", "move $a0, $t0", "move $a0 to $t0", fp);
		sprintf(s, "sll $t0, $a0, %d", WLOGSIZE);
		emit("", s, "multiply wordsile", fp);

        }

		//at this point scalar or array type is taken care of already and has the same following routine
		if(p->symbol->level == 0){//global
			sprintf(s, "la $a0 %s", p->name);//its global so it has a name we can call in MIPS
                        emit("", s, "load global variable address, array value", fp);
					
		}
		else{//we have a local
			sprintf(s, "li $a0 %d", p->symbol->offset*WSIZE);//its local so we have to go to the MIPS memory location
			emit("", s, "load local array var", fp);
			emit("", "add $a0 $a0 $sp", "we have direct reference to memory", fp);	 
		}
		if(p->s1!=NULL){//ending the array routine by adding the value to array element in MIPS
			emit("", "add $a0, $a0, $t0", "add $t0", fp);
		}
}	
/*
 *PRE: pointer to node and file to point to
 *POST: MIPS code for all type of logical and arithmetic expressions
 * */
void emit_expr(struct ASTNode *p, FILE *fp){
	char s[100];//create character array for logging commands
	//the following selection statements satisfies yacc requirements
	switch(p->istype){//handle the node types that can occur in expressions
		case A_BOOL://bool is handled the same as num
		case A_NUM://if a number is found
			sprintf(s, "li $a0 %d", p->value);
			emit("", s, "load a number EXPR", fp);
			return;
			 break;
		case A_IDENT://if an identifier is found
			  emit_ident(p, fp);
			  sprintf(s, "lw $a0 ($a0)");
			  emit("", "lw $a0 ($a0)", "emit ident expr", fp);
			    return;
			  break;
		case A_CALL://if a call to function is found
			  emit_call(p, fp);
			  return;
			  break;
	}

	emit_expr(p->s1, fp);//now we recursively call the next node

	if(p->s2!=NULL){//if there is something to do in s2 we continue
	        sprintf(s, "sw $a0, %d($sp)", p->symbol->offset*WSIZE);
	        emit("", s, "store the value of lhs into memory", fp);
		emit_expr(p->s2, fp);//get the type or operator routine for s2
	        sprintf(s, "move $a1, $a0");
	        emit("", s, "move value of rhs into a1", fp);
	        sprintf(s, "lw $a0 %d($sp)", p->symbol->offset*WSIZE);
	        emit("", s, "load lhs into a0", fp);
	}

	switch(p->op){//operator and their operations
		case A_PLUS: //addition
			sprintf(s, "add $a0, $a0, $a1");
			emit("", s, "add $a0 and $a1", fp);
			break;
		case A_MINUS://subtraction
			sprintf(s, "sub $a0, $a0, $a1");
			emit("", s, "subtract $a0 and $a1", fp);
			break;
		case A_TIMES://multiplication
			emit("", "mult $a0, $a1", "multiply $a0 and $a1", fp);
			emit("", "mflo $a0", "store multiplication result", fp);
			break;
		case A_DIVIDE://division
			emit("", "div $a0, $a1", "divide $a0 and $a1", fp);
                        emit("", "mflo $a0", "store division result", fp);
			break;
		case A_AND://logical and
			sprintf(s, "and $a0, $a0, $a1");
			emit("", s, "and expr $a0 and $a1", fp);
			break;
		case A_OR://logical or
			sprintf(s, "or $a0, $a0, $a1");
			emit("", s, "or expr $a0 and $a1", fp);
			break;
		case A_NOT://logical not
			printf("NOT NOT \n");
			sprintf(s, "not $a0, $a0");
			emit("", s, "not expr $a0 and $a1", fp);
			break;
		case A_LT://less than
			sprintf(s, "slt $a0, $a0, $a1");
			emit("", s, "less than comparison $a0 and $a1", fp);
			break;
		case A_LE://less than or equal
			emit("", "add $a1, $a1, 1", "expr LE add one to do compare", fp);
			emit("", "slt $a0, $a0, $a1", "less than or equal comparison $a0 and $a1", fp);
			break;
		case A_GT://greater than
			sprintf(s, "slt $a0, $a1, $a0");
			emit("", s, "greater than comparison $a0 and $a1", fp);
			break;
		case A_GE://greater than or equal to
			emit("", "add $a0, $a0, 1", "EXPR GE add one to do compare", fp);
			emit("", "slt $a0, $a1, $a0", "EXPR GE", fp);
			break;
		case A_EQ://equals equals
			emit("", "slt $t2, $a0, $a1", "EXPR EQUAL EQUAL", fp);
			emit("", "slt $t3, $a1, $a0", "EXPR EQUAL EQUAL", fp);
			emit("", "nor $a0, $t2, $t3", "EXPR EQUAL EQUAL", fp);
			emit("", "andi $a0, 1", "EXPR EQUAL EQUAL", fp);
			break;
		case A_NEQ://not equal to
			emit("", "slt $t2, $a0, $a1", "EXPR NOT EQUAL", fp);
                        emit("", "slt $t3, $a1, $a0", "EXPR NOT EQUAL", fp);
                        emit("", "or $a0, $t2, $t3", "EXPR NOT EQUAL", fp);
			break;
	}	
}//emit_expr end


/*
 *PRE: pointer to node and file to print to
 *POST: output MIPS code for global strings
 * */
void emit_global_strings(struct ASTNode *p, FILE *fp){
	if(p==NULL) return;//base case

	if(p->istype==A_WRITE && p->name!=NULL){//if we have write type and name has a string in it
			char s[100];//create character array for commands
			sprintf(s, ".asciiz %s", p->name);//name has stored string from T_QUOTED_STRINGS in yacc
			emit(p->label, s, "emit global string", fp);//get the variable string's name and write the global variable with the string
		}
	//recursive calls
	emit_global_strings(p->next, fp);
	emit_global_strings(p->s1, fp);
	emit_global_strings(p->s2, fp);

}//end emit_global_strings

/*
 *PRE: nothing
 *POST: char string label for identifiers
 * */
char * GenerateLabel(){
	char s[100];//character array for logging commands
	char *f;//make a character pointer
	sprintf(s, "_L%d", glabel++);//create label, and iterate glabel to create a unique label each time
	f=strdup(s);//emit the label as a command and store it in f
	return f;//we return the label when function is called
}//end of GenerateLabel

/*
 *PRE: pointer to node and file to print to
 *POST: MIPS code for creating global variables
 * */
void emit_global_variables(struct ASTNode *p, FILE *fp){
	char s[100];//character array for logging commands
	if(p==NULL){ return;}//base case, if there is nothing in p then do nothing
	else{//p has something for us to do
		if(p->istype==A_VARDEC && p->symbol->level==0){ //if variable declaration and a global variable
			int v = p->symbol->mysize*WSIZE;//compute amount of space needed in MIPS
			//cannot use sprintf as emit's format will add an unnecessary colon ':'
			fprintf(fp, "%s:\t.space %d", p->name, v);//pass variable name and space required in MIPS
			fprintf(fp, "\t#add global variable"); //add comments
			fprintf(fp, "\n");//add spacing in program
		}
	}
	//recursive calls
	emit_global_variables(p->next, fp);
	emit_global_variables(p->s1, fp);
	emit_global_variables(p->s2, fp);
}//end emit_global_variables

/*
 *PRE: pointer to node and file to print to
 *POST: MIPS code for functions
 * */

void emit_function(struct ASTNode *p, FILE *fp){
	char s[100];//character array for logging commands

	emit(p->name, "", "Start of Function", fp);//emit the function label
	//function header routine
	sprintf(s, "subu $t0 $sp %d", p->symbol->mysize *WSIZE);//put $t0 for stack pointer
	emit("", s, "Set up $t0 to be the new spot for SP", fp);

	emit("", "sw $ra ($t0)", "Store the return address", fp);
	emit("", "sw $sp 4($t0)", "Store the old stack pointer", fp);
	emit("", "move $sp $t0", "Set the stack pointer to the new value", fp);
	fprintf(fp, "\n");

	emit_ast(p->s2, fp);//continue to the function's contents
	fprintf(fp, "\n");

	//now we are at the end of the function, need to do a select
	//return
	
	//reset SP and RA
	emit("", "li $v0 0", "create tail", fp);
	emit("", "lw $ra ($sp)", "reset the RA", fp);
	emit("", "lw $sp 4($sp)", "reset the SP to old SP", fp);
	fprintf(fp, "\n");//make space in program for neatness
	if(strcmp(p->name, "main")==0){ //create main function
		emit("", "li $v0 10", "syscall exit", fp);
		emit("", "syscall", "Return out of MARS", fp);
	}
	else{ //not main, do tail routine for end of other function
		emit("", "jr $ra", "Not main jump back to call function", fp);
		fprintf(fp, "\n");
	}
}//end of emit_function

//PRE: 3 character strings and a file to print to
//Post: formatted output to MIPS with labels, code, and comments
void emit(char *label, char *command, char *comment, FILE *fp){
	if(strcmp(label, "")==0) {//if no label is passed
		if(strcmp(comment, "")==0)//if there are not any comments
			//label and comment are empty
			fprintf(fp, "\t\t%s\n", command);
		else//if there are comments
			fprintf(fp, "\t\t%s\t#%s\n", command, comment);
	}
	else {//a label was passed
		if(strcmp(comment, "")==0)//a comment was not passed
			//label full and comment empty
			fprintf(fp, "%s:\t%s\n", label, command);
		else//a comment was passed
			//label and comment full
			fprintf(fp, "%s:\t%s\t#%s\n", label, command, comment);
	}
}//end emit

//end of the file
