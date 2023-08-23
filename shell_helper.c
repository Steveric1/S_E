#include "main.h"

/**
 * is_empty - checks if a string is empty
 * @str: string to check
 * return: true if empty, false if not
 */

bool is_empty(const char *str) {
    while (*str != '\0') {
        if (!_isspace(*str)) {
            return false;
        }
        str++;
    }
    return true;
}

/*int tokenization(char *line_cp, char *delim, int *token_count)
{
    char *token;
    token = my_token(line_cp, delim);
    while (token != NULL) {
        token = my_token(NULL, delim);
        *token_count += 1;
    }
    return (*token_count);
}*/

/**
 * print_prompt - prints the prompt
 * @is_interactive: checks if the shell is interactive
 * Return: void
 */
void print_prompt(int is_interactive)
{
    if (isatty(is_interactive)) {
        write(STDOUT_FILENO, "my_shell$ ", 10);
    }
}

/**
 * read_input - reads the input from the user
 * @line: line
 * @n: n
 * @stream: stream
*/
/*ssize_t read_input(char **line, size_t *n, FILE *stream)
{
    ssize_t nread;
    nread = getline(line, n, stream);
    if (nread == -1 || nread == EOF) {
        free(*line);
        return -1;
    }
    return nread;
}*/