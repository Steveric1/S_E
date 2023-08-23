#include "main.h"
#include "getline.h"

/**
 * main_helper - helper function for main
 * @av: argument vector
 * @size: size
 * @nread: number of bytes read
 * Return: 0 on success, -1 on failure
*/
int main_helper(char **av, size_t size, ssize_t nread)
{
    char *lineptr = NULL, *line_copy, *token, delim[] = " ";
    int token_count, i, is_interactive;
    is_interactive = isatty(STDIN_FILENO);
    print_prompt(is_interactive);

    while (1)
    {
        nread = my_getline(&lineptr, &size, stdin);
        if (nread == -1 || nread == EOF) {
            free(lineptr);
            return -1;
        }
        if (is_empty(lineptr)) {
            print_prompt(is_interactive);
            continue;
        }
        line_copy = malloc(sizeof(char) * nread + 1);
        if (line_copy == NULL){
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
        for (i = 0; i < token_count && token != NULL; i++) {
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
        handle_child(line_copy, av, token_count);
        print_prompt(is_interactive);
    }
    free(lineptr);
    exit(EXIT_SUCCESS);
}

/**
 * main - main function of the shell
 * @ac: argument count
 * @av: argument vector
 * Return: 0 on success
 */

int main(int ac __attribute__((unused)), char **av)
{
    ssize_t nread = 0;
    size_t size = 0;
 
    main_helper(av, size, nread);
    return (0);
}

