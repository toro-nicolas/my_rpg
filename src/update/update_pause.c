/*
** EPITECH PROJECT, 2023
** main
** File description:
** main
*/

#include "csfml.h"

void update_pause(void)
{
    for (nodes_t *entity = get_game()->entities_list; entity != NULL;
    entity = entity->next) {
        if (((entity_t *)(entity->data))->type == MOB) {
            ((mob_t *)((entity_t *)(entity->data))->entity_struct)->sound_clock
            = 0;
            (((entity_t *)entity->data)->clock) = 0;
            (((entity_t *)entity->data)->hit_clock) = 0;
        }
    }
}
