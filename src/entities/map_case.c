/*
** EPITECH PROJECT, 2024
** B-MUL-200-NCE-2-1-myrpg-gianni.tuero
** File description:
** The map_case.c
*/
/**
 * @file map_case.c
 * @brief The map_case.c
 * @author Nicolas TORO
 */

#include "csfml.h"

void display_path(path_t *path)
{
    if (path == NULL) {
        my_printf(1, "No path found\n");
        return;
    }
    for (path_t *tmp = path; tmp; tmp = tmp->prev) {
        my_printf(1, "(%f, %f)", tmp->position.x, tmp->position.y);
        if (tmp->prev)
            my_printf(1, " <- ");
    }
    my_putchar('\n');
}

sfVector2f pos_to_case(sfVector2f vector)
{
    int x = vector.x / CASE_SIZE;
    int y = vector.y / CASE_SIZE;
    int x_middle = (CASE_SIZE / 2) * ((vector.x > 0) ? 1 : -1);
    int y_middle = (CASE_SIZE / 2) * ((vector.y > 0) ? 1 : -1);

    return (sfVector2f){(x * CASE_SIZE) + x_middle,
        (y * CASE_SIZE) + y_middle};
}

int is_invalid_case(sfVector2f map_case)
{
    char **map = get_game()->map_infos->map;
    int x = map_case.x / CASE_SIZE;
    int y = map_case.y / CASE_SIZE;
    char *col = map[x + 1];

    if (x < 0 || y < 0 || map_case.x < 0 || map_case.y < 0 ||
        x >= get_game()->map_infos->size - 2 ||
        y >= get_game()->map_infos->size - 2)
        return 1;
    if (map[x + 1][y + 1] == EMPTY)
        return 1;
    return 0;
}
