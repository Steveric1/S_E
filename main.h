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
#include <stdarg.h>

/*macros*/
#define DIR_SIZE 1024
#define IN 1
#define OUT 0

/*prototypes*/
int exec(char **arg_es, char **arg, char *buffer, int count);
void *handle_path(char **cmd);
int check_builtin(char **av, char *buffer, int count);
void print_env(void);
char *_strchr(const char *s, int c);
char *_strstr(const char *haystack, const char *needle);
char *str_pointer_break(char *str1, const char *str2);
char *_getenv(const char *name);
char *_strcat(char *dest, const char *src);
size_t _strlen(const char *s);
char *_strcpy(char *dest, const char *src);
int _putenv(char *string);
int _strcmp(char *s1, char *s2);
int _strncmp(const char *s1, const char *s2, size_t n);
int _isspace(int c);
void handle_ctrl_c(int sig __attribute__((unused)));
int prompt(char **buffer);
int word_counter(char *str, char *seperator);
char *path_initialize(char **pwd);
char *_strdup(char *str);
int write_error_stderr(int error);
void printerror(char **av, int count, char **arg);
void free_arg(char **arr);
void free_all(const unsigned int n, ...);
char **argument_seperator(char *buffer, char *seperator);

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
char *path_convert(char *pwd, char *path);
char *check_working_dir(char **pwd, char **path);
/*Helper function for cd*/
int cmd_helper(char *current_direc, const char *dir);
int change_direc(const char *dir);
int get_working_dir(const char *dir);
int simple_shell_loop(char **argv, int count);

#endif/*MAIN_H*/