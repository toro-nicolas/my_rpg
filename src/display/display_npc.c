/*
** EPITECH PROJECT, 2023
** main
** File description:
** main
*/

#include "csfml.h"
#include <string.h>

void display_npc(entity_t *npc)
{
    npc_t *npc_struct = npc->entity_struct;

    sfRenderWindow_drawSprite(get_window()->window,
    npc->sprite, NULL);
    if (interact(npc))
        npc_struct->is_interacting = 1;
    if (npc_struct->is_interacting) {
        if (npc_struct->action_npc(npc))
            npc_struct->is_interacting = 0;
    }
}
