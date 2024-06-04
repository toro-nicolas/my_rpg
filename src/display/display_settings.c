/*
** EPITECH PROJECT, 2023
** main
** File description:
** main
*/

#include "csfml.h"

static int get_fps(void)
{
    int fps = get_window()->framerate;

    if (fps == 30)
        return 0;
    if (fps == 60)
        return 1;
    if (fps == 120)
        return 2;
    if (fps == 0)
        return 3;
}

static void display_settings_help_help(sfSprite *sprite)
{
    sfSprite_setTextureRect(sprite, (sfIntRect){0, 2070, 98, 38});
    sfSprite_setPosition(sprite,
    (sfVector2f){503 + 138 + 220 * get_window()->size, 148 + 612});
    sfRenderWindow_drawSprite(get_window()->window, sprite, NULL);
    display_button(get_buttons_settings());
    sfSprite_setTextureRect(sprite, (sfIntRect){0, 2120, 3, 23});
    sfSprite_setPosition(sprite, (sfVector2f){843, 282});
    sfSprite_setScale(sprite,
    (sfVector2f){get_window()->vol_music * 1.412, 2});
    sfRenderWindow_drawSprite(get_window()->window, sprite, NULL);
    sfSprite_setPosition(sprite, (sfVector2f){843, 382});
    sfSprite_setScale(sprite,
    (sfVector2f){get_window()->vol_fx * 1.412, 2});
    sfRenderWindow_drawSprite(get_window()->window, sprite, NULL);
}

static void display_settings_help(void)
{
    static sfSprite *sprite = NULL;

    if (sprite == NULL)
        sprite = sfSprite_create();
    sfSprite_setTextureRect(sprite, (sfIntRect){0, 1624, 357, 392});
    sfSprite_setPosition(sprite, (sfVector2f){603, 148});
    sfSprite_setScale(sprite, V2F {2, 2});
    sfSprite_setTexture(sprite, get_game()->main_texture, sfFalse);
    sfRenderWindow_drawSprite(get_window()->window, sprite, NULL);
    sfSprite_setTextureRect(sprite, (sfIntRect){0, 2030, 38, 38});
    sfSprite_setPosition(sprite,
    (sfVector2f){603 + 138 + 120 * get_fps(), 148 + 412});
    sfRenderWindow_drawSprite(get_window()->window, sprite, NULL);
    display_settings_help_help(sprite);
}

void display_settings(void)
{
    button_t *backup = NULL;

    if (get_game()->old_state == MENU) {
        backup = get_buttons_menu()[0];
        get_buttons_menu()[0] = NULL;
        display_menu();
        display_settings_help();
        get_buttons_menu()[0] = backup;
    }
    if (get_game()->old_state == PAUSE) {
        display_main();
        display_settings_help();
    }
}
