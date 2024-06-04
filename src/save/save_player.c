/*
** EPITECH PROJECT, 2024
** B-MUL-200-NCE-2-1-myrpg-gianni.tuero
** File description:
** The save_player.c
*/
/**
 * @file save_player.c
 * @brief The save_player.c
 * @author Nicolas TORO
 */

#include "csfml.h"

void write_all_stats(int fd)
{
    my_printf(fd, "sprite=%d\n",
        (get_player_entity()->initial_rect.top - 2559) / 288);
    my_printf(fd, "stat-hp=%f\n", get_player()->hp);
    my_printf(fd, "stat-max_hp=%f\n", get_player()->max_hp);
    my_printf(fd, "stat-max_hpw=%f\n", get_player()->max_hpw);
    my_printf(fd, "stat-attack=%f\n", get_player()->attack);
    my_printf(fd, "stat-max_attackw=%f\n", get_player()->max_attackw);
    my_printf(fd, "stat-defense=%f\n", get_player()->defense);
    my_printf(fd, "stat-defensew=%f\n", get_player()->defense);
    my_printf(fd, "stat-speed=%f\n", get_player()->speed);
    my_printf(fd, "stat-max_speedw=%f\n", get_player()->max_speedw);
    my_printf(fd, "stat-item=%d\n", get_player()->cur_item);
    my_printf(fd, "lvl-level=%d\n", get_player()->level);
    my_printf(fd, "lvl-xp=%d\n", get_player()->xp);
    my_printf(fd, "lvl-xp_next=%d\n", get_player()->xp_to_next_level);
    my_printf(fd, "lvl-old=%d\n", get_player()->old_level);
}

//my_printf(fd, "stat-x=%f\n", get_player_entity()->position.x);
//my_printf(fd, "stat-y=%f\n", get_player_entity()->position.y);
void write_all_items(int fd)
{
    static char *name[] = {"lance1", "sceptre1", "dague1", "lance2",
        "sceptre2", "dague2", "lance3", "sceptre3", "dague3",
        "lance4", "sceptre4", "dague4"};
    int id = 0;
    item_t *item = NULL;

    for (int slot = 1; slot < 4; slot++) {
        if (get_player()->items[slot - 1] == NULL)
            continue;
        item = get_player()->items[slot - 1]->entity_struct;
        for (; id < 12 &&
        my_strcmp(get_player()->items[slot - 1]->id, name[id]); id++);
        my_printf(fd, "item-%d-%c-index=%d\n", slot, 'A' + id, item->index);
        my_printf(fd, "item-%d-%c-attack=%f\n", slot, 'A' + id, item->attack);
        my_printf(fd, "item-%d-%c-defense=%f\n",
            slot, 'A' + id, item->defense);
        my_printf(fd, "item-%d-%c-speed=%f\n", slot, 'A' + id, item->speed);
        my_printf(fd, "item-%d-%c-hp=%f\n", slot, 'A' + id, item->hp);
    }
}

void save_player(void)
{
    int fd = open("save/player", O_CREAT | O_WRONLY | O_TRUNC, 0666);

    if (fd == -1)
        return;
    write_all_stats(fd);
    write_all_items(fd);
    close(fd);
}
