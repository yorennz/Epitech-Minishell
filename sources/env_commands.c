/*
** EPITECH PROJECT, 2022
** env_commands
** File description:
** all functions about env
*/

#include <unistd.h>
#include <stdlib.h>
#include <stddef.h>
#include "my.h"
#include "mysh.h"

char *get_env_line_name(char **env, int line)
{
    char *line_name;
    int size = 0;
    int pos = 0;

    while (env[line][pos] != '=' && env[line][pos] != '\0') {
        size++;
        pos++;
    }
    line_name = malloc(sizeof(char) * (size + 1));
    line_name[size] = '\0';
    for (int i = 0; i < size; i++)
        line_name[i] = env[line][i];
    return line_name;
}

int check_to_unset_line(char *input, char **env)
{
    char *line_name;
    int pos = 0;
    int env_size = my_arraylen(env);
    int unset = 0;

    while (env[pos] != NULL && unset == 0) {
        line_name = get_env_line_name(env, pos);
        if (my_strcmp(input, line_name) == 1)
            unset = 1;
        free(line_name);
        if (unset == 0)
            pos++;
    }
    for (int j = pos; unset == 1 && j <= env_size + 1; j++)
        if (j != env_size)
            env[j] = env[j + 1];
        else
            free(env[j]);
    return unset;
}

int unsetenv_cmd(char **input, char **env)
{
    int unset = 0;

    if (input[1] == NULL) {
        my_putstr("unsetenv: Too few arguments.\n");
        return 1;
    }
    for (int i = 1; input[i] != NULL; i++) {
        if (unset == 0)
            unset = check_to_unset_line(input[i], env);
        else
            check_to_unset_line(input[i], env);
    }
    if (unset == 0)
        return 1;
    return unset;
}

void set_line(char **input, char **env, int env_line, int exist)
{
    int input_size = my_arraylen(input);
    int env_size = my_arraylen(env);
    char *temp_str = my_strcat(input[1], "=");

    if (exist == 1) {
        if (input_size == 3)
            env[env_line] = my_strcat(temp_str, input[2]);
        else
            env[env_line] = my_strdup(temp_str);
    }
    if (env_line == -1 && exist == 0) {
        if (input_size == 3)
            env[env_size] = my_strcat(temp_str, input[2]);
        else
            env[env_size] = my_strdup(temp_str);
        env[env_size + 1] = NULL;
    }
    free(temp_str);
    return;
}

int setenv_cmd(char **input, char **env)
{
    char *line_name;
    int exist = 0;

    if (my_arraylen(input) == 1)
        return env_cmd(input, env, 1);
    if (my_arraylen(input) > 3) {
        my_putstr("setenv: Too many arguments.\n");
        return 1;
    }
    for (int i = 0; exist == 0 && env[i] != NULL; i++) {
        line_name = get_env_line_name(env, i);
        if (my_strcmp(line_name, input[1]) == 1) {
            exist = 1;
            set_line(input, env, i, exist);
        }
        free(line_name);
    }
    set_line(input, env, -1, exist);
    return 0;
}
