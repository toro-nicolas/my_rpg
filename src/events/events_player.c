/*
** EPITECH PROJECT, 2023
** main
** File description:
** main
*/

#include "csfml.h"
#include "math.h"

void suite_keys2(sfEvent event)
{
    item_t *item = NULL;

    if (SLOT1K)
        get_player()->cur_item = 0;
    if (SLOT2K)
        get_player()->cur_item = 1;
    if (SLOT3K)
        get_player()->cur_item = 2;
    if (INVENTORYK) {
        get_user()->show_equipments = !get_user()->show_equipments;
        INVENTORYK = 0;
    }
}

void suite_keys(sfEvent event)
{
    if (XPK)
        get_player()->xp += XP_GIVEN;
    if (ATTACKK) {
        get_player()->orientation = ATK;
        get_player_entity()->rect.top =
        get_player_entity()->initial_rect.top + (32 * 8);
        choose_offset("attack", get_player_entity()->offset_rect,
        get_player_entity()->initial_rect);
    }
    if (HITK && get_player()->hp > 0)
        get_player()->hp -= 1;
    if (HEALK && get_player()->hp < get_player()->max_hpw) {
        get_player()->hp += 1;
        if (get_player()->hp > get_player()->max_hpw)
            get_player()->hp = get_player()->max_hpw;
    }
    suite_keys2(event);
}

void analyse_key_pressed_player(sfEvent event)
{
    sfVector2f scale = sfSprite_getScale(get_player_entity()->sprite);

    if (LEFTK || RIGHTK || DOWNK || UPK) {
        if (LEFTK)
            scale.x = -ABS(scale.x);
        if (RIGHTK)
            scale.x = ABS(scale.x);
        get_player_entity()->rect.top =
        get_player_entity()->initial_rect.top + (32 * 3);
        choose_offset("walk", get_player_entity()->offset_rect,
        get_player_entity()->initial_rect);
        sfSprite_setScale(get_player_entity()->sprite,
        scale);
    }
    suite_keys(event);
}

void analyse_key_released_player(sfEvent event)
{
    if (!LEFTK && !RIGHTK && !DOWNK && !ATTACKK && !UPK) {
        get_player()->orientation = NONE;
        get_player_entity()->rect.top = get_player_entity()->initial_rect.top;
        choose_offset("idle", get_player_entity()->offset_rect,
        get_player_entity()->initial_rect);
    }
}

void events_player(sfEvent event)
{
    if (get_player()->hp > 0) {
        analyse_key_pressed_player(event);
        analyse_key_released_player(event);
    }
}
