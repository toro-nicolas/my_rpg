/*
** EPITECH PROJECT, 2023
** B-MUL-200-NCE-2-1-myrpg-gianni.tuero
** File description:
** die_loser.c
*/

#include "csfml.h"

static char **dead_dialog(void)
{
    static char *dialog[] = {
        "Ah, alors tu veux\nrejoindre mon equipe",
        "Mais tu n'es pas pret",
        "Tu es sur de vouloir\ncontinuer ?",
        "Je t'assure c'est une\nmauvaise idee...",
        "Je te laisse une \ndernière chance",
        "Aller Aller vas t'en",
        "Encore la ?",
        "J'en ai marre de toi",
        "Trop c'est trop",
        "Tu n'es pas digne",
        NULL};

    return dialog;
}

void kill_player(void)
{
    int power = rand() % 100;

    if (power < 1)
        get_player()->max_hp += 1000;
    get_player()->hp = 0;
}

int you_are_dead(entity_t *self)
{
    sfFloatRect npc_r =
        sfRectangleShape_getGlobalBounds(self->hitbox);
    sfFloatRect player_r =
        sfRectangleShape_getGlobalBounds(get_player_entity()->hitbox);

    if (!sfFloatRect_intersects(&npc_r, &player_r, NULL)) {
        display_chatnpc(dead_dialog(), self->position, 1);
        ((npc_t *)self->entity_struct)->is_interacting = 0;
        return 0;
    }
    if (display_chatnpc(dead_dialog(), self->position, 0)) {
        kill_player();
        return 1;
    }
    return 0;
}
