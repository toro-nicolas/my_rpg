/*
** EPITECH PROJECT, 2023
** B-MUL-200-NCE-2-1-myrpg-gianni.tuero
** File description:
** inventory_npc.c
*/

#include "csfml.h"

static char **thief_npc_dialog(void)
{
    static char *dialog[] = {
        "Je suis le voleur\nHehehehehe",
        NULL};

    return dialog;
}

static void thief_one_interact(void)
{
    get_player()->items[0] = NULL;
    get_player()->items[1] = NULL;
    get_player()->items[2] = NULL;
}

int thief_npc(entity_t *self)
{
    sfFloatRect npc_r =
        sfRectangleShape_getGlobalBounds(self->hitbox);
    sfFloatRect player_r =
        sfRectangleShape_getGlobalBounds(get_player_entity()->hitbox);

    if (!sfFloatRect_intersects(&npc_r, &player_r, NULL)) {
        display_chatnpc(thief_npc_dialog(), self->position, 1);
        ((npc_t *)self->entity_struct)->is_interacting = 0;
        return 0;
    }
    if (display_chatnpc(thief_npc_dialog(), self->position, 0)) {
        thief_one_interact();
        remove_me(self);
        return 1;
    }
    return 0;
}
