/*
** EPITECH PROJECT, 2023
** my_put_nbr
** File description:
** Prints a number (nb) in stdout
*/

#include "my.h"

static void put_str_nb(int nb, int len_nb, int fd)
{
    char nb_str[len_nb];
    int figure_temp = nb;

    for (int i = 0; i < len_nb; i++) {
        nb_str[len_nb - i - 1] = 48 + (figure_temp % 10);
        figure_temp = (figure_temp - (figure_temp % 10)) / 10;
    }
    nb_str[len_nb] = '\0';
    my_putstrf(fd, nb_str);
}

int my_put_nbrf(int fd, int nb)
{
    int len_nb = 1;
    int temp_nb = nb;

    if (nb == -2147483648) {
        my_putstr("-2147483648");
        return 0;
    }
    if (nb < 0) {
        my_putchar('-');
        nb = -nb;
    }
    while ((temp_nb / 10) != 0) {
        len_nb = len_nb + 1;
        temp_nb = temp_nb / 10;
    }
    put_str_nb(nb, len_nb, fd);
    return 0;
}
