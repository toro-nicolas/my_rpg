/*
** EPITECH PROJECT, 2023
** main
** File description:
** main
*/

#include "csfml.h"

entity_t *current_weapon(void)
{
        return get_player()->items[get_player()->cur_item];
}

static void suite_displayweapon(int i, int *angle, int *angle2, int offset)
{
    if (get_player_entity()->rect.left == offset) {
        if (sfSprite_getScale(get_player_entity()->sprite).x < 0)
            sfSprite_setRotation(current_weapon()->sprite, angle2[i]);
        else
            sfSprite_setRotation(current_weapon()->sprite, angle[i]);
    }
}

void display_weapon(void)
{
    int angle[] = {-45, -30, -15, 0, 15, 30, 45, 0, 0};
    int angle2[] = {15, 30, 45, 0, -45, -30, -15, 0, 0};
    int offset = get_player_entity()->offset_rect[2];

    if (current_weapon() == NULL)
        return;
    if (get_player()->orientation != ATK)
        return;
    for (int i = 0; i < 8; i++) {
        offset += 32;
        suite_displayweapon(i, angle, angle2, offset);
    }
    sfRenderWindow_drawSprite(get_window()->window,
    current_weapon()->sprite, NULL);
    sfSprite_setRotation(current_weapon()->sprite, 0);
}

void display_player(void)
{
    static int hit_on = 0;
    player_t *player = get_player();

    if (get_player()->is_hit) {
        sfSprite_setColor(get_player_entity()->sprite, sfRed);
        get_player_entity()->hit_clock += get_window()->delay;
        if (!hit_on)
            get_player_entity()->hit_clock = 0;
        hit_on = 1;
        if (get_player_entity()->hit_clock > 0.25)
            get_player()->is_hit = 0;
    } else {
        sfSprite_setColor(get_player_entity()->sprite, sfWhite);
        hit_on = 0;
    }
    sfRenderWindow_drawSprite(get_window()->window,
    get_player_entity()->sprite, NULL);
    display_weapon();
    stat_up("levelup_sprite", rand() % 3, NOTHING);
    display_stat(get_player_entity());
}
