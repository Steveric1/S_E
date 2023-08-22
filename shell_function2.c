#include "main.h"

/**
 * handle_child - handles the child process
 * @line_copy: copy of the line
 * @av: array of arguments
 * @token_count: number of tokens
 * Return: void
*/
void handle_child(char *line_copy, char **av, int token_count)
{
    int status, i;
    pid_t child;
    child = fork();
    
    if (child == -1)
    {
        perror("fork");
        free(line_copy);
        for (i = 0; i < token_count; i++)
            free(av[i]);
        free(av);
        exit(EXIT_FAILURE);
    } else if (child == 0) 
    {
        exec(av);
    } else 
    {
        wait(&status);
        if (_strcmp(av[0], "cd") == 0)
        {
            cd_command(av[1]);
        }

        if (_strcmp(av[0], "exit") == 0)
        {
            shell_exit(av[0], av[1]);
        }
        free(line_copy);
        for (i = 0; i < token_count; i++)
            free(av[i]);
        free(av);
    }
}

/**
 * handle_builtin_command - handles the built-in commands
 * @command_exec: command to execute
 * @arg: arguments
 * Return: 0 on success, -1 on failure
*/

int handle_builtin_command(char *command_exec, char **arg)
{
    char current_dir[DIR_SIZE];
    if (_strcmp(command_exec, "setenv") == 0) /*Handle setenv*/
    {
        _setenv(arg[1], arg[2]);
        exit(EXIT_SUCCESS);
    } else if (_strcmp(command_exec, "unsetenv") == 0) {
        _unsetenv(arg[1]);
        exit(EXIT_SUCCESS);
    }else if (_strcmp(command_exec, "cd") == 0) {
        int result = cd_command(arg[1]);
        if (result == -1)
        {
            perror("cd");
        } else if (_strcmp(arg[1], "-") == 0)
        {
            if (getcwd(current_dir, sizeof(current_dir)) != NULL)
            {
               write(STDOUT_FILENO, current_dir, _strlen(current_dir));
               write(STDOUT_FILENO, "\n", 1);
            }
        }
        exit(EXIT_SUCCESS);
    } else if (_strcmp(command_exec, "env") == 0){
        shell_env();
        exit(EXIT_SUCCESS);
    } else {
        shell_exit(command_exec, arg[1]);
    }
    return (0);
}

/**
 * path_convert - converts the path
 * @path: path
 * @cmd: command
 * Return: path
*/
char *path_convert(const char *path, const char *cmd)
{
    char *token_path, *path_copy, *cmd_path, *delim = ":";
    int cmd_len, path_len;
    struct stat st;

    path_copy = strdup(path);
    if (path_copy == NULL)
    {
        perror("strdup");
        exit(EXIT_FAILURE);
    }
    token_path = my_token(path_copy, delim);
    while (token_path != NULL)
    {
        path_len = _strlen(token_path);
        cmd_len = _strlen(cmd);
        cmd_path = malloc(sizeof(char) * (path_len + cmd_len + 2));
        if (cmd_path == NULL)
        {
            perror("malloc");
            exit(EXIT_FAILURE);
        }
        _strcpy(cmd_path, token_path);
        _strcat(cmd_path, "/");
        _strcat(cmd_path, cmd);
        if (stat(cmd_path, &st) == 0) {
            free(path_copy);
            return (cmd_path);
        } else {
            free(cmd_path);
            token_path = my_token(NULL, delim);
        }
    }
    free(path_copy);
    return (NULL);
}