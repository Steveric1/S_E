#include "main.h"

/**
 * _strchr - locates a character in a string
 * @s: string to be searched
 * @c: character to be located
 * Return: pointer to the first occurrence of the character c in the string s
*/
char *_strchr(const char *s, int c)
{
    int i;
    for (i = 0; s[i] != '\0'; i++)
    {
        if (s[i] == c)
            return (char *)(s + i);
    }
    return (NULL);
}

/**
 * str_pointer_break - breaks a string into tokens
 * @str1: string to be tokenized
 * @str2: delimiter
 * Return: pointer to the first occurrence of the delimiter
*/

char *str_pointer_break(char *str1, const char *str2)
{
    int i, j;

    for (i = 0; str1[i] != '\0'; i++)
    {
        j = 0;
        while (str2[j] != '\0')
        {
            if (str1[i] == str2[j])
            {
                return (str1 + i);
            }
            j++;
        }
    }

    return (NULL);
}