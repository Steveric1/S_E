#ifndef MAIN_H
#define MAIN_H

/* Libraries */
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <signal.h>
#include <sys/stat.h>
#include <stdbool.h>

/*macros*/
#define DIR_SIZE 1024

/*prototypes*/
void exec(char **args);
void *handle_path(char *cmd);
void shell_exit(char *exit_the_shell, char *args);
void shell_env();
char *_strchr(const char *s, int c);
char *str_pointer_break(char *str1, const char *str2);
char *_getenv(const char *name);
char *_strcat(char *dest, const char *src);
size_t _strlen(const char *s);
char *_strcpy(char *dest, const char *src);
int _putenv(char *string);
int _strcmp(char *s1, char *s2);
int _strncmp(const char *s1, const char *s2, size_t n);
int _isspace(int c);
bool is_empty(const char *str);

/*global variables*/
extern char **environ;
/*strtok struct declaration*/

/**
 * struct s_strtok - strtok struct
 * @current: current position of the string
 * Description: tokenizes a string
*/
typedef struct
{
    char *current;
}s_strtok;


/*strtok function*/
char *my_token(char *str, const char *delim);
/*Setenv function*/
int _setenv(const char *name, const char *value);
/*Unsetenv function*/
int _unsetenv(const char *name);
/*Change directory*/
int cd_command(char *dir);
/*Handle child function*/
void handle_child(char *line_copy, char **av, int token_count);
/*Handle builtin command*/
int handle_builtin_command(char *command_exec, char **arg);
/*Handle path conversion*/
char *path_convert(const char *path, const char *cmd);
/*Helper function for cd*/
int cmd_helper(char *current_direc, const char *dir);
int change_direc(const char *dir);
int get_working_dir(const char *dir);

/*Main function helper*/
void print_prompt(int is_interactive);
int main_helper(char **av, size_t size, ssize_t nread);
void print_prompt(int is_interactive);
/*ssize_t read_input(char **line, size_t *n, FILE *stream);*/
#endif/*MAIN_H*/