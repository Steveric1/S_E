#include "main.h"

/**
 * cd_command - change directory
 * @dir: directory to change to
 * Return: 0 on success, -1 on failure
*/
int cd_command(char *dir) {
   
    char *home_dir, current_dir[DIR_SIZE];
    home_dir = _getenv("HOME");
    if (home_dir != NULL) 
    {
        if (dir == NULL) {
            dir = home_dir;
        }
    }else {
        perror("_getenv");
        return (-1);
    }
    if (getcwd(current_dir, sizeof(current_dir)) == NULL) {
        perror("getcwd");
        return (-1);
    }

    if (_strcmp(dir, "-") == 0) {
        dir = _getenv("OLDPWD");
        if (dir == NULL) {
            perror("_getenv");
            return (-1);
        }
    } 
    if (cmd_helper(current_dir, dir) != 0) {
        return (-1);
    }
    if (change_direc(dir) != 0) {
        return (-1);
    }
    if (get_working_dir(dir) != 0) {
        return (-1);
    }

    return 0;
}

/**
 * cmd_helper - helper function for cd
 * @current_direc: current directory
 * @dir: directory
 * Return: 0 on success, -1 on failure
*/
int cmd_helper(char *current_direc, const char *dir __attribute__((unused)))
{
    if (_setenv("OLDPWD", current_direc) != 0) {
        perror("_setenv");
        return (-1);
    }

    return (0);
}

/**
 * change_direc - changes the directory
 * @dir: directory
 * Return: 0 on success, -1 on failure
*/
int change_direc(const char *dir)
{
    if (chdir(dir) != 0) {
        return (-1);
    }
    return (0);
}

/**
 * get_working_dir - gets the working directory
 * @dir: directory
 * Return: 0 on success, -1 on failure
*/
int get_working_dir(const char *dir __attribute__((unused)))
{
    char new_pwd[DIR_SIZE];
    if (getcwd(new_pwd, sizeof(new_pwd)) == NULL) {
        perror("getcwd");
        return (-1);
    }else if (_setenv("PWD", new_pwd) != 0) {
        perror("_setenv");
        return (-1);
    }
    return (0);
}
