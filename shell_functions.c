#include "main.h"

/*******GETLINE FUNCTION******************/
/**
 * my_getline - reads an entire line from stream
 * @buffer: buffer to store the line
 * @len: length of the buffer
 * @stream: stream to read from
 * Return: number of characters read, -1 on failure
 */

ssize_t my_getline(char **buffer, size_t *len, FILE *stream)
{
    static size_t i;
    ssize_t r, char_read = 0;
    size_t total_r;
    char *new_buffer;

    if (buffer == NULL || len == NULL || stream == NULL)
    {
        errno = EINVAL;
        return (-1);
    }
    if (*buffer == NULL || *len == 0)
    {
        *buffer = malloc(1024);
        *len = 1024;
        if (*buffer == NULL)
            return -1;
    }

    fflush(stdout);/*flushes the output buffer of a stream*/
    r = read(fileno(stream), *buffer, *len);
    if (r == -1){
        perror("read");
        return (-1);
    }

    if (r == 0)
    {
        free(*buffer);
        *buffer = NULL;
        *len = 0;
        return (-1);
    }

    total_r = r;
    i = 0;

    while (i < total_r && r != 0)
    {
        if ((*buffer)[i] == '\n')
        {
            (*buffer)[i] = '\0';
            return (i);
        }

        if (i == *len - 1)
        {
            new_buffer = realloc(*buffer, *len + 1024);
            if (new_buffer == NULL)
            {
                free(*buffer);
                return (-1);
            }
            *buffer = new_buffer;
            *len += 1024;
        }

        /*break if read is zero*/
        if (r == 0)
           break;
        i++;
        char_read++;
    }

    /*reset i and total_r to zero*/
    i = 0;
    total_r = 0;

    return (char_read);
}

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

    if (end != NULL)
    {
        *end = '\0';
        my_strtok.current = end + 1;/*move current to next token*/
    }
    else
    {
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
    char *path, *token_path, *path_copy, *cmd_path, *delim = ":";
    int cmd_len, path_len;
    struct stat st;

    path = _getenv("PATH");
    if (path == NULL)
        return (NULL);

    if (path != NULL)
    {
        path_copy = strdup(path);
        if (path_copy == NULL)
        {
            perror("strdup");
            exit(EXIT_FAILURE);
        }

        token_path = my_token(path_copy, delim);
        while (token_path != NULL)
        {
            /*get length of token_path and cmd*/
            path_len = _strlen(token_path);
            cmd_len = _strlen(cmd);

            /*allocate memory for cmd_path*/
            cmd_path = malloc(sizeof(char) * (path_len + cmd_len + 2));
            if (cmd_path == NULL)
            {
                perror("malloc");
                exit(EXIT_FAILURE);
            }

            /*copy token_path to cmd_path*/
            _strcpy(cmd_path, token_path);
            _strcat(cmd_path, "/");
            _strcat(cmd_path, cmd);

            /*print cmd_path if it exists*/
            if (stat(cmd_path, &st) == 0)
            {
                free(path_copy);
                return (cmd_path);
            }
            else
            {
                /*free cmd_path if it doesn't exist and get next token_path*/
                free(cmd_path);
                token_path = my_token(NULL, delim);
            }
        }
    }

    /*free path_copy if cmd_path doesn't exist*/
    free(path_copy);
    /*check if cmd is a path*/
    if (cmd != NULL && stat(cmd, &st) == 0)
    {
       return (cmd);
    }

    return (NULL);
}
