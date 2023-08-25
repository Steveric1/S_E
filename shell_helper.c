#include "main.h"
#include "getline.h"

/**
 * printerror - prints error message
 * @av: name of the program
 * @count: number of commands entered
 * @arg: command entered
 * Return: void
*/

void printerror(char **av, int count, char **arg)
{
	write(STDERR_FILENO, av[0], _strlen(av[0]));
	write(STDERR_FILENO, ": ", 2);
	write_error_stderr(count);
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, arg[0], _strlen(arg[0]));
	write(STDERR_FILENO, ": not found\n", 12);
}

/**
 * prompt - prompts the user for input
 * @buffer: buffer to store input
 * Return: number of bytes read
*/
int prompt(char **buffer)
{
	ssize_t nread = 0;
	size_t size = 0;
	int is_interactive = isatty(STDIN_FILENO);

	if (is_interactive != 0)
	    write(STDOUT_FILENO, "my_shell$ ", 10);
	nread = my_getline(buffer, &size, stdin);

	return (nread);
}

/**
 * handle_ctrl_c - handles ctrl + c signal
 * @sig: signal
*/
void handle_ctrl_c(int sig __attribute__((unused)))
{
	write(1, "\nmy_shell$ ", 12);
	signal(SIGINT, handle_ctrl_c);
}

/**
 * free_all - frees all memory
 * @n: number of arguments
 * Return: void
*/
void free_all(const unsigned int n, ...)
{
	va_list args;
	unsigned int i;
	char *ptr;

	va_start(args, n);
	for (i = 0; i < n; i++)
	{
		ptr = va_arg(args, char *);
		free(ptr);
	}
	va_end(args);
}
/**
 * free_arg - frees an array of strings
 * @arr: array of strings
*/
void free_arg(char **arr)
{
	free(arr);
}
