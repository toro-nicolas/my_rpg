/*
** EPITECH PROJECT, 2023
** main
** File description:
** main
*/

#include "csfml.h"

int do_args_sprite(int nb, va_list *liste, sfSprite *sprite)
{
    for (int i = 0; i < nb; i++) {
        if (i == 0)
            sfSprite_setTexture(sprite, va_arg(*liste, sfTexture *), sfTrue);
        if (i == 1)
            sfSprite_setTextureRect(sprite, va_arg(*liste, sfIntRect));
        if (i == 2)
            sfSprite_setPosition(sprite, va_arg(*liste, sfVector2f));
        if (i == 3)
            sfSprite_setOrigin(sprite, va_arg(*liste, sfVector2f));
        if (i == 4)
            sfSprite_setScale(sprite, va_arg(*liste, sfVector2f));
    }
    return 0;
}

sfSprite *create_sprite(int nb, ...)
{
    va_list list;
    sfSprite *sprite = sfSprite_create();

    sfSprite_setScale(sprite, (sfVector2f) {1, 1});
    sfSprite_setPosition(sprite, (sfVector2f) {0, 0});
    sfSprite_setOrigin(sprite, (sfVector2f) {0, 0});
    va_start(list, nb);
    do_args_sprite(nb, &list, sprite);
    va_end(list);
    return sprite;
}
