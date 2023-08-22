#include "main.h"

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
    int i;
    char *delimeter, **new_environ;

    delimeter = _strchr(string, '=');
    if (string == NULL || delimeter == NULL || delimeter == string)
    {
        write(STDERR_FILENO, "Error: invalid argument\n", 24);
        return (1);
    }
    /*check if variable exit*/
    for (i = 0; environ[i] != NULL; i++)
    {
        if (_strncmp(string, environ[i], delimeter - string + 1) == 0)
        {
            environ[i] = string;
            return (0);
        }
    }
    /*if variable doesn't exit*/
    while (environ[i] != NULL)
        i++;
    new_environ = malloc(sizeof(char *) * (i + 2));
    if (new_environ == NULL)
    {
        perror("malloc");
        return (1);
    }
    for (i = 0; environ[i] != NULL; i++)
        new_environ[i] = environ[i];
    new_environ[i] = string;
    new_environ[i + 1] = NULL;
    environ = new_environ;
    return 0;
}

/**
 *_strcmp - function that compare two string
 *@s1: The first string to compare
 *@s2: The second string to compare
 *Return: s1 - s2
 */
int _strcmp(char *s1, char *s2)
{
	int i;

	for (i = 0; s1[i] && s2[i]; i++)
	{
		if (s1[i] != s2[i])
		{
			return (s1[i]  - s2[i]);
		}
	}
	return (s1[i] - s2[i]);
}

/**
 * _strncmp - compares two strings
 * @s1: first string
 * @s2: second string
 * @n: number of bytes to be compared
 * Return: difference between the two strings
*/

int _strncmp(const char *s1, const char *s2, size_t n) {
    while (n > 0) {
        if (*s1 == '\0' && *s2 == '\0') {
            return 0;
        } else if (*s1 == *s2) {
            s1++;
            s2++;
            n--;
        } else {
            return (*s1 - *s2);
        }
    }
    return 0;
}