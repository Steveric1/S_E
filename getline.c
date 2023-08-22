#include "getline.h"

/**
 * init_buffer - initialize buffer
 * @buffer: buffer
 * @size: size of buffer
 * Return: void
*/
void init_buffer(char **buffer, size_t *size)
{
    *buffer = malloc(READ_SIZE);
    if (*buffer == NULL)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    *size = READ_SIZE;
}

/**
 * read_into_buffer - read into buffer
 * @buffer: buffer
 * @len: length of buffer
 * @stream: stream
 * Return: ssize_t
*/
ssize_t read_into_buffer(char *buffer, size_t len, FILE *stream)
{
    ssize_t r;
    r = read(fileno(stream), buffer, len);
    if (r == -1)
    {
        perror("read");
        return (-1);
    }
    return (r);
}

/**
 * expand_buffer - expand buffer
 * @buffer: buffer
 * @len: length of buffer
 * Return: void
*/
void expand_buffer(char **buffer, size_t *len)
{
    char *new_buffer;
    new_buffer = realloc(*buffer, *len + READ_SIZE_INCREMENT);
    if (new_buffer == NULL)
    {
        perror("realloc");
        free(*buffer);
        exit(EXIT_FAILURE);
    }

    *buffer = new_buffer;
    *len += READ_SIZE_INCREMENT;
}

/**
 * perform_getline - perform getline
 * @buffer: buffer
 * @len: length of buffer
 * @i: index
 * @r: read
 * Return: ssize_t
*/
ssize_t perform_getline(char *buffer, size_t len, size_t *i, ssize_t r)
{
    size_t char_read = 0;
    size_t total_r;

    total_r = r;
    *i = 0;

    while (*i < total_r && r != 0)
    {
        if (buffer[*i] == '\n')
        {
            buffer[*i] = '\0';
            return (char_read);
        }

        if (*i == len - 1)
        {
            expand_buffer(&buffer, &len);
        }

        (*i)++;
        char_read++;
    }

    *i = 0;
    total_r = 0;

    return (char_read);
}

/**
 * my_getline - get line
 * @buffer: buffer
 * @len: length of buffer
 * @stream: stream
 * Return: ssize_t
*/
ssize_t my_getline(char **buffer, size_t *len, FILE *stream)
{
    static size_t i;
    ssize_t r, char_read = 0;

    if (buffer == NULL || len == NULL || stream == NULL) {
        errno = EINVAL;
        return -1;
    }

    if (*buffer == NULL || *len == 0)
    {
        init_buffer(buffer, len);
    }

    fflush(stdout);/*flush standar output*/
    r = read_into_buffer(*buffer, *len, stream);
    if (r == 0)
    {
        free(*buffer);
        *buffer = NULL;
        *len = 0;
        return (-1);
    }

    char_read = perform_getline(*buffer, *len, &i, r);
    return (char_read);
}