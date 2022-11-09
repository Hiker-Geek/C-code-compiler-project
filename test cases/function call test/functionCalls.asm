.data #start of data section global strings

_NL: .asciiz "\n "# New line
.align 2 #start all global variables aligned

#global variables

.text

.globl main

f:		#Start of Function
		subu $t0 $sp 16	#Set up $t0 to be the new spot for SP
		sw $ra ($t0)	#Store the return address
		sw $sp 4($t0)	#Store the old stack pointer
		move $sp $t0	#Set the stack pointer to the new value

		li $a0 8	#load local array var
		add $a0 $a0 $sp	#we have direct reference to memory
		lw $a0 ($a0)	#emit ident expr
		sw $a0, 12($sp)	#store the value of lhs into memory
		li $a0 6	#load a number EXPR
		move $a1, $a0	#move value of rhs into a1
		lw $a0 12($sp)	#load lhs into a0
		mult $a0, $a1	#multiply $a0 and $a1
		mflo $a0	#store multiplication result
		add $a0, $a0, $a1	#add $a0 and $a1

		li $v0 0	#create tail
		lw $ra ($sp)	#reset the RA
		lw $sp 4($sp)	#reset the SP to old SP

		jr $ra	#Not main jump back to call function

main:		#Start of Function
		subu $t0 $sp 12	#Set up $t0 to be the new spot for SP
		sw $ra ($t0)	#Store the return address
		sw $sp 4($t0)	#Store the old stack pointer
		move $sp $t0	#Set the stack pointer to the new value

		li $a0 8	#load a number EXPR
		sw $a0 8($sp)	#store argument temporary
		subu $t0 $sp 16	#make $t0 sp the new function size
		lw $t2 8($sp)	#get value from rhs memory
		sw $t2 8($t0)	#store rhs value
		jal f	#jump to parameter
		li $v0, 1	#print number
		syscall	#end

		li $v0 0	#create tail
		lw $ra ($sp)	#reset the RA
		lw $sp 4($sp)	#reset the SP to old SP

		li $v0 10	#syscall exit
		syscall	#Return out of MARS
