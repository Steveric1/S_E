#include "main.h"

/**
 * check_working_dir - checks the working directory
 * @pwd: present working directory
 * @path: path
 * Return: path
*/
char *check_working_dir(char **pwd, char **path)
{
	char *str = NULL;

	if (**path == ':')
	{
		str = malloc(sizeof(char) * (_strlen(*pwd) + _strlen(*path) + 1));
		if (str == NULL)
		{
			free_all(2, *pwd, *path);
			return (NULL);
		}
		_strcpy(str, *pwd), _strcat(str, *path);
	}
	else if (_strstr(*path, "::") != NULL)
	{
		str = path_convert(*pwd, *path);
		if (str == NULL)
		{
			free_all(2, *pwd, *path);
			return (NULL);
		}
	}
	else
	{
		str = malloc(sizeof(char) * (_strlen(*path) + 1));
		if (str == NULL)
		{
			free_all(2, *pwd, *path);
			return (NULL);
		}
		_strcpy(str, *path);
	}
	return (str);
}

/**
 * path_convert - converts the path
 * @pwd: present working directory
 * @path: path
 * Return: path
 */
char *path_convert(char *pwd, char *path)
{
	int i, j = 0, n = 0;
	char *str;

	if (pwd == NULL || path == NULL)
		return (NULL);
	str = malloc(sizeof(char) * (_strlen(pwd) + _strlen(path) + 1));
	if (str == NULL)
	  return (NULL);
	for (i = 0; path[i] != '\0'; i++)
	{
		if (path[i] == ':' && path[i + 1] == ':')
		{
			str[n++] = ':';
			while (path[j])
			{
				str[n] = pwd[j];
				n++, j++;
			}
			str[n] = ':';
			while (path[i] == ':')
			    i++;
			i--;
		}
		else
		    str[n] = str[i];
		i++;
		n++;
	}
	str[n] = '\0';
	return (str);
}