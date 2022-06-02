/*
** EPITECH PROJECT, 2021
** mysh
** File description:
** mysh
*/

#include <stdlib.h>
#include <stdio.h>
#include "my.h"
#include "mysh.h"

int mysh(char **env)
{
    int ret = 0;
    size_t input_size = 32;
    size_t characters;
    char *input = malloc(sizeof(char) * (input_size + 1));
    char **input_array;

    for (int state = 1; state == 1;) {
        my_putstr("$> ");
        characters = getline(&input, &input_size, stdin);
        if (characters != -1) {
            input_array = my_str_to_word_array(input, ' ');
            ret = exec_cmd(input_array, &state, env);
        } else {
            my_putchar('\n');
            state = 0;
        }
    }
    free(input);
    return ret;
}

int main(int ac, char **av, char **env)
{
    if (error_handling(ac) == ERROR)
        return ERROR;
    return mysh(env);
}
