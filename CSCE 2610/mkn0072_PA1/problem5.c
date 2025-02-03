// #include <stdio.h>

// int main() {
//     float x;      
//     int a;        
//     float sinX = 0.0; 

//     // Input values
//     printf("Enter the value of x (in radians): ");
//     scanf("%f", &x);

//     printf("Enter the number of terms a (positive integer): ");
//     scanf("%d", &a);

    
//     if (a <= 0) {
//         printf("Invalid input! 'a' must be a positive integer.\n");
//         return 1; 
//     }

    
//     for (int n = 0; n < a; n++) {
//         int exponent = 2 * n + 1; 

        
//         float fact = 1;
//         for (int i = 1; i <= exponent; i++) {
//             fact *= i;
//         }
        
//         float power = 1.0;
//         for (int i = 0; i < exponent; i++) {
//             power *= x;
//         }

//         float term = power / fact;
//         if (n % 2 != 0) {
//             term = -term; 
//         }

//         sinX += term; 
//     }

//     printf("sin(%.4f) ≈ %.6f\n", x, sinX);

//     return 0;
// }