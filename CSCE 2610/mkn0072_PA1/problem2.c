// #include <stdio.h>
// #include <stdlib.h>

// int main() {
//     //Variables
//     int y = 0, a = 0, b = 0, n = 0, pow = 0, result = 0;
//     //Get numbers from user
//     printf("Input the value of a: \n");
//     scanf("%d", &a);
//     printf("Input the value of n: \n");
//     scanf("%d", &n);
//     printf("Input the value of b: \n");
//     scanf("%d", &b);
//     //Find the result of a to the power of n
//     pow = a;
//     for(int i = 0; i < (n - 1); i++) {
//         if (n == 0) {
//             a = 1;
//         }
//         if (n == 1) {
//             break;
//         }
//         pow = pow * a;
//     }
//     //Find result of equation
//     result = pow + b;
//     //Summation of the result of equation
//     for(int i = 0; i < (n - 1); i++){
//         if (i == 0) {
//             y = result + result;
//         }
//         else {
//             y = y + result;
//         }
//     }
//     printf("The result of the summation is %d", y);

//     return 0;
// }