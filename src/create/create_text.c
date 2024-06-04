/*
** EPITECH PROJECT, 2023
** main
** File description:
** main
*/

#include "csfml.h"

int do_args(int nb, va_list *liste, sfText *text)
{
    for (int i = 0; i < nb; i++) {
        if (i == 0)
            sfText_setString(text, va_arg(*liste, char *));
        if (i == 1)
            sfText_setFont(text, va_arg(*liste, sfFont *));
        if (i == 2)
            sfText_setCharacterSize(text, va_arg(*liste, int));
        if (i == 3)
            sfText_setColor(text, va_arg(*liste, sfColor));
        if (i == 4)
            sfText_setPosition(text, va_arg(*liste, sfVector2f));
        if (i == 5)
            sfText_setScale(text, va_arg(*liste, sfVector2f));
    }
    return 0;
}

sfText *create_text(int nb, ...)
{
    va_list list;
    sfText *text = sfText_create();

    sfText_setScale(text, (sfVector2f){1, 1});
    sfText_setPosition(text, (sfVector2f){0, 0});
    sfText_setColor(text, sfBlack);
    sfText_setCharacterSize(text, 30);
    va_start(list, nb);
    do_args(nb, &list, text);
    va_end(list);
    return text;
}
