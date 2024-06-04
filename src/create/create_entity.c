/*
** EPITECH PROJECT, 2023
** main
** File description:
** main
*/

#include "csfml.h"

int do_args_entity(int nb, va_list *liste, entity_t *entity)
{
    for (int i = 0; i < nb; i++) {
        if (i == 0)
            entity->type = va_arg(*liste, entity_type_e_t);
        if (i == 1)
            entity->id = va_arg(*liste, char *);
        if (i == 2)
            entity->sprite = va_arg(*liste, sfSprite *);
        if (i == 3)
            entity->entity_struct = va_arg(*liste, void *);
        if (i == 4)
            entity->hitbox = va_arg(*liste, void *);
    }
    return 0;
}

entity_t *create_entity(int nb, ...)
{
    va_list list;
    entity_t *entity = MALLOC(sizeof(entity_t));

    entity->clock = 0;
    entity->hit_clock = 0;
    entity->hitbox = NULL;
    va_start(list, nb);
    do_args_entity(nb, &list, entity);
    va_end(list);
    if (entity->sprite != NULL) {
        entity->position = sfSprite_getPosition(entity->sprite);
        entity->origin = sfSprite_getOrigin(entity->sprite);
        entity->scale = sfSprite_getScale(entity->sprite);
        entity->initial_rect = sfSprite_getTextureRect(entity->sprite);
        entity->rect = entity->initial_rect;
    }
    return entity;
}
