/*
** EPITECH PROJECT, 2023
** main
** File description:
** main
*/

#include "csfml.h"

static void display_button_help(button_t **buttons, int i, sfSprite *sprite,
    sfText *text)
{
    sfSprite_setTextureRect(sprite,
    (sfIntRect){(buttons[i]->state % 2) * 222, 1302, 222, 108});
    sfSprite_setScale(sprite, buttons[i]->scale);
    sfSprite_setPosition(sprite, (sfVector2f){buttons[i]->pos.x
    - (222 * buttons[i]->scale.x) / 2,
    buttons[i]->pos.y - (108 * buttons[i]->scale.y) / 2});
    if (buttons[i]->state == DISABLED)
        sfSprite_setColor(sprite, (sfColor){100, 100, 100, 255});
    sfRenderWindow_drawSprite(get_window()->window, sprite, NULL);
    sfSprite_setColor(sprite, sfWhite);
    sfText_setString(text, buttons[i]->text);
    sfText_setPosition(text, (sfVector2f){buttons[i]->pos.x
    - sfText_getGlobalBounds(text).width / 2, buttons[i]->pos.y
    - sfText_getGlobalBounds(text).height / 2
    - 4 - 12 * ((buttons[i]->state + 1) % 2)});
    if (buttons[i]->state == DISABLED)
        sfText_setColor(text, (sfColor){100, 100, 100, 255});
    sfRenderWindow_drawText(get_window()->window, text, NULL);
    sfText_setColor(text, sfWhite);
}

void display_button(button_t **buttons)
{
    static sfSprite *sprite = NULL;
    static sfText *text = NULL;

    if (text == NULL) {
        text = sfText_create();
        sfText_setFont(text, get_font());
    }
    if (sprite == NULL) {
        sprite = sfSprite_create();
        sfSprite_setTexture(sprite, get_game()->main_texture, sfFalse);
    }
    for (int i = 0; buttons[i] != NULL; i++)
        display_button_help(buttons, i, sprite, text);
}
