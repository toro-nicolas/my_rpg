/*
** EPITECH PROJECT, 2023
** main
** File description:
** main
*/

#include "csfml.h"

void create_inventory(void)
{
    static sfSprite *inventory_sprite = NULL;
    static entity_t *inventory = NULL;

    if (inventory_sprite)
        return;
    inventory_sprite = create_sprite(5, get_game()->main_texture,
    (sfIntRect){1922, 3440, 903, 200},
    V2F {1920 / 2, 1080 - 50}, V2F {903 / 2, 200 / 2},
    V2F {1, 0.5});
    inventory = create_entity(3, CUSTOM, "inventory", inventory_sprite);
    push_f_doubly(&get_game()->entities_list, inventory, UNKNOW);
}

void update_hud(void)
{
    create_inventory();
    return;
}
