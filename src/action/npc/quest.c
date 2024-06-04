/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** random npc
*/

#include "csfml.h"

char **quest_dialog(void)
{
    static char *dialog[] = {
        "Ah, tu es de retour !",
        "Tu dois arriver au \ndixieme etage pour",
        "gagner quelque \nchose de precieux...",
        "Mais attention, \nil y a des monstres !",
        "Bonne chance !",
        NULL};

    return dialog;
}

int quest(entity_t *self)
{
    sfFloatRect npc_r =
    sfRectangleShape_getGlobalBounds(self->hitbox);
    sfFloatRect player_r =
    sfRectangleShape_getGlobalBounds(get_player_entity()->hitbox);

    if (!sfFloatRect_intersects(&npc_r, &player_r, NULL)) {
        display_chatnpc(quest_dialog(), self->position, 1);
        ((npc_t *)self->entity_struct)->is_interacting = 0;
        return 0;
    }
    return display_chatnpc(quest_dialog(), self->position, 0);
}
