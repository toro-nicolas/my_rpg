/*
** EPITECH PROJECT, 2023
** main
** File description:
** main
*/

#include "csfml.h"

static void text_suite(float boost[], char str[],
    sfVector2f pos, sfColor color[])
{
    sfIntRect old_rect =
    sfSprite_getTextureRect(get_entity("levelup_sprite")->sprite);

    for (int i = 0; i < 4; i++) {
        if (boost[i] == 0)
            continue;
        sfText_setPosition(get_game()->text_chatbox, pos);
        my_strcat(str, my_float_to_str(boost[i], 2));
        sfText_setCharacterSize(get_game()->text_chatbox, 20);
        sfText_setString(get_game()->text_chatbox, str);
        sfText_setColor(get_game()->text_chatbox, color[i]);
        sfRenderWindow_drawText(get_window()->window,
        get_game()->text_chatbox, NULL);
        sfSprite_setTextureRect(get_entity("levelup_sprite")->sprite,
        old_rect);
        str[1] = '\0';
        pos.y -= 25;
    }
}

void display_stats_weapon(entity_t *weapon)
{
    sfVector2f pos = {1920 / 2 + 70 * 2 + 25, 1080 / 2 - 30 * 2};
    item_t *item = weapon->entity_struct;
    float boost[] = {item->attack, item->defense, item->speed, item->hp};
    sfColor color[] = {RED, BLUE, sfYellow, GREEN};
    char *rect[] = {"atk", "def", "speed", "hp"};
    char str[10] = "+";

    text_suite(boost, str, pos, color);
}

void display_current_weapon(void)
{
    entity_t *weapon = current_weapon();
    sfVector2f pos = {1920 / 2 + 70 * 2 + 25, 1080 / 2 + 80 * 2};

    if (!weapon)
        return;
    weapon = current_weapon();
    sfSprite_setPosition(weapon->sprite, pos);
    sfSprite_setScale(weapon->sprite, V2F {0.3, 0.3});
    sfSprite_setRotation(weapon->sprite, -90);
    sfRenderWindow_drawSprite(get_window()->window, weapon->sprite, NULL);
    sfSprite_setRotation(weapon->sprite, 0);
    display_stats_weapon(weapon);
}

void display_weapons(void)
{
    entity_t *weapon = NULL;
    sfVector2f pos[] = {{1920 / 2 - 242, 1080 / 2 + 55 * 2 + 10},
        {1920 / 2 - 64 * 2, 1080 / 2 + 55 * 2 + 10},
        {1920 / 2 - 7 * 2, 1080 / 2 + 55 * 2 + 10}};

    for (int i = 0; i < 3; i++) {
        if (!get_player()->items[i])
            continue;
        weapon = get_player()->items[i];
        sfSprite_setPosition(weapon->sprite,
        pos[i]);
        sfSprite_setScale(weapon->sprite, V2F {0.2, 0.2});
        sfRenderWindow_drawSprite(get_window()->window, weapon->sprite, NULL);
    }
}

void display_player_equipments(void)
{
    sfVector2f scale = {6.5, 6.5};
    sfVector2f pos = {1920 / 2 - 140, 1080 / 2 - 28};
    sfVector2f pos_backup = sfSprite_getPosition(get_player_entity()->sprite);
    sfVector2f scale_backup = sfSprite_getScale(get_player_entity()->sprite);

    sfSprite_setPosition(get_player_entity()->sprite, pos);
    sfSprite_setScale(get_player_entity()->sprite, scale);
    sfRenderWindow_drawSprite(get_window()->window,
        get_player_entity()->sprite, NULL);
    sfSprite_setPosition(get_player_entity()->sprite, pos_backup);
    sfSprite_setScale(get_player_entity()->sprite, scale_backup);
    display_weapons();
    display_current_weapon();
}

void display_equipments(void)
{
    static sfSprite *sprite = NULL;

    if (!sprite)
        sprite = create_sprite(4, get_game()->main_texture,
        (sfIntRect){5632, 2700, 514, 416}, V2F {1920 / 2, 1080 / 2},
        V2F {514 / 2, 416 / 2});
    sfRenderWindow_drawSprite(get_window()->window, sprite, NULL);
    display_player_equipments();
    display_globalstat();
    return;
}
