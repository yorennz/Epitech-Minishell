/*
** EPITECH PROJECT, 2022
** bin_commands
** File description:
** contains all functions needed to exec bin commands
*/

#include <sys/types.h>
#include <sys/wait.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include "my.h"
#include "mysh.h"

int disp_cmd_not_found(char **input)
{
    my_printf("%s: Command not found.\n", input[0]);
    exit(1);
}

char **find_path_line(char **input, char **env)
{
    char *path;
    char **path_array;

    for (int i = 0; env[i] != NULL; i++)
        if (env[i][0] == 'P' && env[i][1] == 'A' && env[i][2] == 'T'
&& env[i][3] == 'H' && env[i][4] == '=') {
            path = my_strdup(env[i]);
            break;
        }
    path += 5;
    path_array = my_str_to_word_array(path, ':');
    path -= 5;
    free(path);
    return path_array;
}

void find_bin_and_exec(char **input, char **new_av, char **env)
{
    char *bin;
    char *temp_path;
    char **path_array = find_path_line(input, env);
    int pos = 0;

    for (; path_array[pos] != NULL; pos++) {
        temp_path = my_strcat(path_array[pos], "/");
        bin = my_strcat(temp_path, input[0]);
        free(temp_path);
        if (execve(bin, new_av, env) == -1)
            free(bin);
    }
    for (int i = 0; i <= pos; i++)
        free(path_array[i]);
    free(path_array);
    return;
}

int bin_call(char **input, char **env)
{
    int ret = 0;
    int size = my_arraylen(input);
    char *new_av[size + 1];

    for (int i = 0; i <= size; i++) {
        if (i < size)
            new_av[i] = my_strdup(input[i]);
        else
            new_av[i] = NULL;
    }
    if (execve(input[0], new_av, env) == -1) {
        find_bin_and_exec(input, new_av, env);
        ret = disp_cmd_not_found(input);
    }
    for (int j = 0; j <= size; j++)
        free(new_av[j]);
    return ret;
}
