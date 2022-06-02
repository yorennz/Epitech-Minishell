/*
** EPITECH PROJECT, 2021
** my_putdec.c
** File description:
** fake function
*/

void my_putchar(char c);

unsigned int my_put_dec(unsigned int nb)
{
    if (nb >= 10) {
        my_put_dec(nb / 10);
        my_putchar(nb % 10 + '0');
    }
    if (nb < 10)
        my_put_dec(nb + '0');
    return (0);
}
