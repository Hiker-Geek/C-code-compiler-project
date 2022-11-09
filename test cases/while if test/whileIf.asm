.data #start of data section global strings

_NL: .asciiz "\n "# New line
.align 2 #start all global variables aligned

#global variables
x:	.space 4	#add global variable
y:	.space 20	#add global variable

.text

.globl main

main:		#Start of Function
		subu $t0 $sp 28	#Set up $t0 to be the new spot for SP
		sw $ra ($t0)	#Store the return address
		sw $sp 4($t0)	#Store the old stack pointer
		move $sp $t0	#Set the stack pointer to the new value

		li $a0 1	#load a number EXPR
		sw $a0, 8($sp)	#store rhs value in memory
		la $a0 x	#load global variable address, array value
		lw $a1 8($sp)	#get rhs stored value
		sw $a1 ($a0)	#ASSIGN final store

_L0:		#begin while loop
		la $a0 x	#load global variable address, array value
		lw $a0 ($a0)	#emit ident expr
		sw $a0, 12($sp)	#store the value of lhs into memory
		li $a0 5	#load a number EXPR
		move $a1, $a0	#move value of rhs into a1
		lw $a0 12($sp)	#load lhs into a0
		add $a0, $a0, 1	#EXPR GE add one to do compare
		slt $a0, $a1, $a0	#EXPR GE
		beq $a0 $0 _L1	#while branch out

		la $a0 x	#load global variable address, array value
		lw $a0 ($a0)	#emit ident expr
		sw $a0, 16($sp)	#store the value of lhs into memory
		li $a0 5	#load a number EXPR
		move $a1, $a0	#move value of rhs into a1
		lw $a0 16($sp)	#load lhs into a0
		slt $t2, $a0, $a1	#EXPR EQUAL EQUAL
		slt $t3, $a1, $a0	#EXPR EQUAL EQUAL
		nor $a0, $t2, $t3	#EXPR EQUAL EQUAL
		andi $a0, 1	#EXPR EQUAL EQUAL
		beq $a0 $0 _L2	#if branch to else part

		li $a0 3	#load a number EXPR
		sw $a0, 20($sp)	#store rhs value in memory
		la $a0 x	#load global variable address, array value
		lw $a0 ($a0)	#emit ident expr
		move $a0, $t0	#move $a0 to $t0
		sll $t0, $a0, 2	#multiply wordsile
		la $a0 y	#load global variable address, array value
		add $a0, $a0, $t0	#add $t0
		lw $a1 20($sp)	#get rhs stored value
		sw $a1 ($a0)	#ASSIGN final store


		j _L3	#if s1 end

_L2:		#else target
		la $a0 x	#load global variable address, array value
		lw $a0 ($a0)	#emit ident expr
		sw $a0, 20($sp)	#store the value of lhs into memory
		li $a0 2	#load a number EXPR
		move $a1, $a0	#move value of rhs into a1
		lw $a0 20($sp)	#load lhs into a0
		mult $a0, $a1	#multiply $a0 and $a1
		mflo $a0	#store multiplication result
		sw $a0, 24($sp)	#store rhs value in memory
		la $a0 x	#load global variable address, array value
		lw $a0 ($a0)	#emit ident expr
		move $a0, $t0	#move $a0 to $t0
		sll $t0, $a0, 2	#multiply wordsile
		la $a0 y	#load global variable address, array value
		add $a0, $a0, $t0	#add $t0
		lw $a1 24($sp)	#get rhs stored value
		sw $a1 ($a0)	#ASSIGN final store


_L3:		#exit if statement
		la $a0 x	#load global variable address, array value
		lw $a0 ($a0)	#emit ident expr
		sw $a0, 20($sp)	#store the value of lhs into memory
		li $a0 1	#load a number EXPR
		move $a1, $a0	#move value of rhs into a1
		lw $a0 20($sp)	#load lhs into a0
		add $a0, $a0, $a1	#add $a0 and $a1
		sw $a0, 24($sp)	#store rhs value in memory
		la $a0 x	#load global variable address, array value
		lw $a1 24($sp)	#get rhs stored value
		sw $a1 ($a0)	#ASSIGN final store


		j _L0	#while loop jump back
_L1:		#end while loop

		li $v0 0	#create tail
		lw $ra ($sp)	#reset the RA
		lw $sp 4($sp)	#reset the SP to old SP

		li $v0 10	#syscall exit
		syscall	#Return out of MARS
