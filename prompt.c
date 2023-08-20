#include "main.h"

/**
 * main - main function of the shell
 * @ac: argument count
 * @av: argument vector
 * Return: 0 on success
 */

int main(int ac, char **av)
{
    ssize_t nread;
    char *lineptr = NULL;
    size_t size = 0;
    char buffer[12] = "my_shell$ ";
    char *line_copy, *token, delim[] = " ";
    int token_count, i, status;
    pid_t child;


    (void)ac;

    write(STDOUT_FILENO, buffer, 11);

    while (1)
    {
        nread = my_getline(&lineptr, &size, stdin);
        if (nread == -1)
        {
            free(lineptr);
            return -1;
        }

        line_copy = malloc(sizeof(char) * nread + 1);
        if (line_copy == NULL)
        {
            perror("malloc");
            free(lineptr);
            exit(EXIT_FAILURE);
        }
        _strcpy(line_copy, lineptr);
        token = my_token(line_copy, delim);
        token_count = 0;

        while (token != NULL) {
            token = my_token(NULL, delim);
            token_count++;
        }

        av = malloc(sizeof(char *) * (token_count + 1));
        if (av == NULL) {
            free(line_copy);
            return -1;
        }

        token = my_token(lineptr, delim);
        for (i = 0; i < token_count; i++) {
            av[i] = malloc(sizeof(char) * _strlen(token) + 1);
            if (av[i] == NULL) {
                free(line_copy);
                free(av);
                return -1;
            }
            _strcpy(av[i], token);
            token = my_token(NULL, delim);
        }
        av[i] = NULL;

        child = fork();
        if (child < 0) {
            perror("fork");
            free(line_copy);
            for (i = 0; i < token_count; i++)
               free(av[i]);
            free(av);
            exit(EXIT_FAILURE);
        } else if (child == 0) {
            exec(av);
        } else {
            wait(&status);
            if (strcmp(av[0], "exit") == 0)
            {
                shell_exit(av[0], av[1]);
            }
            free(line_copy);
            for (i = 0; i < token_count; i++)
                free(av[i]);
            free(av);
        }
        write(STDOUT_FILENO, buffer, 11);
    }

    free(lineptr);
    exit(EXIT_SUCCESS);
}