/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** The gladiator.c
*/
/**
 * @file gladiator.c
 * @brief The gladiator.c
 * @author Nicolas TORO
 */

#include "../../include/csfml.h"

static void set_stat_g(mob_t *mob_struct)
{
    int floor = get_game()->map_infos->floor;

    mob_struct->hp = 20 * (1 + 0.1 * log(floor + 1)) * pow(1.05, floor);
    mob_struct->attack = 3 * (1 + 0.1 * log(floor + 1)) * pow(1.05, floor);
    mob_struct->speed = 1 * (1 + 0.1 * log(floor + 1)) * pow(1.05, floor);
    mob_struct->range = 500;
    mob_struct->xp_to_drop = RANDINT(5, 10) * (1 + 0.5 * log(floor + 1)) *
    pow(1.05, floor);
    mob_struct->defense = 4 * (1 + 0.1 * log(floor + 1)) * pow(1.05, floor);
    mob_struct->resistance = 10 *
        (1 + 0.1 * log(floor + 1)) * pow(1.05, floor);
}

void init_gladiator(sfVector2f pos)
{
    sfSprite *sprite = create_sprite(5, get_game()->main_texture,
    (sfIntRect){0, 1050, 32, 32}, pos, V2F {16, 16}, V2F {5, 5});
    entity_t *mob = create_entity(3, MOB, "gladiator", sprite);
    mob_t *mob_struct = MALLOC(sizeof(mob_t));

    mob->hitbox = create_rectangle(7, V2F {22, 22}, mob->position,
    V2F {mob->origin.x - 5, mob->origin.y - 10}, mob->scale,
    sfTransparent, sfBlue, 1);
    mob->entity_struct = mob_struct;
    set_stat_g(mob_struct);
    mob_struct->animation =
        (animation_t){0, STAND, sfClock_create(), 5, 8, 7, 7, 3};
    mob->clock = 0;
    mob_struct->hit_sound = SOUND_HIT_GLADIATOR;
    mob_struct->dead_sound = SOUND_DEAD_GLADIATOR;
    push_f_doubly(&get_game()->entities_list, mob, UNKNOW);
}
