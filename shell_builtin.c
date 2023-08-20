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
        write(STDOUT_FILENO, environ[i], _strlen(environ[i]));
        write(STDOUT_FILENO, "\n", 1);
        i++;
    }
}

/**
 * _setenv - sets an environment variable
 * @name: name of the variable
 * @value: value of the variable
 * @check_overwrite: function to check if the variable already exists
 * Return: 0 on success, -1 on failure
*/
int _setenv(const char *name, const char *value)
{
    int len = 0;
    char *new_string = NULL, *existing = NULL;

    len = _strlen(name) + _strlen(value) + 2;
    new_string = malloc(sizeof(char) * len);

    if (new_string == NULL)
    {
        write(STDERR_FILENO, "Error: malloc failed\n", 21);
        return (-1);
    }

    _strcpy(new_string, name);
    _strcat(new_string, "=");
    _strcat(new_string, value);

    /*Initialize a new environment or modify existing one*/
    if (_putenv(new_string) != 0)
    {
        write(STDERR_FILENO, "Error: putenv failed\n", 21);
        free(new_string);
        return (-1);
    }

    /*free(new_string);*/
    return (0);
}

/**
 * _unsetenv - unsets an environment variable
 * @name: name of the variable
 * Return: 0 on success, -1 on failure
*/
int _unsetenv(const char *name)
{
    int i, j, len = 0;
    int environ_len = 0, found = 0;
    char **new_environ = NULL;

    len = _strlen(name);
    while (environ[environ_len] != NULL)
        environ_len++;
    
    for (i = 0; environ[i] != NULL; i++)
    {
        if (strncmp(environ[i], name, len) == 0)
        {
            found = 1;
            free(environ[i]);
            for (j = i; environ[j] != NULL; j++)
                environ[j] = environ[j + 1];
            environ_len--;
            break;
        }
    }

    /*if not found return 0*/
    if (found == 0)
        return (0);
    new_environ = malloc(sizeof(char *) * (environ_len + 1));
    if (new_environ == NULL)
    {
        write(STDERR_FILENO, "Error: malloc failed\n", 21);
        return (-1);
    }

    for (i = 0; environ[i] != NULL; i++)
        new_environ[i] = environ[i];
    new_environ[i] = NULL;

    free(environ);
    environ = new_environ;
    return (0);
}