.data
array_size:	.word 5
array:	.double 1.5, 2.5, 3.5, 4.5, 5.5
sum: 	.double 0.0
average: .double 0.0
zero: .double 0.0

.text
.global main

main:
	ADRP X0, array //load array
	ADD X0, X0, :lo12:array

	ADRP X1, array_size //load array size
	ADD X1, X1, :lo12:array_size
	LDR W1, [X1]

	ADRP X10, zero //put float zero into a register
	ADD X10, X10, :lo12:zero
	LDR D0, [X10]
	MOV W2, #0
loop_start:
	CMP W2, W1 // compare W2 = 0 and the array size
	B.GE loop_end //end loop

	MOV W3, W2
	LSL W3, W3, #3
	UXTW X3, W3
	ADD X4, X0, X3
	LDR D1, [X4]

	FADD D0, D0, D1

	ADD W2, W2, #1 // increment loop
	B loop_start

loop_end:
	SCVTF D2, W1

	FDIV D3, D0, D2
	ADRP X5, sum
	ADD X5, X5, :lo12:sum
	STR D0, [X5]

	ADRP X6, average
	ADD X6, X6, :lo12:average
	STR D3, [X6]

end:
	B end
