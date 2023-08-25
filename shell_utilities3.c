#include "main.h"

/**
 * word_counter - counts the number of words in a string
 * @str: string to count
 * @seperator: seperator
 * Return: number of words
*/

int word_counter(char *str, char *seperator)
{
    int i, j, state, count = 0, is_sep;
    state = OUT;

    for (i = 0; str[i] != '\0'; i++)
    {
        is_sep = 0;
        for (j = 0; seperator[j] != '\0'; j++)
        {
            if (str[i] == seperator[j])
            {
                is_sep = 1;
                break;
            }
        }

        if (is_sep == 1)
        {
            state = OUT;
        }
        else if (state == OUT && str[i] != '\n')
        {
            state = IN;
            ++count;
        }
    }

    return (count);
}

/**
 * path_intialize - intializes the path
 * @pwd: pointer to the pwd
 * Return: pointer to the path
*/
char *path_initialize(char **pwd)
{
    char *path = NULL;
    path = _strdup(_getenv("PATH"));
    if (path == NULL)
    {
        free_all(1, *pwd);
        return (NULL);
    }
    return (path);
}

/**
 * _strdup - duplicates a string
 * @str: string to duplicate
 * Return: pointer to the new string
*/
char *_strdup(char *str)
{
    char *new_str;
    int i, len;

    if (str == NULL)
        return (NULL);
    len = _strlen(str);
    new_str = malloc(sizeof(char) * (len + 1));
    if (new_str == NULL)
        return (NULL);
    
    for (i = 0; str[i] != '\0'; i++)
        new_str[i] = str[i];
    new_str[i] = '\0';

    return (new_str);
}

/**
 * _strstr - locates a substring
 * @haystack: string to search
 * @needle: substring to search for
 * Return: pointer to the beginning of the located substring
*/
char *_strstr(const char *haystack, const char *needle)
{
    int i, j, k;

    for (i = 0; haystack[i] != '\0'; i++)
    {
        for (j = 0, k = i; needle[j] != '\0'; j++, k++)
        {
            if (needle[j] != haystack[k] || haystack[k] == '\0')
               break;
        }
        if (needle[j] == '\0')
            return ((char *)haystack + i);
    }
    return (NULL);
}

/**
 * write_error_stderr - writes an error to stderr
 * @error: error to write
 * Return: number of characters written
*/
int write_error_stderr(int error)
{
    int temp, char_count = 0;
    unsigned int num;

    if (error < 0)
    {
        error = -error;
        write(2, "-", 1);
        char_count++;
    }
    
    num = error;
    while (num / 10)
    {
        char_count += write_error_stderr(num / 10);
    }
    temp = (num % 10) + '0';
    write(2, &temp, 1);
    char_count++;
    return (char_count);
}