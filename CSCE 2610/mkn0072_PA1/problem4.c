// #include <stdio.h>
// #include <stdlib.h>

// int main() {

//     char sentence[256];
//     int words, digits, length;
//     int i = 0, inWord = 0;
//     int wordCount = 0, digitCount = 0;

//     printf("Enter a sentence (max 255 characters): ");
//     fgets(sentence, 256, stdin);

//     while (sentence[i] != '\0') {
//         (length)++;

//         if (sentence[i] >= '0' && sentence[i] <= '9') {
//             (digitCount)++;
//         }
//         if (sentence[i] != ' ') {
//             if (inWord == 0) {
//                 wordCount++;  
//                 inWord = 1;
//             }
//         } 
//         else {
//             inWord = 0;  
//         }

//         i++;
//     }
//     printf("Number of words: %d\n", wordCount);
//     printf("Total number of numeric digits %d\n", digitCount);
//     printf("Length of the sentence: %d\n", length);

//     return 0;

// }