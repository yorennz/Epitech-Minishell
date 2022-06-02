/*
** EPITECH PROJECT, 2022
** extra_commands
** File description:
** handle extern commands of /bin/ needed by minishell
*/

#include <unistd.h>
#include <stddef.h>
#include "my.h"
#include "mysh.h"

int env_cmd(char **input, char **env, int from_setenv)
{
    if (from_setenv == 0 && input[1] != NULL) {
        if (input[1][my_strlen(input[1]) - 1] == '/' &&
access(input[1], R_OK) == 0) {
            write(2, "env: '", 6);
            write(2, input[1], my_strlen(input[1]));
            write(2, "': Permission denied\n", 21);
            return 126;
        } else {
            write(2, "env: '", 6);
            write(2, input[1], my_strlen(input[1]));
            write(2, "': No such file or directory\n", 29);
            return  127;
        }
    }
    for (int i = 0; env[i] != NULL; i++)
        my_printf("%s\n", env[i]);
    return 0;
}

int exit_cmd(char **input, int *state, char **env)
{
    int exit_val = 0;

    if (my_arraylen(input) == 1)
        state[0] = 0;
    if (input[1] != NULL) {
        if (my_arraylen(input) == 2 && my_str_isnum(input[1]) == 1) {
            exit_val = my_getnbr(input[1]);
            state[0] = 0;
            my_putstr("exit\n");
        } else {
            write(2, "exit: Expression Syntax.\n", 25);
            exit_val = 1;
        }
    }
    return exit_val;
}

int extra_cmd(char **input, int *state, char **env)
{
    if (my_strcmp(input[0], "cd") == 1)
        return cd_cmd(input, env);
    if (my_strcmp(input[0], "setenv") == 1)
        return setenv_cmd(input, env);
    if (my_strcmp(input[0], "unsetenv") == 1)
        return unsetenv_cmd(input, env);
    if (my_strcmp(input[0], "env") == 1)
        return env_cmd(input, env, 0);
    if (my_strcmp(input[0], "exit") == 1)
        return exit_cmd(input, state, env);
    return -667;
}
