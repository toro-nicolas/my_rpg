/*
** EPITECH PROJECT, 2023
** B-MUL-200-NCE-2-1-myrpg-gianni.tuero
** File description:
** create_map.c
*/

#include "csfml.h"

static sfIntRect get_from_map_one(int texture)
{
    static sfIntRect texture_rect[] = {
    {160, 256, 32, 32},
    {224, 256, 32, 38}
    };

    return texture_rect[texture];
}

static sfIntRect get_from_map_two(int texture)
{
    static sfIntRect texture_rect[] = {
    {320, 256, 32, 32},
    {380, 420, 32, 38}
    };

    return texture_rect[texture];
}

static void place_on_map(int i, int j, sfImage *img, char c)
{
    if (c == EMPTY)
        return;
    for (int x = 0; x < 32 * MAP_SCALE; x++)
        for (int y = 0; y < 32 * MAP_SCALE; y++)
            sfImage_setPixel(img, i + x, j + y, sfBlack);
}

static void fill_image(char **buffer, sfImage *create, int size)
{
    for (int i = 1; buffer[i + 1] != NULL; i++) {
        for (int j = 1; buffer[i][j + 1] != 0; j++)
            place_on_map((i - 1) * MAP_SCALE * 32,
            (j - 1) *MAP_SCALE * 32, create, buffer[i][j]);
    }
}

static sfImage *create_color_map(char **room, int size)
{
    sfImage *res = sfImage_createFromColor((size - 2) * 32 * MAP_SCALE,
    (size - 2) * 32 * MAP_SCALE, sfRed);

    fill_image(room, res, size);
    return res;
}

void create_new_map(void)
{
    int size = 30 + (rand() % 20);

    get_game()->map_infos->mob = rand() % 6;
    get_game()->map_infos->type = rand() % 2;
    size = size % 2 == 0 ? size - 1 : size;
    get_game()->map_infos->size = size;
    if (get_game()->map_infos->map != NULL) {
        for (int i = 0; get_game()->map_infos->map[i] != NULL; i++)
            free(get_game()->map_infos->map[i]);
        free(get_game()->map_infos->map);
    }
    get_game()->map_infos->map = generate_whole_map(size, size);
    if (get_game()->map_infos->color_map)
        sfImage_destroy(get_game()->map_infos->color_map);
    get_game()->map_infos->color_map =
    create_color_map(get_game()->map_infos->map, size);
    place_mobs_map();
    place_npc_map();
    move_end_ladder();
}

static void draw_map_c(int i, int j)
{
    sfSprite_setPosition(get_game()->map_infos->tile,
    (sfVector2f){(i - 1) * 32 * MAP_SCALE, (j - 1) * 32 * MAP_SCALE});
    sfSprite_setScale(get_game()->map_infos->tile,
    (sfVector2f){MAP_SCALE, MAP_SCALE});
    sfRenderWindow_drawSprite(get_window()->window,
    get_game()->map_infos->tile, NULL);
}

static void from_map(int size, int i, int j)
{
    if (j + 1 < size && get_game()->map_infos->map[i][j + 1] == EMPTY) {
        if (get_game()->map_infos->type)
            sfSprite_setTextureRect(get_game()->map_infos->tile,
            get_from_map_two(1));
        else
            sfSprite_setTextureRect(get_game()->map_infos->tile,
            get_from_map_one(1));
        return;
    }
    if (get_game()->map_infos->type)
        sfSprite_setTextureRect(get_game()->map_infos->tile,
        get_from_map_two(0));
    else
        sfSprite_setTextureRect(get_game()->map_infos->tile,
        get_from_map_one(0));
}

void draw_bg(void)
{
    sfView_setCenter(get_window()->view, (sfVector2f){960, 540});
    sfRenderWindow_setView(get_window()->window, get_window()->view);
    move_rect(get_entity("bg2"),
    get_entity("bg2")->offset_rect, &get_entity("bg2")->rect.left,
    &get_entity("bg2")->rect.top, &get_entity("bg2")->clock, 1.0);
    sfRenderWindow_drawSprite(get_window()->window,
    get_entity("bg2")->sprite, NULL);
    sfView_setCenter(get_window()->view, get_player_entity()->position);
    sfRenderWindow_setView(get_window()->window, get_window()->view);
}

void draw_map(void)
{
    int size = get_game()->map_infos->size;
    int i = 0;
    int j = 0;

    draw_bg();
    for (int k = 0; get_game()->map_infos->map[k / size] != NULL; k++) {
        i = k / size;
        j = k % size;
        if (i == 0 || i == size - 1 || j == 0 || j == size - 1)
            continue;
        if (get_game()->map_infos->map[i][j] == EMPTY)
            continue;
        from_map(size, i, j);
        draw_map_c(i, j);
    }
}
