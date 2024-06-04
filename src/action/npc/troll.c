/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** random npc
*/

#include "csfml.h"

char **troll_dialog(void)
{
    static char *dialog[] = {
        "Ah, j'ai plein de chose \na te dire !",
        "Tu dois arriver au \ndixieme etage pour",
        "... pour faire quoi deja ?",
        "mince j'ai oublie...",
        "Bonne chance !",
        NULL};

    return dialog;
}

int troll(entity_t *self)
{
    sfFloatRect npc_r =
        sfRectangleShape_getGlobalBounds(self->hitbox);
    sfFloatRect player_r =
        sfRectangleShape_getGlobalBounds(get_player_entity()->hitbox);

    if (!sfFloatRect_intersects(&npc_r, &player_r, NULL)) {
        display_chatnpc(troll_dialog(), self->position, 1);
        ((npc_t *)self->entity_struct)->is_interacting = 0;
        return 0;
    }
    return display_chatnpc(troll_dialog(), self->position, 0);
}
