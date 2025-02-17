.data
    x1:     	.xword 9         // First number
    x2:    	.xword 5        // Second number
    x3:   	.xword 2          // Third number
    x4: 		.xword 3          //Fourth number
    x5:      .xword 2          // Fifth number
    x6:      .xword 4          //Sixth number

.text
.global main

main:
    // Load the addresses of x0 and x1 into registers X0 and X1
	ADR X9, x1
	ADR X10, x2
	ADR X11, x3
	ADR X12, x4
	ADR X13, x5
	ADR X14, x6

	LDR X0, [X9] //X0 = a (9)
	LDR X1, [X10] //X1 = b (5)
	LDR X2, [X11] //X2 = c (2)
	LDR X3, [X12] //X3 = d (3)
	LDR X4, [X13] //X4 = e (2)
	LDR X5, [X14] //X5 = f (4)


	// Multiply b * c
	MUL X6, X1, X2 //X6 = b * c
	ADD X6, X6, X0 //X6 = (a + (b * c))
	SUB X6, X6, X3 //X6 = (a + (b * c)) - d
	SDIV X6, X6, X4 //X6 = ((a + (b * c)) - d) / e
	ADD X6, X6, X5 //X6 = (((a + (b * c)) - d) / e) + f
