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
    char buffer[20] = "my_shell$ ";
    char *line_copy, *token, delim[] = " ";
    int token_count, i;
    pid_t child;


    (void)ac;

    write(STDOUT_FILENO, buffer, 20);
    fflush(stdout);/*flushes the output buffer of a stream*/

    while (1)
    {
        nread = my_getline(&lineptr, &size, stdin);
        if (nread ==  -1 || nread == EOF)
           return (-1);

        line_copy = malloc(sizeof(char) * nread);
        if (line_copy == NULL)
        {
            perror("malloc");
            exit(EXIT_FAILURE);
        }

        strcpy(line_copy, lineptr);
        token = my_token(line_copy, delim);
        token_count = 0;

        while (token != NULL)
        {
            token = my_token(NULL, delim);
            token_count++;
        }

        av = malloc(sizeof(char *) * (token_count + 1));
        if (av == NULL)
        {
            perror("malloc");
            exit(EXIT_FAILURE);
        }

        token = my_token(lineptr, delim);
        for (i = 0; i < token_count && token != NULL; i++)
        {
            av[i] = malloc(sizeof(char) * strlen(token) + 1);
            if (av[i] == NULL){
                perror("malloc");
                exit(EXIT_FAILURE);
            }
            strcpy(av[i], token);
            token = my_token(NULL, delim);
        }
        av[i] = NULL;

        child = fork();
        if (child < 0)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (child == 0) {
            execute(av, av[1]);
            /*child cleanup*/
            free(lineptr);
            free(av);
            exit(EXIT_SUCCESS);
        } else {
            if (strcmp(av[0], "env") == 0)
            {
                shell_env();/*print environment*/
            }

            if (strcmp(av[0], "exit") == 0)
            {
                shell_exit(av[0], av[1]);
                free(lineptr);
                free(av);
                exit(EXIT_SUCCESS); /*Exit the shell*/
            }
        }

        write(STDOUT_FILENO, buffer, 20);
    }

    free(lineptr);
    exit(EXIT_SUCCESS);
}