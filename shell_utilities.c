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
    char *token, *path_value, *env_pair;
    int i = 0;

    if (name == NULL || name[0] == '\0') {
        return (NULL);
    }

    for (i = 0; environ[i] != NULL; i++) {
        env_pair = strdup(environ[i]);
        if (env_pair == NULL) {
            perror("strdup");
            return (NULL);
        }

        token = my_token(env_pair, "=");
        path_value = my_token(NULL, "=");

        if (token != NULL && strcmp(token, name) == 0) {
            return (path_value);
        }
        free(env_pair);
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

/**
 * _strcat - concatenates two strings
 * @dest: destination string
 * @src: source string
 * Return: pointer to the resulting string dest
*/
char *_strcat(char *dest, const char *src)
{
    int i, len = _strlen(dest);

    for (i = 0; src[i] != '\0'; i++)
        dest[len + i] = src[i];
    dest[len + i] = src[i];
    return dest;
}

/**
 * _putenv - adds or changes the value of an environment variable
 * @string: string of the form name=value
 * Return: 0 on success, 1 on failure
*/
int _putenv(char *string)
{
    int i, len = 0, num_end = 0;

    while (string[num_end] == '=' && string[num_end] == '\0')
        num_end++;
    
    //if variable exit
    for (i = 0; environ[i] != NULL; i++)
    {
        if (strncmp(string, environ[i], num_end + 1) == 0)
        {
            environ[i] = string;
            return 0;
        }
    }

    //if variable does not exit
    len = sizeof(environ) / sizeof(environ[0]);
    char **new_environ = malloc(sizeof(char *) * (len + 2));
    if (new_environ == NULL)
    {
        perror("malloc");
        return 1;
    }

    for (i = 0; environ[i] != NULL; i++)
    {
        new_environ[i] = environ[i];
    }
    new_environ[len] = string;
    new_environ[len + 1] = NULL;

    free(environ);
    environ = new_environ;
    
    return 0;
}