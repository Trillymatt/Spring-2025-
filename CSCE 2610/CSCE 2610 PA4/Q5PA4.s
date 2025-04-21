
// Problem 5: Leaf procedure convert_str
// Convert uppercase <-> lowercase, skip non-alphabet

.data
str_case: .asciz "aB3cD#EfGz"

.text
.global _start

_start:
    LDR X0, =str_case
    BL convert_str_leaf

    MOV X8, #93
    MOV X0, #0
    SVC #0

convert_str_leaf:
    MOV X1, X0
convert_loop_leaf:
    LDRB W2, [X1], #1
    CBZ W2, convert_done_leaf

    CMP W2, #'A'
    BLT not_upper_leaf
    CMP W2, #'Z'
    BGT not_upper_leaf
    ADD W2, W2, #32
    B push_leaf
not_upper_leaf:
    CMP W2, #'a'
    BLT not_alpha_leaf
    CMP W2, #'z'
    BGT not_alpha_leaf
    SUB W2, W2, #32
    B push_leaf
not_alpha_leaf:
    // Do nothing

push_leaf:
    STRB W2, [SP, #-1]!
    B convert_loop_leaf

convert_done_leaf:
    MOV W2, #0
    STRB W2, [SP, #-1]!
    RET
