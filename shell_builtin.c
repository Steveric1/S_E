#include "main.h"

/**
 * shell_exit - exits the shell
 * @exit_the_shell: string to compare with exit
 * Return: void
*/
void shell_exit(char *exit_the_shell, char *args)
{
    int status;
    if (strcmp(exit_the_shell, "exit") == 0)
    {
        if (args != NULL)
        {
            status = atoi(args);
        } else {
            status = 0;
        }
        exit(status); /*Exit the shell*/
    }
}

/**
 * shell_env - prints the environment
 * Return: void
*/
void shell_env()
{
    int i = 0;
    while (environ[i] != NULL)
    {
        write(STDOUT_FILENO, environ[i], strlen(environ[i]));
        write(STDOUT_FILENO, "\n", 1);
        i++;
    }
}