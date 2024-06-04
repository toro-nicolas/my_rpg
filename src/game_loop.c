/*
** EPITECH PROJECT, 2023
** B-MUL-200-NCE-2-1-myrpg-gianni.tuero
** File description:
** game_loop.c
*/

#include "csfml.h"

static void init_mob(sfVector2f pos)
{
    switch (get_game()->map_infos->mob) {
        case BARREL_MIMIC:
            init_barrel_mimic(pos);
            break;
        case CHEST_MIMIC:
            init_chest_mimic(pos);
            break;
        case GHOUL:
            init_ghoul(pos);
            break;
        case GLADIATOR:
            init_gladiator(pos);
            break;
        case JAR_MIMIC:
            init_jar_mimic(pos);
            break;
        case DEMON:
            init_demon(pos);
            break;
    }
}

void move_end_ladder(void)
{
    int size = get_game()->map_infos->size;
    sfVector2f ladder_pos = V2F {size - 4, size - 4};
    entity_t *ladder = get_entity("ladder");

    ladder->position = V2F {ladder_pos.x * MAP_SCALE * 32,
    ladder_pos.y * MAP_SCALE * 32};
}

void place_mobs_map(void)
{
    int floor = get_game()->map_infos->floor;
    int amount = rand() % floor + floor + 6;

    amount = amount < 6 ? 6 : amount;
    for (; amount > 0; amount--)
        init_mob(get_valid_random_pos());
}

void place_npc_map(void)
{
    int floor = get_game()->map_infos->floor;
    int amount = rand() % 4;
    entity_t *npc = random_npc(V2F {200, 100});

    if (floor == 1)
        ((npc_t *)(npc->entity_struct))->action_npc = &quest;
    if (floor == 10)
        ((npc_t *)(npc->entity_struct))->action_npc = &end_npc;
    for (; amount > 0; amount--)
        random_npc(get_valid_random_pos());
}

void remove_mobs_fl(void)
{
    nodes_t *temp = get_game()->entities_list;
    sfColor cl[] = {sfRed, sfGreen, sfBlue, sfYellow, sfMagenta, sfCyan};
    int color_bg = rand() % 6;

    for (; temp != NULL; temp = temp->next)
        if (((entity_t *)(temp->data))->type == MOB ||
        ((entity_t *)(temp->data))->type == ITEM ||
        ((entity_t *)(temp->data))->type == NPC) {
            previous_to_next(&get_game()->entities_list, temp);
        }
    sfSprite_setColor(get_entity("bg2")->sprite, cl[color_bg]);
}

void restart_game(void)
{
    get_game()->map_infos->floor++;
    remove_mobs_fl();
    for (int i = 0; i < 3; i++) {
        if (get_player()->items[i])
            push_f_doubly(&get_game()->entities_list,
            get_player()->items[i], UNKNOW);
    }
    sfView_setCenter(get_window()->view, (sfVector2f){960, 540});
    sfRenderWindow_setView(get_window()->window, get_window()->view);
    loading_function(&create_new_map);
    sfView_setCenter(get_window()->view, get_player_entity()->position);
    sfRenderWindow_setView(get_window()->window, get_window()->view);
    get_game()->player->position = V2F {100, 100};
}
