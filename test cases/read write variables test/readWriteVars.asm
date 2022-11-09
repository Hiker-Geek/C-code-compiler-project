.data #start of data section global strings

_L0:	.asciiz "give me a number\n"	#emit global string
_L1:	.asciiz "this is your number: "	#emit global string
_L2:	.asciiz "\nthis was my number: "	#emit global string
_NL: .asciiz "\n "# New line
.align 2 #start all global variables aligned

#global variables
x:	.space 4	#add global variable
y:	.space 60	#add global variable
z:	.space 4	#add global variable

.text

.globl main

main:		#Start of Function
		subu $t0 $sp 148	#Set up $t0 to be the new spot for SP
		sw $ra ($t0)	#Store the return address
		sw $sp 4($t0)	#Store the old stack pointer
		move $sp $t0	#Set the stack pointer to the new value

		li $a0 10	#load a number EXPR
		sw $a0, 132($sp)	#store rhs value in memory
		la $a0 x	#load global variable address, array value
		lw $a1 132($sp)	#get rhs stored value
		sw $a1 ($a0)	#ASSIGN final store

		li $a0 3	#load a number EXPR
		sw $a0, 136($sp)	#store rhs value in memory
		li $a0 1	#load a number EXPR
		move $a0, $t0	#move $a0 to $t0
		sll $t0, $a0, 2	#multiply wordsile
		la $a0 y	#load global variable address, array value
		add $a0, $a0, $t0	#add $t0
		lw $a1 136($sp)	#get rhs stored value
		sw $a1 ($a0)	#ASSIGN final store

		li $a0 12	#load a number EXPR
		sw $a0, 140($sp)	#store rhs value in memory
		li $a0 23	#load a number EXPR
		move $a0, $t0	#move $a0 to $t0
		sll $t0, $a0, 2	#multiply wordsile
		li $a0 8	#load local array var
		add $a0 $a0 $sp	#we have direct reference to memory
		add $a0, $a0, $t0	#add $t0
		lw $a1 140($sp)	#get rhs stored value
		sw $a1 ($a0)	#ASSIGN final store

		li $a0 8	#load a number EXPR
		sw $a0, 144($sp)	#store rhs value in memory
		li $a0 128	#load local array var
		add $a0 $a0 $sp	#we have direct reference to memory
		lw $a1 144($sp)	#get rhs stored value
		sw $a1 ($a0)	#ASSIGN final store

		li $v0, 4	#print a string
		la $a0 _L0	#print fetch string location
		syscall	#end
		la $a0 z	#load global variable address, array value
		li $v0 5	#read in a number
		syscall	#now read
		sw $v0 ($a0)	#end of read statement
		li $v0, 4	#print a string
		la $a0 _L1	#print fetch string location
		syscall	#end
		la $a0 z	#load global variable address, array value
		lw $a0 ($a0)	#emit ident expr
		li $v0, 1	#print number
		syscall	#end
		li $v0, 4	#print a string
		la $a0 _L2	#print fetch string location
		syscall	#end
		li $a0 28	#load a number EXPR
		li $v0, 1	#print number
		syscall	#end

		li $v0 0	#create tail
		lw $ra ($sp)	#reset the RA
		lw $sp 4($sp)	#reset the SP to old SP

		li $v0 10	#syscall exit
		syscall	#Return out of MARS
