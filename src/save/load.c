/*
** EPITECH PROJECT, 2024
** B-MUL-200-NCE-2-1-myrpg-gianni.tuero
** File description:
** The save.c
*/
/**
 * @file save.c
 * @brief The save.c
 * @author Nicolas TORO
 */

#include "csfml.h"

void load_save(void)
{
    load_player();
    init_bg2();
    if (get_game()->map_infos == NULL) {
        LEFTM = 0;
        loading_function(&create_new_map);
        play_music(MUSIC_GAME);
    } else {
        restart_game();
    }
}
