#include <stdio.h>
#include <stdlib.h>

int main() {
    //intializing variables
    int y = 0, a = 0, n = 0;
    int result = 0;
    //Ask user for input and number of iterations
    printf("Please input the number you would like to add: \n");
    scanf("%d", &a);
    printf("Please input the number of iterations you would like: \n");
    scanf("%d", &n);
    //Process for summation
    for(int i = 0; i < (n - 1); i++){
        if (i == 0) {
            y = a + a;
        }
        else {
            y = y + a;
        }
    }
    printf("The result of the summation is %d", y);

    return 0;
}