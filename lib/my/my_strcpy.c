/*
** EPITECH PROJECT, 2021
** my_strcpy.c
** File description:
** Write a function that copies a string into another
*/

#include <stdio.h>

char *my_strcpy(char *dest, char const *src)
{
    int j = 0;
    for (int i = 0; src[i] != '\0'; i += 1) {
        dest[i] = src[i];
        j += 1;
    }
    dest[j] = '\0';
    return (dest);
}
