
// Problem 6: Non-leaf convert_str with test_char

.data
str_case: .asciz "aB3cD#EfGz"

.text
.global _start

_start:
    LDR X0, =str_case
    BL convert_str_nonleaf

    MOV X8, #93
    MOV X0, #0
    SVC #0

convert_str_nonleaf:
    STP X29, X30, [SP, #-16]!
    MOV X29, SP

    MOV X1, X0
convert_loop_nonleaf:
    LDRB W2, [X1], #1
    CBZ W2, convert_done_nonleaf

    MOV W0, W2
    BL test_char

    CMP W0, #1
    B.EQ to_lower_nonleaf
    CMP W0, #-1
    B.EQ to_upper_nonleaf
    B push_nonleaf

to_lower_nonleaf:
    ADD W2, W2, #32
    B push_nonleaf
to_upper_nonleaf:
    SUB W2, W2, #32
    B push_nonleaf

push_nonleaf:
    STRB W2, [SP, #-1]!
    B convert_loop_nonleaf

convert_done_nonleaf:
    MOV W2, #0
    STRB W2, [SP, #-1]!

    LDP X29, X30, [SP], #16
    RET

test_char:
    CMP W0, #'A'
    BLT not_upper_test
    CMP W0, #'Z'
    BGT not_upper_test
    MOV W0, #1
    RET
not_upper_test:
    CMP W0, #'a'
    BLT not_lower_test
    CMP W0, #'z'
    BGT not_lower_test
    MOV W0, #-1
    RET
not_lower_test:
    MOV W0, #0
    RET
