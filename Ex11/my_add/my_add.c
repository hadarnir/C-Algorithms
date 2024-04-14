/*
 Author: Hadar Nir
*/
#include "stdio.h"
#include <stdlib.h>

#define BYTE_SIZE 8

/*
 This function performs a simple binary addition algorithm.
 It iterates through each bit of the input numbers using a for loop
 and isolates each bit using bit shifting.

 @param a: (unsigned int) The first number for the addition.
 @param b: (unsigned int) The second number for the addition.

 @return: (unsigned int) The sum of the two numbers.
*/
unsigned int my_add(unsigned int a, unsigned int b)
{
    unsigned int sum = 0, carry = 0, result = 0, bitA, bitB, i;

    for (i = 0; i < sizeof(int) * BYTE_SIZE; i++) {
        bitA = (a >> i) & 1;
        bitB = (b >> i) & 1;

        /* Calculate the sum of bits and carry */
        sum = bitA ^ bitB ^ carry;

        /* Update the result with the sum at the current bit position */
        result |= (sum << i);

        /* Calculate the new carry */
        carry = (bitA & bitB) | (bitA & carry) | (bitB & carry);
    }

    return result;
}

/*
 This function converts a decimal number to its binary representation as a string.

 @param num: (unsigned int) The decimal number to convert.

 @return: (char*) A pointer to the binary representation string.
*/
char* decimalToBinary(unsigned int num)
{
    // Array to store binary digits as characters
    char* binaryStr = (char*)malloc(32 * sizeof(char)); // Assuming max 32 bits for binary representation
    int i = 0;

    // Convert decimal to binary
    while (num > 0) {
        binaryStr[i] = (num % 2) + '0'; // Convert binary digit to character '0' or '1'
        num /= 2;
        i++;
    }
    binaryStr[i] = '\0'; // Null-terminate the string

    // Reverse the string to get the correct binary representation
    int len = i;
    for (int j = 0; j < len / 2; j++) {
        char temp = binaryStr[j];
        binaryStr[j] = binaryStr[len - j - 1];
        binaryStr[len - j - 1] = temp;
    }

    return binaryStr;
}

int main()
{
    unsigned int num1, num2, sum;

    /* Prompt user for input */
    printf("Enter two integers ('12345 54321'): ");

    /* Read two integers */
    scanf("%u %u", &num1, &num2);

    printf("Num1: %u, num2: %u\n", num1, num2);
    /* Calculate the sum */
    sum = my_add(num1, num2);

    // Print the sum
    printf("The addition result is: %u + %u = %u\n", num1, num2, sum);

    // Convert and print binary representation
    printf("Num1: %s\n", decimalToBinary(num1));
    printf("Num2: %s\n", decimalToBinary(num2));
    printf("Sum:  %s\n", decimalToBinary(sum));

    return 0;
}
