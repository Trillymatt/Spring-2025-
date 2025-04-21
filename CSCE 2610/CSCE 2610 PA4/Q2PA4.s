//.data
//myStr1:           			// data section
//	.asciz "so!"
//.text
//.global main
//
//main:
//    // Load the addresses
//    LDR X0, =myStr
//    LDRB W1, [X0]
//    MOV W2, W1
//	loop:
//		CBZ W1, end_loop
//		CMP W1, W2
//		B.LE skip_update
//		MOV W2, W1
//    skip_update:
//    	ADD X0, X0, #1
//    	LDRUB W1, [X0]
//    	B loop
//	end_loop:
//		SUB SP, SP, #8
//		MOV x6, SP
//		STURB W2, [X6, #0]
//		B exit
//exit:


