/*
** EPITECH PROJECT, 2023
** main
** File description:
** main
*/

#include "csfml.h"

int suite(int i, va_list *liste, sfRectangleShape *rectangle)
{
    if (i == 4)
        sfRectangleShape_setFillColor(rectangle, va_arg(*liste, sfColor));
    if (i == 5)
        sfRectangleShape_setOutlineColor(rectangle, va_arg(*liste, sfColor));
    if (i == 6)
        sfRectangleShape_setOutlineThickness(rectangle, va_arg(*liste, int));
}

int do_args_rectangle(int nb, va_list *liste, sfRectangleShape *rectangle)
{
    for (int i = 0; i < nb; i++) {
        if (i == 0)
            sfRectangleShape_setSize(rectangle, va_arg(*liste, sfVector2f));
        if (i == 1)
            sfRectangleShape_setPosition(rectangle,
            va_arg(*liste, sfVector2f));
        if (i == 2)
            sfRectangleShape_setOrigin(rectangle,
            va_arg(*liste, sfVector2f));
        if (i == 3)
            sfRectangleShape_setScale(rectangle,
            va_arg(*liste, sfVector2f));
        suite(i, liste, rectangle);
    }
    return 0;
}

sfRectangleShape *create_rectangle(int nb, ...)
{
    va_list list;
    sfRectangleShape *rectangle = sfRectangleShape_create();

    sfRectangleShape_setSize(rectangle, (sfVector2f) {100, 100});
    sfRectangleShape_setScale(rectangle, (sfVector2f) {1, 1});
    sfRectangleShape_setPosition(rectangle, (sfVector2f) {0, 0});
    sfRectangleShape_setOrigin(rectangle, (sfVector2f) {0, 0});
    sfRectangleShape_setOutlineColor(rectangle, sfRed);
    sfRectangleShape_setOutlineThickness(rectangle, 2);
    va_start(list, nb);
    do_args_rectangle(nb, &list, rectangle);
    va_end(list);
    return rectangle;
}
