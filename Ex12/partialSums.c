//
// Created by Hadar on 5/8/2024.
//

#include <stdio.h>
#include <stdlib.h>


int* partialSums(int* arr, int length)
{
    int i, sum = 0;
    int* partialSums = (int*)malloc(sizeof(int) * length);
    for (i = 0; i < length; ++i) {
        sum += arr[i];
        partialSums[i] = sum;
    }
    return partialSums;
}


int* getArrayInput(int length)
{
    int i;
    int* arr = (int*)malloc(sizeof(int) * length);
    printf("Array length is %d\n", length);
    for (i = 0; i < length; i++) {
        printf("\nEnter the number in index %d: ", i);
        scanf("%d", arr + i);
    }

    return arr;
}



void printArray(int* arr, int length)
{
    int i;
    printf("\n{");
    for (i = 0; i < length-1; ++i)
    {
        printf("%d, ", arr[i]);
    }

    printf("%d}\n", arr[length-1]);
}


int main() {
    int length;
    int* pArr;
    int* pPartialSums;

    printf("Enter the array`s length: ");
    scanf("%d", &length);

    pArr = getArrayInput(length);

    printf("The given array is:");
    printArray(pArr, length);

    pPartialSums = partialSums(pArr, length);

    printf("The returned partial sums array is:");
    printArray(pPartialSums, length);

    free(pPartialSums);
    free(pArr);
}

