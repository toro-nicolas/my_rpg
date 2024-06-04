/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** The monsters.c
*/
/**
 * @file monsters.c
 * @brief The monsters.c
 * @author Nicolas TORO
 */

#include "csfml.h"

static void set_stat_d(mob_t *mob_struct)
{
    int floor = get_game()->map_infos->floor;

    mob_struct->hp = 10 * (1 + 0.1 * log(floor + 1)) * pow(1.05, floor);
    mob_struct->attack = 2 * (1 + 0.1 * log(floor + 1)) * pow(1.05, floor);
    mob_struct->speed = 6 * (1 + 0.4 * log(floor + 1)) * pow(1.05, floor);
    mob_struct->range = 1500;
    mob_struct->xp_to_drop = RANDINT(3, 7) * (1 + 0.5 * log(floor + 1)) *
    pow(1.05, floor);
    mob_struct->defense = 0 * (1 + 0.1 * log(floor + 1)) * pow(1.05, floor);
    mob_struct->resistance = 0 *
        (1 + 0.1 * log(floor + 1)) * pow(1.05, floor);
}

void init_demon(sfVector2f pos)
{
    sfSprite *sprite = create_sprite(5, get_game()->main_texture,
        (sfIntRect){320, 666, 32, 32}, pos, V2F {16, 16}, V2F {5, 5});
    entity_t *mob = create_entity(3, MOB, "demon", sprite);
    mob_t *mob_struct = MALLOC(sizeof(mob_t));

    mob->hitbox = create_rectangle(7, V2F {22, 22}, mob->position,
        V2F {mob->origin.x - 5, mob->origin.y - 10}, mob->scale,
        sfTransparent, sfBlue, 1);
    mob->entity_struct = mob_struct;
    set_stat_d(mob_struct);
    mob_struct->animation =
        (animation_t){0, STAND, sfClock_create(), 5, 8, 8, 6, 6};
    mob->clock = 0;
    mob_struct->idle_sound = SOUND_IDLE_MONSTER;
    mob_struct->hit_sound = SOUND_HIT_MONSTER;
    mob_struct->dead_sound = SOUND_DEAD_MONSTER;
    push_f_doubly(&get_game()->entities_list, mob, UNKNOW);
}

static void set_stat_g(mob_t *mob_struct)
{
    int floor = get_game()->map_infos->floor;

    mob_struct->hp = 40 * (1 + 0.1 * log(floor + 1)) * pow(1.05, floor);
    mob_struct->attack = 9 * (1 + 0.1 * log(floor + 1)) * pow(1.05, floor);
    mob_struct->speed = 1 * (1 + 0.4 * log(floor + 1)) * pow(1.05, floor);
    mob_struct->range = 600;
    mob_struct->xp_to_drop = RANDINT(20, 30) * (1 + 0.5 * log(floor + 1)) *
    pow(1.05, floor);
    mob_struct->defense = 7 * (1 + 0.1 * log(floor + 1)) * pow(1.05, floor);
    mob_struct->resistance = 20 *
        (1 + 0.1 * log(floor + 1)) * pow(1.05, floor);
}

void init_ghoul(sfVector2f pos)
{
    sfSprite *sprite = create_sprite(5, get_game()->main_texture,
        (sfIntRect){320, 794, 32, 32}, pos, V2F {16, 16}, V2F {5, 5});
    entity_t *mob = create_entity(3, MOB, "ghoul", sprite);
    mob_t *mob_struct = MALLOC(sizeof(mob_t));

    mob->hitbox = create_rectangle(7, V2F {22, 22}, mob->position,
        V2F {mob->origin.x - 5, mob->origin.y - 10}, mob->scale,
        sfTransparent, sfBlue, 1);
    mob->entity_struct = mob_struct;
    set_stat_g(mob_struct);
    mob_struct->animation =
        (animation_t){0, STAND, sfClock_create(), 4, 8, 6, 6, 5};
    mob->clock = 0;
    mob_struct->idle_sound = SOUND_IDLE_MONSTER;
    mob_struct->hit_sound = SOUND_HIT_MONSTER;
    mob_struct->dead_sound = SOUND_DEAD_MONSTER;
    push_f_doubly(&get_game()->entities_list, mob, UNKNOW);
}
