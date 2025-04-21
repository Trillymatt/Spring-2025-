.data
array_size:	.word 6
array:	.float 5.2, 1.1, 3.3, 6.4, 2.5, 0.9

.text
.global main

main:
	ADRP X0, array // load in array
	ADD X0, X0, :lo12:array

	ADRP X1, array_size
	ADD X1, X1, :lo12:array_size
	LDR W1, [X1]

	MOV W2, #0
outer_loop:
	SUB W6, W1, #1
	CMP W2, W6
	B.GE end

	MOV W3, #0

inner_loop:
	SUB W7, W1, W2 	//counter
	SUB W7, W7, #1
	CMP W3, W7
	B.GE outer_loop_increment

	MOV W4, W3
	LSL W4, W4, #2
	UXTW X4, W4
	ADD X5, X0, X4
	LDR S1, [X5]

	ADD X6, X5, #4
	LDR S2, [X6]

	FCMP S1, S2
	B.LE skip_swap

	STR S2, [X5] // stores x5 in S2 and swap values
	STR S1, [X6] //stores x6 in S1 and swap values

skip_swap:
	ADD W3, W3, #1
	B inner_loop
outer_loop_increment:
	ADD W2, W2, #1 //increment
	B outer_loop
end:
	B end


