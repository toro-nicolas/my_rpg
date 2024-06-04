/*
** EPITECH PROJECT, 2023
** main
** File description:
** main
*/

#include <string.h>
#include "csfml.h"

void init_bg(void)
{
    static sfSprite *bg = NULL;
    static entity_t *bg_entity = NULL;

    if (bg == NULL) {
        bg = sfSprite_create();
        sfSprite_setTexture(bg, get_game()->main_texture, sfTrue);
        sfSprite_setTextureRect(bg,
        (sfIntRect){4630, 540, 1920, 1080});
        bg_entity = create_entity(3, DECOR, "bg", bg);
        push_f_doubly(&get_game()->entities_list, bg_entity, UNKNOW);
        bg_entity->offset_rect = MALLOC(sizeof(int) * 6);
        bg_entity->offset_rect[0] = 5;
        bg_entity->offset_rect[1] = 6550;
        bg_entity->offset_rect[2] = 4630;
        bg_entity->offset_rect[3] = 0;
        bg_entity->offset_rect[4] = 540;
        bg_entity->offset_rect[5] = 540;
    }
}

void init_bg2(void)
{
    static sfSprite *bg = NULL;
    static entity_t *bg_entity = NULL;

    if (bg == NULL) {
        bg = sfSprite_create();
        sfSprite_setTexture(bg, get_game()->main_texture, sfTrue);
        sfSprite_setTextureRect(bg,
        (sfIntRect){5632, 1620, 1920, 1080});
        bg_entity = create_entity(3, DECOR, "bg2", bg);
        push_f_doubly(&get_game()->entities_list, bg_entity, UNKNOW);
        bg_entity->offset_rect = MALLOC(sizeof(int) * 6);
        bg_entity->offset_rect[0] = 5;
        bg_entity->offset_rect[1] = 5632 + 1920;
        bg_entity->offset_rect[2] = 5632;
        bg_entity->offset_rect[3] = 0;
        bg_entity->offset_rect[4] = 1620;
        bg_entity->offset_rect[5] = 1620;
    }
}
