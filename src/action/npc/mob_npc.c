/*
** EPITECH PROJECT, 2023
** B-MUL-200-NCE-2-1-myrpg-gianni.tuero
** File description:
** mob_npc.c
*/

#include "csfml.h"

static char **mob_two_dialog(void)
{
    static char *dialog[] = {
        "Tu es dans de beaux \ndraps petit aventurier",
        "A l'attaque !",
        NULL};

    return dialog;
}

static void mob_two_interact(entity_t *self)
{
    sfVector2f pos = self->position;

    init_jar_mimic(V2F {pos.x + 10, pos.y + 10});
    init_jar_mimic(V2F {pos.x - 10, pos.y + 10});
    init_jar_mimic(V2F {pos.x + 10, pos.y - 10});
    init_jar_mimic(V2F {pos.x - 10, pos.y - 10});
}

int mob_npc_two(entity_t *self)
{
    sfFloatRect npc_r =
        sfRectangleShape_getGlobalBounds(self->hitbox);
    sfFloatRect player_r =
        sfRectangleShape_getGlobalBounds(get_player_entity()->hitbox);

    if (!sfFloatRect_intersects(&npc_r, &player_r, NULL)) {
        display_chatnpc(mob_two_dialog(), self->position, 1);
        ((npc_t *)self->entity_struct)->is_interacting = 0;
        return 0;
    }
    if (display_chatnpc(mob_two_dialog(), self->position, 0)) {
        mob_two_interact(self);
        remove_me(self);
        return 1;
    }
    return 0;
}

static char **mob_one_dialog(void)
{
    static char *dialog[] = {
        "Hahaha tu es tombé\n dans mon piege",
        NULL};

    return dialog;
}

static void mob_one_interact(entity_t *self)
{
    sfVector2f pos = self->position;

    init_gladiator(pos);
}

int mob_npc_one(entity_t *self)
{
    sfFloatRect npc_r =
        sfRectangleShape_getGlobalBounds(self->hitbox);
    sfFloatRect player_r =
        sfRectangleShape_getGlobalBounds(get_player_entity()->hitbox);

    if (!sfFloatRect_intersects(&npc_r, &player_r, NULL)) {
        display_chatnpc(mob_one_dialog(), self->position, 1);
        ((npc_t *)self->entity_struct)->is_interacting = 0;
        return 0;
    }
    if (display_chatnpc(mob_one_dialog(), self->position, 0)) {
        mob_one_interact(self);
        remove_me(self);
        return 1;
    }
    return 0;
}
