/*
** EPITECH PROJECT, 2023
** main
** File description:
** main
*/

#include "csfml.h"

static void scepter_stat(item_t *item, int floor)
{
    item->defense = RANDINT(1, 5) *
    (1 + 0.5 * log(floor + 1)) * pow(1.05, floor);
    item->attack = RANDINT(2, 10) *
    (1 + 0.5 * log(floor + 1)) * pow(1.05, floor);
    item->speed = 0;
    item->hp = RANDINT(10, 40) *
    (1 * log(floor + 1)) * pow(1.05, floor);
}

static void dagger_stat(item_t *item, int floor)
{
    item->defense = RANDINT(1, 5) *
    (1 + 0.5 * log(floor + 1)) * pow(1.05, floor);
    item->attack = RANDINT(20, 50) *
    (1 + 0.3 * log(floor + 1)) * pow(1.05, floor);
    item->speed = 0;
    item->hp = RANDINT(10, 20) *
    (1 * 0.5 * log(floor + 1)) * pow(1.05, floor);
}

static void lance_stat(item_t *item, int floor)
{
    item->defense = RANDINT(1, 5) *
    (1 + 0.5 * log(floor + 1)) * pow(1.05, floor);
    item->attack = RANDINT(10, 30) *
    (1 + 0.5 * log(floor + 1)) * pow(1.05, floor);
    item->speed = 0;
    item->hp = RANDINT(10, 20) *
    (1 * 0.5 * log(floor + 1)) * pow(1.05, floor);
}

static void drop_item(entity_t *mob)
{
    int drop = rand() % 100;
    int floor = get_game()->map_infos->floor;
    entity_t *item = NULL;
    sfVector2f pos = {mob->position.x, mob->position.y +
    (mob->rect.height / 2)};

    if (drop > 30 * log(get_game()->map_infos->floor + 1))
        return;
    item = RANDOM_ITEM(pos);
    item->position = V2F {pos.x - (item->rect.width / 2), pos.y -
    (item->rect.height / 2)};
    ((item_t *) item->entity_struct)->on_ground = 1;
    ((item_t *) item->entity_struct)->speed = 0;
    if (strncmp(item->id, "s", 1) == 0)
        scepter_stat(item->entity_struct, floor);
    if (strncmp(item->id, "d", 1) == 0)
        dagger_stat(item->entity_struct, floor);
    if (strncmp(item->id, "l", 1) == 0)
        lance_stat(item->entity_struct, floor);
}

float calculate_damage(float attack, float defense)
{
    if (current_weapon())
        attack += ((item_t *)current_weapon()->entity_struct)->attack;
    if (defense == 0)
        return attack;
    return attack / defense;
}

void check_hitbox(nodes_t **tmp, sfFloatRect player_rect)
{
    entity_t *mob_e = (*tmp)->data;
    sfFloatRect mob_rect;
    mob_t *mob_t = NULL;

    if (mob_e->type != MOB)
        return;
    mob_rect = sfRectangleShape_getGlobalBounds(mob_e->hitbox);
    if (!sfFloatRect_intersects(&player_rect, &mob_rect, NULL))
        return;
    mob_t = mob_e->entity_struct;
    knockback(get_player_entity(), mob_e, mob_t->resistance);
    if (mob_t->hp <= 0)
        return;
    mob_t->is_hit = 1;
    if (mob_t->hp -
        calculate_damage(get_player()->max_attackw, mob_t->defense) <= 0) {
        get_player()->xp += mob_t->xp_to_drop;
        mob_t->hp = 0;
        drop_item(mob_e);
    }
}

static void suiteangle(int *angle, int *angle2,
    sfFloatRect player_rect, int i)
{
    if (sfSprite_getScale(get_player_entity()->sprite).x < 0)
        sfRectangleShape_setRotation(current_weapon()->hitbox, angle2[i]);
    else
        sfRectangleShape_setRotation(current_weapon()->hitbox, angle[i]);
    player_rect = sfRectangleShape_getGlobalBounds(current_weapon()->hitbox);
    for (nodes_t *tmp = get_game()->entities_list; tmp; tmp = tmp->next)
        check_hitbox(&tmp, player_rect);
}

static int check_angle(int *angle, int *angle2,
    int offset, sfFloatRect player_rect)
{
    if (!current_weapon())
        return 0;
    for (int i = 0; i < 8; i++) {
        offset += 32;
        if (get_player_entity()->rect.left == offset)
            suiteangle(angle, angle2, player_rect, i);
        sfRectangleShape_setRotation(current_weapon()->hitbox, 0);
    }
    return 1;
}

void attack_mob(void)
{
    sfFloatRect player_rect =
    sfRectangleShape_getGlobalBounds(get_player_entity()->hitbox);
    int angle[] = {-45, -30, -15, 0, 15, 30, 45, 0, 0};
    int angle2[] = {15, 30, 45, 0, -45, -30, -15, 0, 0};
    int offset = get_player_entity()->offset_rect[2];

    if (check_angle(angle, angle2, offset, player_rect)) {
        get_player()->is_attacking = 0;
        return;
    }
    for (nodes_t *tmp = get_game()->entities_list; tmp; tmp = tmp->next) {
        check_hitbox(&tmp, player_rect);
        ((entity_t *)tmp->data)->hit_clock = 0;
    }
    get_player()->is_attacking = 0;
}
