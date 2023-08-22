#include "main.h"

/**
 * cd_command - change directory
 * @dir: directory to change to
 * Return: 0 on success, -1 on failure
*/
int cd_command(char *dir) {
   
    char *home_dir, current_dir[DIR_SIZE], new_pwd[DIR_SIZE];
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

    if (_setenv("OLDPWD", current_dir) != 0) {
        perror("_setenv");
        return (-1);
    }

    if (chdir(dir) != 0) {
        return (-1);
    }

    if (getcwd(new_pwd, sizeof(new_pwd)) == NULL) {
        perror("getcwd");
        return (-1);
    }

    if (_setenv("PWD", new_pwd) != 0) {
        perror("_setenv");
        return (-1);
    }

    return 0;
}
