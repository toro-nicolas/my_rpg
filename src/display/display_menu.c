/*
** EPITECH PROJECT, 2023
** main
** File description:
** main
*/

#include "csfml.h"

void display_menu(void)
{
    static sfSprite *sprite = NULL;

    if (sprite == NULL) {
        sprite = sfSprite_create();
        sfSprite_setPosition(sprite, (sfVector2f){0, 0});
        sfSprite_setTexture(sprite, get_game()->main_texture, sfFalse);
        sfSprite_setTextureRect(sprite, (sfIntRect){0, 2559, 1920, 1080});
    }
    sfRenderWindow_drawSprite(get_window()->window, sprite, NULL);
    display_button(get_buttons_menu());
}
