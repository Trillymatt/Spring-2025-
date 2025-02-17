.data
	N: .xword 10 //Example input
	sum: .xword 0

.text
.global main

main:

	//Load x1 the upper bound
	ADR X9, N
	LDR X0, [X9]

	//Initialize sum = 0
	MOV X1, #0 //sum
	MOV X2, #2 //X2 = current even number

loop:
	CMP X2, X0
	BGT end_loop

	ADD X1, X1, X2 //sum += X2
	ADD X2, X2, #2 //move to next even number

	B loop

end_loop:

	ADR X10, sum
	STR X1, [X10]





