/*
** EPITECH PROJECT, 2023
** main
** File description:
** main
*/

#include <string.h>
#include "csfml.h"

int normalize_vector(sfVector2f *vector)
{
    float length = sqrt(pow(vector->x, 2) + pow(vector->y, 2));

    if (length == 0)
        return 1;
    vector->x /= length;
    vector->y /= length;
    return 0;
}

static void update_stat(void)
{
    entity_t *weapon = current_weapon();
    item_t *item = weapon ? weapon->entity_struct : NULL;

    get_player()->max_attackw = get_player()->attack;
    get_player()->max_defensew = get_player()->defense;
    get_player()->max_speedw = get_player()->speed;
    get_player()->max_hpw = get_player()->max_hp;
    if (!weapon)
        return;
    get_player()->max_attackw += item->attack;
    get_player()->max_defensew += item->defense;
    get_player()->max_speedw += item->speed;
    get_player()->max_hpw += item->hp;
}

void healing(void)
{
    if (get_player()->hp >= get_player()->max_hpw
        || get_player()->hp <= 0)
        return;
    if (get_player()->is_hit) {
        get_player()->heal_clock = 0;
        return;
    }
    for (; get_player()->heal_clock > 3.01f; get_player()->heal_clock -= 0.01)
        get_player()->hp += 0.001 * get_player()->max_hpw;
}

static void dying(void)
{
    if (get_player()->hp > 0)
        return;
    if (get_player()->hp <= 0) {
        get_player_entity()->rect.top =
        get_player_entity()->initial_rect.top + (32 * 7);
        choose_offset("die", get_player_entity()->offset_rect,
        get_player_entity()->initial_rect);
    }
    if (get_player_entity()->rect.left
    == get_player_entity()->offset_rect[1]) {
        get_player()->hp = get_player()->max_hpw;
        sfSprite_setPosition(get_player_entity()->sprite, V2F {100, 100});
        sfRectangleShape_setPosition(get_player_entity()->hitbox,
        V2F {100, 100});
        get_player_entity()->position = V2F {100, 100};
        get_player_entity()->rect.top = get_player_entity()->initial_rect.top;
        choose_offset("idle", get_player_entity()->offset_rect,
        get_player_entity()->initial_rect);
    }
}

void update_player2(void)
{
    update_stat();
    healing();
    dying();
    if (get_player()->hp >= get_player()->max_hpw)
        get_player()->hp = get_player()->max_hpw;
}
