#ifndef GETLINE_H
#define GETLINE_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

/*define macro*/
#define READ_SIZE 1024
#define READ_SIZE_INCREMENT 1024

/*prototypes*/
void init_buffer(char **buffer, size_t *size);
ssize_t read_into_buffer(char *buffer, size_t len, FILE *stream);
void expand_buffer(char **buffer, size_t *len);
ssize_t perform_getline(char *buffer, size_t len, size_t *i, ssize_t r);
ssize_t my_getline(char **buffer, size_t *len, FILE *stream);
#endif /*GETLINE_H*/