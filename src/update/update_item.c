/*
** EPITECH PROJECT, 2023
** main
** File description:
** main
*/

#include <string.h>
#include "csfml.h"

entity_t *get_new_item(sfVector2f pos, int id)
{
    static char *name[] = {"lance1", "sceptre1", "dague1",
    "lance2", "sceptre2", "dague2",
    "lance3", "sceptre3", "dague3",
    "lance4", "sceptre4", "dague4"};
    static sfVector2f scale[] = {{0.5, 0.5}, {0.3, 0.3}, {0.3, 0.3},
    {0.5, 0.5}, {0.3, 0.3}, {0.3, 0.3}, {0.5, 0.5}, {0.3, 0.3}, {0.3, 0.3},
    {0.5, 0.5}, {0.3, 0.3}, {0.3, 0.3}};
    sfSprite *sprite = create_sprite(5, get_game()->main_texture,
    get_stat_rect(name[id]), pos, V2F {0, 0}, scale[id]);
    item_t *item_struct = MALLOC(sizeof(item_t));
    sfRectangleShape *hitbox = create_rectangle(7,
    V2F {get_stat_rect(name[id]).width, get_stat_rect(name[id]).height}
    , pos, V2F {0, 0}, scale[id], sfTransparent, sfWhite, 8);
    entity_t *entity = create_entity(5, ITEM, name[id], sprite,
    item_struct, hitbox);

    item_struct->interaction = &interact;
    push_b_doubly(&get_game()->entities_list, entity, UNKNOW);
    return entity;
}

void update_pos(entity_t **tab)
{
    entity_t *entity = NULL;
    int signe = 1;

    for (int i = 0; i < 3; i++) {
        if (!tab[i])
            continue;
        entity = tab[i];
        if (sfSprite_getScale(get_player_entity()->sprite).x < 0)
            signe = -1;
        entity->position =
        V2F {PLAYER_POS.x + 10 * signe, PLAYER_POS.y};
        sfSprite_setScale(entity->sprite,
        V2F {entity->scale.x * signe, entity->scale.y});
        sfRectangleShape_setScale(entity->hitbox,
        V2F {entity->scale.x * signe, entity->scale.y});
        sfSprite_setPosition(entity->sprite, entity->position);
        sfRectangleShape_setPosition(entity->hitbox, entity->position);
    }
}

void update_item(void)
{
    update_pos(get_player()->items);
}
