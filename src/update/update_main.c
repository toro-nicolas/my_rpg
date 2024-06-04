/*
** EPITECH PROJECT, 2023
** main
** File description:
** main
*/

#include "csfml.h"

void update_npc(void)
{
    entity_t *ent = NULL;

    for (nodes_t *tmp = get_game()->entities_list; tmp; tmp = tmp->next) {
        ent = (entity_t *)(tmp->data);
        if (ent->type == NPC) {
            move_rect(ent, ent->offset_rect, &ent->rect.left, &ent->rect.top,
            &ent->clock, 5.0);
        }
    }
}

void update_main(void)
{
    check_mob_alive();
    check_mob_action();
    if (get_player()->is_attacking)
        attack_mob();
    update_hud();
    update_npc();
    update_player();
    update_item();
    for (nodes_t *tmp = get_game()->entities_list; tmp; tmp = tmp->next) {
        if (((entity_t *)(tmp->data))->type != ITEM)
            update_entity(tmp->data);
    }
}
