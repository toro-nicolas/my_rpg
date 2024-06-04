/*
** EPITECH PROJECT, 2024
** B-MUL-200-NCE-2-1-myrpg-gianni.tuero
** File description:
** The update_entities.c
*/
/**
 * @file update_entities.c
 * @brief The update_entities.c
 * @author Nicolas TORO
 */

#include "csfml.h"

void check_idle_sound(entity_t *entity)
{
    int random = RANDINT(5, 50000);

    if (entity->type == MOB
    && ((mob_t *)entity->entity_struct)->hp > 0 &&
    ((mob_t *)entity->entity_struct)->animation.orientation == STAND
    && ((mob_t *)entity->entity_struct)->sound_clock > random) {
        play_sound(entity, ((mob_t *)entity->entity_struct)->idle_sound);
        ((mob_t *)entity->entity_struct)->sound_clock = 0;
    }
}

void check_all_collisions(entity_t *entity)
{
    if (entity->type == MOB && (((mob_t *)entity->entity_struct)->hp <= 0 ||
    ((mob_t *)entity->entity_struct)->animation.orientation == DISAPPEAR))
        return;
    check_collision(entity, get_player_entity());
    for (nodes_t *tmp = get_game()->entities_list;
    tmp != NULL; tmp = tmp->next) {
        if (((entity_t *)tmp->data)->type == MOB && tmp->data != entity &&
        ((mob_t *)((entity_t *)tmp->data)->entity_struct)->hp > 0) {
            check_collision(entity, (entity_t *)tmp->data);
        }
    }
}

void update_entity(entity_t *entity)
{
    if (entity->sprite != NULL) {
        if (entity->type == MOB) {
            check_all_collisions(entity);
            check_idle_sound(entity);
            update_mob_animation(entity);
            sfSprite_setTextureRect(entity->sprite, entity->rect);
            sfSprite_setScale(entity->sprite, entity->scale);
            entity->scale = sfSprite_getScale(entity->sprite);
            entity->origin = sfSprite_getOrigin(entity->sprite);
        }
        sfSprite_setPosition(entity->sprite, entity->position);
        sfSprite_move(entity->sprite, entity->move);
        entity->position = sfSprite_getPosition(entity->sprite);
        entity->move = V2F {0, 0};
    }
    if (entity->hitbox != NULL) {
        entity->origin = sfRectangleShape_getOrigin(entity->hitbox);
        entity->scale = sfRectangleShape_getScale(entity->hitbox);
        sfRectangleShape_setPosition(entity->hitbox, entity->position);
    }
}
