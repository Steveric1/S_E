#include "main.h"

/******************MY_TOKEN FUNCTION*************/
/**
 * my_token - tokenizes a string
 * @str: string to tokenize
 * @delim: delimiter
 * Return: pointer to the next token
 */
char *my_token(char *str, const char *delim)
{
   static s_strtok my_strtok;
   char *start, *end;

   if (str != NULL)
       my_strtok.current = str;
    if (my_strtok.current == NULL || *(my_strtok.current) == '\0')
        return (NULL);/*no more tokens*/
    while (*(my_strtok.current) != '\0' && _strchr(delim, *(my_strtok.current)) != NULL)
        (my_strtok.current)++;/*skip delimiters*/
    if (*(my_strtok.current) == '\0')
        return (NULL);/*no more tokens*/
    start = my_strtok.current;
    end = str_pointer_break(start, delim);

    if (end != NULL) {
        *end = '\0';
        my_strtok.current = end + 1;/*move current to next token*/
    }else {
        my_strtok.current = NULL;
    }

    return (start);
}

/**
 * exec - executes a command
 * @av: array of arguments
 * Return: void
 */

void exec(char **arg)
{
    char *command_exec = NULL;
    char *cmd_path = NULL;

    if (arg != NULL)
    {
        command_exec = arg[0];
        cmd_path = handle_path(command_exec);
        if (cmd_path != NULL)
            command_exec = cmd_path;
        handle_builtin_command(command_exec, arg);
        if (execve(command_exec, arg, environ) == -1)
        {
            perror("./prompt");
            free(cmd_path);
            exit(EXIT_FAILURE);
        }

        free(cmd_path);
    }
}

/**
 * handle_path - handles the path
 * @cmd: command
 * Return: pointer to the path
 */

void *handle_path(char *cmd)
{
    char *path, *cmd_path;
    struct stat st;

    path = _getenv("PATH");
    if (path != NULL)
    {
        cmd_path = path_convert(path, cmd);
        if (cmd_path != NULL)
        {
            if (stat(cmd_path, &st) == 0)
                return (cmd_path);
            free(cmd_path);
        }
    }
    
    return (NULL);
}
