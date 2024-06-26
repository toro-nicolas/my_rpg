/*
** EPITECH PROJECT, 2023
** my_printf
** File description:
** Prints a string (format) with possible flags and format
** in stdout and returns the lenght the printed string
*/

#include <stdarg.h>
#include "my.h"
#include "./flags/myflags.h"
#include "./flags/myformats.h"

static void find_format(user_t *user,
    flags_t *flgs, formating_t *formating)
{
    int copy = user->i + 1;

    formating->nb_format = 0;
    format_first(user, flgs, formating, &copy);
    copy = user->i + 1 + formating->nb_format;
    format_width(user, flgs, formating, &copy);
    copy = user->i + 1 + formating->nb_format;
    format_precision(user, flgs, formating, &copy);
    copy = user->i + 1 + formating->nb_format;
    format_numbers(user, flgs, formating, &copy);
    copy = user->i + 1 + formating->nb_format;
    format_specifier(user, flgs, formating, &copy);
    copy = user->i + 1 + formating->nb_format;
    formating->flag = user->str[copy];
}

static void not_a_flag(formating_t *formating, user_t *user)
{
    my_putcharf(formating->fd, '%');
    (user->total_len) += 1;
    if (my_strcmp(formating->final_format, "\0") != 0) {
        my_putstrf(formating->fd, formating->final_format);
        (user->total_len) += my_strlen(formating->final_format);
    }
    if (formating->flag != '\0') {
        my_putcharf(formating->fd, formating->flag);
        (user->total_len) += 1;
    }
}

static void find_flags(user_t *user, va_list list,
    formating_t *formating, int *index)
{
    flags_t flgs = {.str = "dicspouxXeEfFgGaAmbSD%",
    .index_flag = 0};
    int copi;

    find_format(user, &flgs, formating);
    copi = user->i + my_strlen(formating->final_format) + 1;
    user->i = user->i + (my_strlen(formating->final_format)) + 1;
    for (; flgs.index_flag < my_strlen(flgs.str); flgs.index_flag++) {
        if (user->str[copi] == 'n') {
            flag_n(list, formating, user->total_len);
            return;
        }
        if (user->str[copi] == flgs.str[flgs.index_flag]) {
            *index = flgs.index_flag;
            return;
        }
    }
    not_a_flag(formating, user);
    *index = -1;
}

static void select_display(user_t *user, va_list *liste, int fd)
{
    int index_flag = -1;
    formating_t formating = {.liste = liste, .fd = fd};

    if (user->str[user->i] == '%')
        find_flags(user, *liste, &formating, &index_flag);
    if (index_flag != -1)
        user->total_len += FLAGS[index_flag](*liste, &formating);
    if (user->str[user->i] != '%' && user->str[user->i] != '\0'
        && (user->str[user->i] != formating.flag)) {
        my_putcharf(formating.fd, user->str[user->i]);
        (user->total_len)++;
    }
}

int my_printf(int fd, char const *format, ...)
{
    va_list liste;
    user_t user = {.str = format, .total_len = 0};

    va_start(liste, format);
    for (user.i = 0; user.i < my_strlen(user.str); (user.i)++) {
        select_display(&user, &liste, fd);
    }
    va_end(liste);
    return user.total_len;
}
