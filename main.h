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
extern s_strtok my_strtok;

/*getline function*/
ssize_t my_getline(char **buffer, size_t *len, FILE *stream);
/*strtok function*/
char *my_token(char *str, const char *delim);
/*Setenv function*/
int _setenv(const char *name, const char *value);
/*Unsetenv function*/
int _unsetenv(const char *name);


#endif/*MAIN_H*/