/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** The mimics.c
*/
/**
 * @file mimics.c
 * @brief The mimics.c
 * @author Nicolas TORO
 */

#include "csfml.h"

static void set_stat_m(mob_t *mob_struct)
{
    int floor = get_game()->map_infos->floor;

    mob_struct->hp = 50 * (1 + 0.1 * log(floor + 1)) * pow(1.05, floor);
    mob_struct->attack = 4 * (1 + 0.1 * log(floor + 1)) * pow(1.05, floor);
    mob_struct->speed = 1 * (1 + 0.4 * log(floor + 1)) * pow(1.05, floor);
    mob_struct->range = 250;
    mob_struct->xp_to_drop = RANDINT(30, 40) * (1 + 0.5 * log(floor + 1)) *
    pow(1.05, floor);
    mob_struct->defense = 7 * (1 + 0.1 * log(floor + 1)) * pow(1.05, floor);
    mob_struct->resistance = 25 *
        (1 + 0.1 * log(floor + 1)) * pow(1.05, floor);
}

void init_chest_mimic(sfVector2f pos)
{
    sfSprite *sprite = create_sprite(5, get_game()->main_texture,
        (sfIntRect){0, 666, 32, 32}, pos, V2F {16, 16}, V2F {5, 5});
    entity_t *mob = create_entity(3, MOB, "chest_mimic", sprite);
    mob_t *mob_struct = MALLOC(sizeof(mob_t));

    mob->hitbox = create_rectangle(7, V2F {22, 22}, mob->position,
        V2F {mob->origin.x - 5, mob->origin.y - 10}, mob->scale,
        sfTransparent, sfBlue, 1);
    mob->entity_struct = mob_struct;
    set_stat_m(mob_struct);
    mob_struct->animation =
        (animation_t){0, STAND, sfClock_create(), 6, 6, 6, 0, 5};
    mob->clock = 0;
    mob_struct->hit_sound = SOUND_HIT_MIMIC;
    mob_struct->dead_sound = SOUND_DEAD_MIMIC;
    push_f_doubly(&get_game()->entities_list, mob, UNKNOW);
}

static void set_stat_mm(mob_t *mob_struct)
{
    int floor = get_game()->map_infos->floor;

    mob_struct->hp = 15 * (1 + 0.1 * log(floor + 1)) * pow(1.05, floor);
    mob_struct->attack = 1 * (1 + 0.1 * log(floor + 1)) * pow(1.05, floor);
    mob_struct->speed = 2 * (1 + 0.4 * log(floor + 1)) * pow(1.05, floor);
    mob_struct->range = 700;
    mob_struct->xp_to_drop = RANDINT(1, 7) * (1 + 0.5 * log(floor + 1)) *
    pow(1.05, floor);
    mob_struct->defense = 2 * (1 + 0.1 * log(floor + 1)) * pow(1.05, floor);
    mob_struct->resistance = 5 *
        (1 + 0.1 * log(floor + 1)) * pow(1.05, floor);
}

void init_jar_mimic(sfVector2f pos)
{
    sfSprite *sprite = create_sprite(5, get_game()->main_texture,
        (sfIntRect){0, 794, 32, 32}, pos, V2F {16, 16}, V2F {5, 5});
    entity_t *mob = create_entity(3, MOB, "jar_mimic", sprite);
    mob_t *mob_struct = MALLOC(sizeof(mob_t));

    mob->hitbox = create_rectangle(7, V2F {22, 22}, mob->position,
        V2F {mob->origin.x - 5, mob->origin.y - 10}, mob->scale,
        sfTransparent, sfBlue, 1);
    mob->entity_struct = mob_struct;
    set_stat_mm(mob_struct);
    mob_struct->animation =
        (animation_t){0, STAND, sfClock_create(), 10, 4, 6, 0, 4};
    mob->clock = 0;
    mob_struct->hit_sound = SOUND_HIT_MIMIC;
    mob_struct->dead_sound = SOUND_DEAD_MIMIC;
    push_f_doubly(&get_game()->entities_list, mob, UNKNOW);
}

static void set_stat_mmm(mob_t *mob_struct)
{
    int floor = get_game()->map_infos->floor;

    mob_struct->hp = 30 * (1 + 0.1 * log(floor + 1)) * pow(1.05, floor);
    mob_struct->attack = 8 * (1 + 0.1 * log(floor + 1)) * pow(1.05, floor);
    mob_struct->speed = 3 * (1 + 0.4 * log(floor + 1)) * pow(1.05, floor);
    mob_struct->range = 700;
    mob_struct->xp_to_drop = RANDINT(15, 20) * (1 + 0.5 * log(floor + 1)) *
    pow(1.05, floor);
    mob_struct->defense = 1 * (1 + 0.1 * log(floor + 1)) * pow(1.05, floor);
    mob_struct->resistance = 10 *
        (1 + 0.1 * log(floor + 1)) * pow(1.05, floor);
}

void init_barrel_mimic(sfVector2f pos)
{
    sfSprite *sprite = create_sprite(5, get_game()->main_texture,
        (sfIntRect){0, 922, 32, 32}, pos, V2F {16, 16}, V2F {5, 5});
    entity_t *mob = create_entity(3, MOB, "barrel_mimic", sprite);
    mob_t *mob_struct = MALLOC(sizeof(mob_t));

    mob->hitbox = create_rectangle(7, V2F {22, 22}, mob->position,
        V2F {mob->origin.x - 5, mob->origin.y - 10}, mob->scale,
        sfTransparent, sfBlue, 1);
    mob->entity_struct = mob_struct;
    set_stat_mmm(mob_struct);
    mob_struct->animation =
        (animation_t){0, STAND, sfClock_create(), 8, 6, 8, 5, 5};
    mob->clock = 0;
    mob_struct->hit_sound = SOUND_HIT_MIMIC;
    mob_struct->dead_sound = SOUND_DEAD_MIMIC;
    push_f_doubly(&get_game()->entities_list, mob, UNKNOW);
}
