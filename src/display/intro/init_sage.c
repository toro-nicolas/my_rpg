/*
** EPITECH PROJECT, 2023
** main
** File description:
** main
*/

#include <string.h>
#include "csfml.h"

void create_sage_entity(entity_t **sage, entity_t **chatbox)
{
    sfSprite *sprite = create_sprite(5, get_game()->main_texture,
    (sfIntRect){1630, 0, 500, 500},
    V2F {1920 / 2 - 300, 1080 / 2 + 200},
    V2F {250, 250}, V2F {1, 1});
    sfSprite *sprite2 = create_sprite(5, get_game()->main_texture,
    (sfIntRect){4630, 0, 770, 540},
    V2F {1920 / 2 - 700, 1080 / 2 - 400}, V2F {0, 0}, V2F {1, 0.5});

    *sage = create_entity(3, NPC, "sage", sprite);
    (*sage)->offset_rect = MALLOC(sizeof(int) * 6);
    (*sage)->offset_rect[0] = 500;
    (*sage)->offset_rect[1] = 4130;
    (*sage)->offset_rect[2] = 1630;
    (*sage)->offset_rect[3] = 500;
    (*sage)->offset_rect[4] = 2000;
    (*sage)->offset_rect[5] = 0;
    *chatbox = create_entity(3, DECOR, "chatbox", sprite2);
    push_f_doubly(&get_game()->entities_list, *sage, UNKNOW);
    push_f_doubly(&get_game()->entities_list, *chatbox, UNKNOW);
}

void init_sage(void)
{
    entity_t *sage = NULL;
    entity_t *chatbox = NULL;

    create_sage_entity(&sage, &chatbox);
    sage->entity_struct = MALLOC(sizeof(npc_t));
    ((npc_t *)sage->entity_struct)->action_npc = &quest;
}
