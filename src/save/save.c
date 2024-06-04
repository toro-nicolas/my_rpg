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

void save_game(void)
{
    struct stat folder;

    if (stat("save", &folder) == -1)
        mkdir("save", 0755);
    save_player();
    save_map();
    save_entities();
}
