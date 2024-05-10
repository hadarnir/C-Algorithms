//
// Created by Hadar on 5/8/2024.
//

#include <stdio.h>
#include <stdlib.h>

/**
 * Calculates the partial sums of an array.
 *
 * @param arr The input array.
 * @param length The length of the input array.
 * @return A pointer to an array of partial sums.
 */
int* partialSums(int* arr, int length)
{
    int i, sum = 0;
    int* partialSums = (int*)malloc(sizeof(int) * length);
    for (i = 0; i < length; i++) {
        sum += arr[i];
        partialSums[i] = sum; // Calculate and store the partial sums
    }
    return partialSums;
}

/**
 * Takes user input to create an integer array.
 *
 * @param length The length of the array to be created.
 * @return A pointer to the created integer array.
 */
int* getArrayInput(int length)
{
    int i;
    int* arr = (int*)malloc(sizeof(int) * length);
    printf("Array length is %d\n", length);
    for (i = 0; i < length; i++) {
        printf("\nEnter the number in index %d: ", i);
        scanf("%d", arr + i); // Read user input and store in array
    }
    return arr;
}

/**
 * Prints an integer array.
 *
 * @param arr The array to be printed.
 * @param length The length of the array.
 */
void printArray(int* arr, int length)
{
    int i;
    printf("\n{");
    for (i = 0; i < length-1; i++)
    {
        printf("%d, ", arr[i]); // Print each element of the array
    }

    printf("%d}\n", arr[length-1]); // Print the last element of the array
}

/**
 * The main function to demonstrate partial sums calculation.
 */
int main() {
    int length;
    int* pArr;
    int* pPartialSums;

    printf("Enter the array's length: ");
    scanf("%d", &length); // Read the length of the array from user input

    pArr = getArrayInput(length); // Get user input for array elements

    printf("The given array is:");
    printArray(pArr, length); // Print the input array

    pPartialSums = partialSums(pArr, length); // Calculate and store partial sums

    printf("The returned partial sums array is:");
    printArray(pPartialSums, length); // Print the partial sums array

    free(pPartialSums); // Free memory allocated for partial sums array
    free(pArr); // Free memory allocated for input array
}
