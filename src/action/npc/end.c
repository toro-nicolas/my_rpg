/*
** EPITECH PROJECT, 2023
** B-MUL-200-NCE-2-1-myrpg-gianni.tuero
** File description:
** end.c
*/

#include "csfml.h"

static char **end_npc_dialog(void)
{
    static char *dialog[] = {
        "Felicitations,",
        "Tu as termine ma\nmission",
        "Pour te\nrecompenser",
        "...",
        "...",
        "...",
        "Rien en fait.",
        "La vraie\nrécompense...",
        "Ne serait-ce\npas",
        "Les amis qu'on a\nfait le long",
        "Du voyage ?",
        "Sinon !",
        "Tu peux continuer\na jouer.",
        "Voyons jusqu ou\nton talent",
        "T'ameneras.",
        "Bon voyage",
        NULL};

    return dialog;
}

int end_npc(entity_t *self)
{
    sfFloatRect npc_r =
        sfRectangleShape_getGlobalBounds(self->hitbox);
    sfFloatRect player_r =
        sfRectangleShape_getGlobalBounds(get_player_entity()->hitbox);

    if (!sfFloatRect_intersects(&npc_r, &player_r, NULL)) {
        display_chatnpc(end_npc_dialog(), self->position, 1);
        ((npc_t *)self->entity_struct)->is_interacting = 0;
        return 0;
    }
    if (display_chatnpc(end_npc_dialog(), self->position, 0)) {
        remove_me(self);
        return 1;
    }
    return 0;
}
