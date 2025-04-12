
// Problem 6: Non-leaf convert_str with test_char
// Requirements Met:
// - X0 has the input string for convert_str
// - X0 has the character for test_char
// - test_char returns 1 (uppercase), -1 (lowercase), 0 (non-alphabet)
// - All link registers and stack frames are preserved

.data
str_case: .asciz "aB3cD#EfGz"

.text
.global _start

_start:
    LDR X0, =str_case      // Pass address of string in X0
    BL convert_str_nonleaf

    MOV X8, #93
    MOV X0, #0
    SVC #0

// ----------------------
// convert_str_nonleaf
// ----------------------
convert_str_nonleaf:
    STP X29, X30, [SP, #-16]!  // Save frame pointer and return address
    MOV X29, SP

    MOV X1, X0              // Copy string pointer to X1

convert_loop_nonleaf:
    LDRB W2, [X1], #1       // Load character into W2 and advance pointer
    CBZ W2, convert_done_nonleaf

    // Call test_char with char in X0
    UXTB X0, W2              // Move char to W0 (also X0)
    BL test_char

    CMP W0, #1
    B.EQ to_lower_nonleaf
    CMP W0, #-1
    B.EQ to_upper_nonleaf
    B push_nonleaf

to_lower_nonleaf:
    ADD W2, W2, #32         // Convert to lowercase
    B push_nonleaf
to_upper_nonleaf:
    SUB W2, W2, #32         // Convert to uppercase
    B push_nonleaf

push_nonleaf:
    STRB W2, [SP, #-1]!     // Push converted char to stack
    B convert_loop_nonleaf

convert_done_nonleaf:
    MOV W2, #0
    STRB W2, [SP, #-1]!     // Push null terminator

    LDP X29, X30, [SP], #16 // Restore frame pointer and return address
    RET

// ----------------------
// test_char
// ----------------------
test_char:
    STP X29, X30, [SP, #-16]!  // Save link register for safety
    MOV X29, SP

    // Check uppercase
    CMP W0, #'A'
    BLT not_upper_test
    CMP W0, #'Z'
    BGT not_upper_test
    MOV W0, #1
    B test_done

not_upper_test:
    CMP W0, #'a'
    BLT not_lower_test
    CMP W0, #'z'
    BGT not_lower_test
    MOV W0, #-1
    B test_done

not_lower_test:
    MOV W0, #0

test_done:
    LDP X29, X30, [SP], #16
    RET
