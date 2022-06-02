/*
** EPITECH PROJECT, 2022
** cd_commands
** File description:
** all functions about cd commands
*/

#include <unistd.h>
#include <stddef.h>
#include <stdlib.h>
#include <errno.h>
#include "my.h"
#include "mysh.h"

int cd_replace_env(char **input, char *oldpwd, char **env)
{
    char *line_name;
    char *pwd = getcwd(NULL, 0);
    int replaced = 0;

    for (int i = 0; replaced < 2 && env[i] != NULL; i++) {
        line_name = get_env_line_name(env, i);
        if (my_strcmp("OLDPWD", line_name) == 1) {
            env[i] = my_strcat("OLDPWD=", oldpwd);
            replaced++;
        }
        if (my_strcmp("PWD", line_name) == 1) {
            env[i] = my_strcat("PWD=", pwd);
            replaced++;
        }
        free(line_name);
    }
    return 0;
}

int exec_cd_minus(char **input, char *oldpwd, char **env)
{
    char *line_name;
    int found = 0;

    for (int i = 0; found == 0 && env[i] != NULL; i++) {
        line_name = get_env_line_name(env, i);
        if (my_strcmp("OLDPWD", line_name) == 1) {
            env[i] += 7;
            chdir(env[i]);
            env[i] -= 7;
            found = 1;
        }
        free(line_name);
    }
    if (found == 1)
        cd_replace_env(input, oldpwd, env);
    return 0;
}

int exec_cd_arg(char **input, char *oldpwd, char **env)
{
    errno = 0;
    if (my_strcmp(input[1], "-") == 1)
        return exec_cd_minus(input, oldpwd, env);
    chdir(input[1]);
    if (errno == ENOTDIR) {
        write(2, input[1], my_strlen(input[1]));
        write(2, ": Not a directory.\n", 19);
        return 1;
    } else if (errno == ENOENT) {
        write(2, input[1], my_strlen(input[1]));
        write(2, ": No such file or directory.\n", 29);
        return 1;
    } else
        cd_replace_env(input, oldpwd, env);
    return 0;
}

int exec_cd_noarg(char **input, char *oldpwd, char **env)
{
    char *line_name;
    int found = 0;

    for (int i = 0; found == 0 && env[i] != NULL; i++) {
        line_name = get_env_line_name(env, i);
        if (my_strcmp("HOME", line_name) == 1) {
            env[i] += 5;
            chdir(env[i]);
            env[i] -= 5;
            found = 1;
        }
        free(line_name);
    }
    cd_replace_env(input, oldpwd, env);
    return 0;
}

int cd_cmd(char **input, char **env)
{
    char *oldpwd = getcwd(NULL, 0);
    int input_size = my_arraylen(input);
    int ret = 0;

    if (input_size > 2) {
        write(2, "cd: Too many arguments.\n", 24);
        return 1;
    }
    if (input_size == 2)
        ret = exec_cd_arg(input, oldpwd, env);
    else
        ret = exec_cd_noarg(input, oldpwd, env);
    free(oldpwd);
    return ret;
}
