#include <stdio.h>
#include <stdlib.h>

int main() {

    int *int_ptr = (int *)malloc(2 * sizeof(int));

    if (int_ptr == NULL) {
        printf("Memory allocation error\n");
        return 0;
    }

    printf("Enter first integer: ");
    scanf("&d", &int_ptr[0]);

    printf("Enter second integer: ");
    scanf("&d", &int_ptr[1]);
    
    printf("Original values: 1st = %d 2nd = %d\n", int_ptr[0], int_ptr[1]);
    
    int_ptr[0] = int_ptr[0] ^ int_ptr[1];
    int_ptr[1] = int_ptr[0] ^ int_ptr[1];
    int_ptr[0] = int_ptr[0] ^ int_ptr[1];

    printf("Swapped values: 1st: %d 2nd: %d\n", int_ptr[0], int_ptr[1]);

    free(int_ptr);

    return 0;
}
