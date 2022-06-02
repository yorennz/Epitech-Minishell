/*
** EPITECH PROJECT, 2022
** commands
** File description:
** execute commands typed in minishell by user
*/

#include <sys/types.h>
#include <sys/wait.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "my.h"
#include "mysh.h"

int check_ret(int ret)
{
    int signal = 0;

    if (WIFSIGNALED(ret)) {
        signal = WTERMSIG(ret);
        if (ret == 512)
            return 2;
        if (signal == 8)
            my_putstr("Floating exception");
        if (signal == 11)
            my_putstr("Segmentation fault");
        if (WCOREDUMP(ret) && (signal == 8 || signal == 11))
            my_putstr(" (core dumped)\n");
        if (!WCOREDUMP(ret) && (signal == 8 || signal == 11))
            my_putchar('\n');
        return ret;
    }
    return WEXITSTATUS(ret);
}

int exec_cmd(char **input_array, int *state, char **env)
{
    pid_t child_pid;
    int ret = 0;

    if (input_array[0] == NULL)
        return 0;
    ret = extra_cmd(input_array, state, env);
    if (ret == -667)
        child_pid = fork();
    if (ret == -667 && child_pid == 0)
        ret = bin_call(input_array, env);
    if (ret == -667 && child_pid != 0)
        waitpid(child_pid, &ret, 0);
    return check_ret(ret);
}
