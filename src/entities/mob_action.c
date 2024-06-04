/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** The mob_attack.c
*/
/**
 * @file mob_attack.c
 * @brief The mob_attack.c
 * @author Nicolas TORO
 */

#include "csfml.h"

void move_mob(entity_t *entity)
{
    path_t *path =
        get_best_path(pos_to_case(entity->position),
        pos_to_case(get_player_entity()->position));
    path_t *tmp = path;
    nodes_t *visited = get_visited_list(NULL);
    sfVector2f new_pos = {0};

    if (path == NULL)
        return;
    for (; tmp->prev != NULL && tmp->prev->prev != NULL; tmp = tmp->prev);
    entity->position = move_to_next_point(entity->position, tmp->position,
    ((mob_t *)entity->entity_struct)->speed, entity);
    delete_list(&visited, "nd");
}

void check_mob_action(void)
{
    entity_t *entity = NULL;
    mob_t *mob = NULL;
    player_t *player = get_player();

    for (nodes_t *tmp = get_game()->entities_list; tmp; tmp = tmp->next) {
        entity = tmp->data;
        mob = (mob_t *)entity->entity_struct;
        if (entity->type == MOB && mob->animation.orientation == ATTACK &&
        mob->animation.hit_frame - 1 == mob->animation.current
        && player->hp > 0 &&
        is_hitbox_intersecting(get_player_entity()->hitbox, entity->hitbox)) {
            player->hp -= calculate_damage(mob->attack, player->defense);
            player->is_hit = true;
            knockback(entity, get_player_entity(), 0);
            play_sound(get_player_entity(), SOUND_DAMAGE);
        }
        if (entity->type == MOB && mob->animation.orientation == MOVE)
            move_mob(entity);
    }
}
