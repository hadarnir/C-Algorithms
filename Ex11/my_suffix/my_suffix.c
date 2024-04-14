/*
 Author: Hadar Nir
*/
#include "stdio.h"

#define END_OF_STRING '\0'

/*
 * Finds suffixes in a string starting with a given character and counts them.
 *
 * This function iterates over the string using a for loop.
 *
 * @param str: (char[]) the string to iterate over.
 * @param c: (char) the character that starts the suffix.
 *
 * @return: (int) the number of suffixes in the string.
 *          If a suffix is found, it is printed.
 */
int suffix(char str[], char c)
{
    int count = 0;
    char* currChar;

    for (currChar = str; *currChar != END_OF_STRING; currChar++)
    {
        if (*currChar == c)
        {
            printf("%s\n", currChar);
            count++;
        }
    }

    return count;
}

int main()
{
    char c, str[128];
    int suffixResult;

    /* Read a character */
    printf("Enter a character: ");
    scanf("%c", &c);

    /* Read a string */
    printf("Enter a string: ");
    scanf("%s", str);

    printf("The given string is: %s \nThe given character is: %c\n", str, c);
    /* Run the suffix function */
    suffixResult = suffix(str, c);

    /* Print the count of suffixes */
    printf("The number of suffixes is: %d\n", suffixResult);

    return 0;
}
