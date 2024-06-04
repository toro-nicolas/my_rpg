/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** The mob.c
*/
/**
 * @file mob.c
 * @brief The mob.c
 * @author Nicolas TORO
 */

#include "csfml.h"

static void update_animation_information_next(entity_t *entity, mob_t *mob)
{
    if (is_hitbox_intersecting(get_player_entity()->hitbox, entity->hitbox)) {
        if (mob->animation.orientation != ATTACK) {
            mob->animation.orientation = ATTACK;
            mob->animation.current = 0;
        }
        return;
    }
    if ((get_player_entity()->position.x - entity->position.x < mob->range &&
    get_player_entity()->position.x - entity->position.x > -mob->range) &&
    (get_player_entity()->position.y - entity->position.y < mob->range &&
    get_player_entity()->position.y - entity->position.y > -mob->range)) {
        if (mob->animation.orientation != MOVE) {
            mob->animation.orientation = MOVE;
            mob->animation.current = 0;
        }
    } else if (mob->animation.orientation != STAND) {
        mob->animation.orientation = STAND;
        mob->animation.current = 0;
    }
}

static void update_animation_information(entity_t *entity)
{
    mob_t *mob = (mob_t *)entity->entity_struct;

    if (mob->animation.orientation == DEAD &&
    mob->animation.current >= mob->animation.max_dead) {
        entity->initial_rect = (sfIntRect){0, 506, 32, 32};
        mob->animation.orientation = DISAPPEAR;
        mob->animation.current = 0;
        return;
    }
    if (mob->hp <= 0) {
        if (mob->animation.orientation != DEAD &&
        mob->animation.orientation != DISAPPEAR) {
            mob->animation.orientation = DEAD;
            mob->animation.current = 0;
            play_sound(entity, mob->dead_sound);
        }
        return;
    }
    update_animation_information_next(entity, mob);
}

static void update_current_animation(entity_t *entity)
{
    mob_t *mob = (mob_t *)entity->entity_struct;

    if (TIME(mob->animation.animation_clock) > 0.15) {
        ((mob_t *)entity->entity_struct)->animation.current++;
        sfClock_restart(((mob_t *)entity->entity_struct)->
        animation.animation_clock);
    }
    if ((mob->animation.orientation == STAND &&
    mob->animation.current >= mob->animation.max_stand) ||
    (mob->animation.orientation == MOVE &&
    mob->animation.current >= mob->animation.max_move) ||
    (mob->animation.orientation == ATTACK &&
    mob->animation.current >= mob->animation.max_attack))
        ((mob_t *)entity->entity_struct)->animation.current = 0;
    entity->clock = (mob->animation.orientation != MOVE) ? 0 : entity->clock;
}

void update_mob_animation(entity_t *entity)
{
    update_animation_information(entity);
    update_current_animation(entity);
    if (get_player_entity()->position.x - entity->position.x > 0)
        entity->scale.x = ABS(entity->scale.x);
    else
        entity->scale.x = -ABS(entity->scale.x);
    entity->rect = entity->initial_rect;
    entity->rect.left += entity->rect.width *
        ((mob_t *)entity->entity_struct)->animation.current;
    entity->rect.top += entity->rect.height *
        ((mob_t *)entity->entity_struct)->animation.orientation;
}
