//
// Created by Hadar on 3/27/2024.
//

#include "my_add.h"

#include <stdio.h>

#define BYTE_SIZE 8

/*
 * This function performs binary addition on two unsigned integers.
 * It iterates over each bit position using a for loop and performs
 * bitwise operations to calculate the sum and carry.
 *
 * @param a: (unsigned int) the first number for the addition
 * @param b: (unsigned int) the second number for the addition
 * @return: (unsigned int) The sum of the two numbers
 */
unsigned int my_add(unsigned int a, unsigned int b)
{
    unsigned int sum = 0, carry = 0, result = 0, bitA, bitB, i;

    for (i = 0; i < sizeof(int) * BYTE_SIZE; i++) {
        bitA = (a >> i) & 1;
        bitB = (b >> i) & 1;

        // Calculate the sum of bits and carry
        sum = bitA ^ bitB ^ carry;

        // Update the result with the sum at the current bit position
        result |= (sum << i);

        // Calculate the new carry
        carry = (bitA & bitB) | (bitA & carry) | (bitB & carry);
    }

    return result;
}

int main()
{
    unsigned int num1, num2, sum;

    // Prompt user for input
    printf("Enter two integers: ");

    // Read two integers
    scanf("%u %u", &num1, &num2);

    // Calculate the sum
    sum = my_add(num1, num2);

    // Print the sum
    printf("The binary addition: %u + %u = %u\n", num1, num2, sum);

    return 0;
}
