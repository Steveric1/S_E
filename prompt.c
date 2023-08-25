#include "main.h"
#include "getline.h"

/**
 * main - main function
 * @argc: number of arguments
 * @av: arguments
 * Return: 0 on success, 1 on failure
*/

int main(int argc __attribute__((unused)), char **av)
{
    int count = 0, status, return_val;
    pid_t child;

    signal(SIGINT, handle_ctrl_c);

    while (1)
    {
        return_val = simple_shell_loop(av, count);
        if (return_val == 2)
        {
            count++;
            child = fork();

            if (child == -1)
            {
                perror("Error");
                exit(EXIT_FAILURE);
            }
            else if (child != 0)
            {
                wait(&status);
                return (127);
            }
            else
                continue;
        }
        if (return_val != 0)
            break;
        count++;
    }
    return (0);
}