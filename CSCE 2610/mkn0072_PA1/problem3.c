// #include <stdio.h>
// #include <stdlib.h>

// int main() {
//     //Variables
//     int b = 0, n = 0, pow = 0, result = 1;
//     //Input values
//     printf("Input value of b: \n");
//     scanf("%d", &b);
//     printf("Input value of n: \n");
//     scanf("%d", &n);
//     //Compute b to the power of n
//     pow = b;
//     for(int i = 0; i < (n - 1); i++) {
//         if (n == 0) {
//             b = 1;
//         }
//         if (n == 1) {
//             break;
//         }
//         pow = pow * b;
//     }
//     //Compute factorial
//     for(int j = 1; j <= pow; j++) {
//         result *= j;
//     }

//     printf("The result is %d", result);

//     return 0;
// }