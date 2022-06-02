/*
** EPITECH PROJECT, 2022
** mysh.h
** File description:
** .h containing all protos for mysh project
*/

#ifndef MYSH_H_
    #define MYSH_H_
    #define ERROR 84

int bin_call(char **input, char **env);
int cd_replace_env(char **input, char *old_pwd, char **env);
int cd_cmd(char **input, char **env);
char *get_env_line_name(char **env, int line);
int unsetenv_cmd(char **input, char **env);
int setenv_cmd(char **input, char **env);
int env_cmd(char **input, char **env, int from_setenv);
int extra_cmd(char **input, int *state, char **env);
int bin_call(char **array, char **env);
int exec_cmd(char **input_array, int *state, char **env);
int error_handling(int ac);

#endif
