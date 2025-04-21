//.data
//myStr:           			// data section
//	.asciz	"bdcae"
//
//.text
//.global main
//
//main:
//    // Load the addresses
//    LDR X0, =myStr
//
//    MOV X4, #0
//    outer_loop:
//		MOV X1, X0
//		MOV X5, #0
//    inner_loop:
//		LDRB W2, [X1]
//		CBZ W2, end_outer
//
//		LDRB W3, [X1, #1]
//		CBZ W3, check_swaps
//
//		CMP W2, W3
//		B.LE no_swap
//
//		STRB W3, [X1]
//		STRB W2, [X1, #1]
//
//		MOV X5, #1
//	no_swap:
//		ADD X1, X1, #1
//		B inner_loop
//	check_swaps:
//	CMP X5, #1
//	B.EQ outer_loop
//	B end_outer
//	end_outer:
//		B exit
//exit:



