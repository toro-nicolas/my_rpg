/*
** EPITECH PROJECT, 2023
** main
** File description:
** main
*/

#include "csfml.h"
#include <stdio.h>

void place_and_display(sfText *text, float clock, int result, char *id)
{
    sfVector2f pos_sprite = {0, 0};

    pos_sprite.x = sfText_getGlobalBounds(text).width
    + sfText_getPosition(text).x + 30;
    pos_sprite.y = sfText_getPosition(text).y + 30;
    sfSprite_setPosition(get_entity(id)->sprite, pos_sprite);
    if (clock < 0.45 && result) {
        sfRenderWindow_drawSprite(get_window()->window,
        get_entity(id)->sprite, NULL);
        sfRenderWindow_drawText(get_window()->window, text, NULL);
    }
}

void display_level_up(char *id, action_player_e_t action, float value,
    int other)
{
    static int result = 0;
    static float clock = 0;
    static sfText *text = NULL;
    static void (*increase_stats[])(sfText *, float) =
    {&atk_up, &def_up, &hp_up};

    if (text == NULL) {
        text = create_text(5, "",
        get_font(), 50, sfWhite);
    }
    sfText_setPosition(text, V2F {PLAYER_POS.x + 50, PLAYER_POS.y});
    if (get_player()->old_level != get_player()->level || other != NOTHING) {
        increase_stats[action](text, value);
        get_player()->old_level = get_player()->level;
        result = 1;
        clock = 0;
    }
    clock += get_window()->delay;
    place_and_display(text, clock, result, id);
}

void stat_up(char *id, action_player_e_t stat, int other)
{
    float value = (rand() % 3 + 1) * 0.6 * (get_player()->level + 1);

    if (get_player()->loot) {
        other = SOMETHING;
        get_player()->loot = 0;
    }
    display_level_up(id, stat, value, other);
}
