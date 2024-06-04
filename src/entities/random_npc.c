/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** random npc
*/

#include "csfml.h"

static sfTexture *get_npc_texture(char *npc)
{
    static sfTexture *texture = NULL;
    static sfTexture *texture2 = NULL;
    static sfTexture *texture3 = NULL;

    if (texture == NULL)
        texture = sfTexture_createFromFile("assets/reaper.png", NULL);
    if (texture2 == NULL)
        texture2 = sfTexture_createFromFile("assets/golem.png", NULL);
    if (texture3 == NULL)
        texture3 = sfTexture_createFromFile("assets/angel.png", NULL);
    if (strcmp(npc, "reaper") == 0)
        return (texture);
    if (strcmp(npc, "golem") == 0)
        return (texture2);
    if (strcmp(npc, "angel") == 0)
        return (texture3);
    return (NULL);
}

int fill_npc_struct(npc_t *npc_struct, entity_t *npce)
{
    npce->entity_struct = npc_struct;
    npce->clock = 0;
    npce->offset_rect = MALLOC(sizeof(int) * 6);
    npce->offset_rect[0] = 900;
    npce->offset_rect[1] = 3600;
    npce->offset_rect[2] = 0;
    npce->offset_rect[3] = 900;
    npce->offset_rect[4] = 2700;
    npce->offset_rect[5] = 0;
}

entity_t *random_npc(sfVector2f pos)
{
    static char *npc[] = {"reaper", "golem", "angel"};
    static int (*action[])(entity_t *) = {&speak, &troll, &drop_itemnpc,
    &you_are_dead, &mob_npc_two, &mob_npc_one, &thief_npc};
    int random = rand() % 3;
    sfSprite *sprite = create_sprite(5, get_npc_texture(npc[random]),
    (sfIntRect){0, 0, 900, 900}, pos, V2F {450, 450}, V2F {0.2, 0.2});
    sfRectangleShape *hitbox = create_rectangle(7, V2F {900, 900},
    pos, V2F {450, 450}, V2F {0.2, 0.2}, sfTransparent, GREEN, 16);
    entity_t *npce = create_entity(5, NPC, npc[random], sprite, NULL, hitbox);
    npc_t *npc_struct = MALLOC(sizeof(npc_t));

    npc_struct->action_npc = action[rand() % 7];
    fill_npc_struct(npc_struct, npce);
    push_f_doubly(&get_game()->entities_list, npce, UNKNOW);
    return npce;
}
