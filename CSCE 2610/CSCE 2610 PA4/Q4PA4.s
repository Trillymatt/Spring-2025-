.data
myStr1: .asciz	"Hello"
myStr2:	.asciz  "World"
.text
.global main

main:
    // Load the addresses
    LDR X0, =myStr1
    LDRB W1, [X0]
	copy_str1:
		LDRB W1, [X0]
		CBZ W1, copy_str2
		SUB SP, SP, #1
		MOV x6, SP
		STURB W1, [X6, #0]
		ADD X0, X0, #1
		B copy_str1
    copy_str2:
    	LDR X0, =myStr2
	copy_str2_loop:
		LDRB W1, [X0]
		CBZ W1, exit
		SUB SP, SP, #1
		MOV x6, SP
		STURB W1, [X6, #0]
		ADD X0, X0, #1
		B copy_str2_loop
	exit:
		SUB SP, SP, #1
		MOV W1, #0
		STRB W1, [SP]





