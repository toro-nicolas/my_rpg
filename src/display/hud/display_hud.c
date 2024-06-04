/*
** EPITECH PROJECT, 2023
** main
** File description:
** main
*/

#include "csfml.h"

void resize_scale(int max_width, entity_t *entity, sfVector2f *scalei)
{
    sfFloatRect rect = sfSprite_getGlobalBounds(entity->sprite);
    sfVector2f scale = {0, 0};

    if (rect.width > max_width) {
        scale.x = max_width / rect.width;
        scale.y = max_width / rect.width;
        scalei->x = scale.x;
        scalei->y = scale.y;
    }
}

void suite_items_inventory(entity_t *entity,
    sfVector2f scale, sfVector2f old_scale)
{
    sfSprite_setScale(entity->sprite, scale);
    sfRenderWindow_drawSprite(get_window()->window, entity->sprite, NULL);
    sfSprite_setScale(entity->sprite, old_scale);
}

void display_items_in_inventory(void)
{
    entity_t *entity = NULL;
    sfFloatRect inv_pos =
    sfSprite_getGlobalBounds(get_entity("inventory")->sprite);
    sfVector2f pos[] = {V2F {inv_pos.left, inv_pos.top},
        V2F {inv_pos.left + 300, inv_pos.top},
        V2F {inv_pos.left + 600, inv_pos.top}};
    sfVector2f scale = {0, 0};
    sfVector2f old_scale;

    for (int i = 0; i < 3; i++) {
        if (get_player()->items[i] == NULL)
            continue;
        entity = get_player()->items[i];
        scale = entity->scale;
        old_scale = scale;
        scale.x = scale.x < 0 ? -scale.x : scale.x;
        resize_scale(300, entity, &scale);
        sfSprite_setPosition(entity->sprite, pos[i]);
        suite_items_inventory(entity, scale, old_scale);
    }
}

void display_current_item(void)
{
    static sfRectangleShape *rect = NULL;
    sfFloatRect inv_pos =
    sfSprite_getGlobalBounds(get_entity("inventory")->sprite);
    sfVector2f pos[] = {{inv_pos.left, inv_pos.top},
    {inv_pos.left + 300, inv_pos.top}, {inv_pos.left + 600, inv_pos.top}};

    if (!rect) {
        rect = sfRectangleShape_create();
        sfRectangleShape_setSize(rect, V2F {300, 100});
        sfRectangleShape_setFillColor(rect, sfTransparent);
        sfRectangleShape_setOutlineColor(rect, sfWhite);
        sfRectangleShape_setOutlineThickness(rect, -5);
    }
    sfRectangleShape_setPosition(rect, pos[get_player()->cur_item]);
    sfRenderWindow_drawRectangleShape(get_window()->window, rect, NULL);
}

void display_hud(void)
{
    if (get_entity("inventory") == NULL)
        return;
    sfRenderWindow_drawSprite(get_window()->window,
    get_entity("inventory")->sprite, NULL);
    display_items_in_inventory();
    display_current_item();
}
