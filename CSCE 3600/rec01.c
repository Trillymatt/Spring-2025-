#include <stdio.h>

int main() {

    char inputVal;

    printf("Enter an ASCII character: ");
    scanf(" %c", &inputVal);

    printf("The ASCII value of %c is:\n", inputVal);
    printf("dec -- %d\n", inputVal);
    printf("hex -- %x\n", inputVal);

    printf("bin -- ");
    for (int i = 7; i >= 0; i--) {
        int bit = (inputVal >> i) & 1;
        printf("%d", bit);
    }
    printf("\n");
    
    return 0;

}