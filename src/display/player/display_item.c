/*
** EPITECH PROJECT, 2023
** main
** File description:
** main
*/

#include "csfml.h"

static void replace_on_index(entity_t *item_to_get, int index)
{
    if (get_player()->items[index] != NULL) {
        ((item_t *)get_player()->items[index]->entity_struct)->on_ground = 1;
        get_player()->items[index]->position = item_to_get->position;
        get_player()->items[index] = item_to_get;
        ((item_t *)get_player()->items[index]->entity_struct)->on_ground = 0;
    }
    get_player()->items[index] = item_to_get;
    ((item_t *)get_player()->items[index]->entity_struct)->on_ground = 0;
}

static void move_pos(entity_t **entity, float value)
{
    static int signe = 1;

    if (sfSprite_getPosition((*entity)->sprite).y >
    (*entity)->position.y + value)
        signe = -1;
    if (sfSprite_getPosition((*entity)->sprite).y < (*entity)->position.y)
        signe = 1;
    sfSprite_move((*entity)->sprite, V2F {0, 1 * signe});
    sfRectangleShape_move((*entity)->hitbox, V2F {0, 1 * signe});
    return;
}

void player_on_item(entity_t *entity)
{
    if (interact(entity))
        replace_on_index(entity, get_player()->cur_item);
}

void display_item(entity_t *entity)
{
    item_t *item = (entity->entity_struct);

    if (!item->on_ground)
        return;
    sfRenderWindow_drawSprite(get_window()->window,
    entity->sprite, NULL);
    for (; entity->clock > 0.03; entity->clock -= 0.03)
        move_pos(&entity, 30);
    player_on_item(entity);
}
