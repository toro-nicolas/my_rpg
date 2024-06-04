/*
** EPITECH PROJECT, 2023
** main
** File description:
** main
*/

#include "csfml.h"

sfFont *get_font(void)
{
    static sfFont *font = NULL;

    if (!font)
        font = sfFont_createFromFile(FONT);
    return font;
}

entity_t *get_entity(char *id)
{
    entity_t *entity = NULL;

    for (nodes_t *tmp = get_game()->entities_list; tmp; tmp = tmp->next) {
        entity = tmp->data;
        if (my_strcmp(entity->id, id) == 0)
            return entity;
    }
    return NULL;
}

keys_t *get_keys(void)
{
    static keys_t keys = {0};

    return &keys;
}

bind_t *get_bind(void)
{
    static bind_t bind = {0, 72, 73, 74, 75,
    1, 37, 5, 28, 29,
    30, 18, 8, 13, 16,
    59, 24};

    return &bind;
}

static sfIntRect suiterect(char *stat)
{
    if (my_strcmp(stat, "lance2") == 0)
        return (sfIntRect) {3490, 3209, 556, 103};
    if (my_strcmp(stat, "sceptre2") == 0)
        return (sfIntRect) {3366, 3327, 407, 143};
    if (my_strcmp(stat, "dague2") == 0)
        return (sfIntRect) {3477, 3480, 385, 160};
    if (my_strcmp(stat, "lance3") == 0)
        return (sfIntRect) {4149, 3194, 580, 126};
    if (my_strcmp(stat, "sceptre3") == 0)
        return (sfIntRect) {3920, 3345, 424, 110};
    if (my_strcmp(stat, "dague3") == 0)
        return (sfIntRect) {4135, 3488, 384, 152};
    if (my_strcmp(stat, "lance4") == 0)
        return (sfIntRect) {4826, 3200, 556, 120};
    if (my_strcmp(stat, "sceptre4") == 0)
        return (sfIntRect) {4464, 3322, 394, 160};
    if (my_strcmp(stat, "dague4") == 0)
        return (sfIntRect) {4817, 3488, 380, 152};
    return (sfIntRect) {0, 0, 0, 0};
}

sfIntRect get_stat_rect(char *stat)
{
    if (my_strcmp(stat, "hp") == 0)
        return (sfIntRect) {512, 570, 100, 100};
    if (my_strcmp(stat, "atk") == 0)
        return (sfIntRect) {512, 470, 100, 100};
    if (my_strcmp(stat, "def") == 0)
        return (sfIntRect) {612, 470, 100, 100};
    if (my_strcmp(stat, "life") == 0)
        return (sfIntRect) {612, 570, 95, 90};
    if (my_strcmp(stat, "speed") == 0)
        return (sfIntRect) {6145, 2700, 100, 100};
    if (my_strcmp(stat, "lance1") == 0)
        return (sfIntRect) {2826, 3194, 556, 126};
    if (my_strcmp(stat, "sceptre1") == 0)
        return (sfIntRect) {2826, 3320, 394, 160};
    if (my_strcmp(stat, "dague1") == 0)
        return (sfIntRect) {2826, 3480, 394, 160};
    if (my_strcmp(stat, "pressE") == 0)
        return (sfIntRect) {2178, 2559, 400, 400};
    return suiterect(stat);
}
