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

/**
 * _getenv - gets an environment variable
 * @name: name of the environment variable
 * Return: pointer to the value of the environment variable
 * or NULL if there is no match
*/

char *_getenv(const char *name)
{
    char **env;
    char *env_name, *delimeter;
    size_t name_len;

    if (name == NULL || name[0] == '\0')
        return (NULL);
    for (env = environ; *env != NULL; env++)
    {
        env_name = *env;
        delimeter = _strchr(env_name, '=');

        if (delimeter != NULL)
        {
            name_len = (size_t)(delimeter - env_name);
            if (_strlen(name) == name_len && _strncmp(env_name, name, name_len) == 0)
            {
                return (delimeter + 1);
            }
        }
    }
    return (NULL);
}
/**
 * _strcpy - copies the string pointed to by src to dest
 * @dest: destination string
 * @src: source string
 * Return: pointer to dest
*/
char *_strcpy(char *dest, const char *src)
{
    int i;
    for (i = 0; src[i] != '\0'; i++)
        dest[i] = src[i];
    dest[i] = src[i];
    return dest;
}

/**
 * _strlen - returns the length of a string
 * @s: string to be measured
 * Return: length of the string
*/
size_t _strlen(const char *s)
{
    int len;
    for (len = 0; s[len] != '\0'; len++)
        ;
    return len;
}