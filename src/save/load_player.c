/*
** EPITECH PROJECT, 2024
** B-MUL-200-NCE-2-1-myrpg-gianni.tuero
** File description:
** The load_player.c
*/
/**
 * @file load_player.c
 * @brief The load_player.c
 * @author Nicolas TORO
 */

#include "csfml.h"

static sfSprite *load_player_sprite(char *sprite_type)
{
    sfSprite *sprite = sfSprite_create();
    char **tmp = my_super_array(sprite_type, " \t=");
    int type = 0;

    if (tmp == NULL || my_array_of_array_len(tmp) != 2 ||
        my_strcmp(tmp[0], "sprite") != 0 ||
        my_getnbr(tmp[1]) < 0 || my_getnbr(tmp[1]) > 2)
        type = 0;
    else
        type = my_getnbr(tmp[1]);
    sfSprite_setTexture(sprite, get_game()->main_texture, sfTrue);
    sfSprite_setScale(sprite, (sfVector2f){5, 5});
    sfSprite_setOrigin(sprite, (sfVector2f){16, 16});
    sfSprite_setTextureRect(sprite,
        (sfIntRect){1922, 2559 + type * 288, 32, 32});
    return sprite;
}

static void load_stat3(char **line)
{
    if (my_strcmp(line[0], "stat-max_defensew") == 0) {
        get_player()->max_defensew = my_getnbr_float(line[1]);
        return;
    }
    if (my_strcmp(line[0], "stat-item") == 0) {
        get_player()->cur_item = my_getnbr(line[1]);
        return;
    }
    if (my_strcmp(line[0], "stat-x") == 0) {
        get_player_entity()->position.x = my_getnbr_float(line[1]);
        return;
    }
    if (my_strcmp(line[0], "stat-y") == 0)
        get_player_entity()->position.y = my_getnbr_float(line[1]);
}

static void load_stat2(char **line)
{
    if (my_strcmp(line[0], "stat-max_speedw") == 0) {
        get_player()->max_speedw = my_getnbr_float(line[1]);
        return;
    }
    if (my_strcmp(line[0], "stat-attack") == 0) {
        get_player()->attack = my_getnbr_float(line[1]);
        return;
    }
    if (my_strcmp(line[0], "stat-max_attackw") == 0) {
        get_player()->max_attackw = my_getnbr_float(line[1]);
        return;
    }
    if (my_strcmp(line[0], "stat-defense") == 0) {
        get_player()->defense = my_getnbr_float(line[1]);
        return;
    }
    load_stat3(line);
}

static void load_stat(char **line)
{
    if (my_strcmp(line[0], "stat-hp") == 0) {
        get_player()->hp = my_getnbr_float(line[1]);
        return;
    }
    if (my_strcmp(line[0], "stat-max_hp") == 0) {
        get_player()->max_hp = my_getnbr_float(line[1]);
        return;
    }
    if (my_strcmp(line[0], "stat-max_hpw") == 0) {
        get_player()->max_hpw = my_getnbr_float(line[1]);
        return;
    }
    if (my_strcmp(line[0], "stat-speed") == 0) {
        get_player()->speed = my_getnbr_float(line[1]);
        return;
    }
    load_stat2(line);
}

static void load_lvl(char **line)
{
    if (my_strcmp(line[0], "lvl-level") == 0) {
        get_player()->level = my_getnbr(line[1]);
        return;
    }
    if (my_strcmp(line[0], "lvl-xp") == 0) {
        get_player()->xp = my_getnbr(line[1]);
        return;
    }
    if (my_strcmp(line[0], "lvl-xp_next") == 0) {
        get_player()->xp_to_next_level = my_getnbr(line[1]);
        return;
    }
    if (my_strcmp(line[0], "lvl-old") == 0)
        get_player()->old_level = my_getnbr(line[1]);
}

static entity_t *get_item(char *line)
{
    entity_t *item = NULL;

    if (my_strlen(line) <= 9 || (line[5] != '1' &&
    line[5] != '2' && line[5] != '3') || (line[7] < 'A' || line[7] > 'L'))
        return NULL;
    item = get_player()->items[line[5] - '1'];
    if (item == NULL)
        get_player()->items[line[5] - '1'] =
        get_new_item(V2F {0, 0}, line[7] - 'A');
    return item;
}

static void load_item_stats(char **line, item_t *item)
{
    if (my_strcmp(line[0] + 9, "attack") == 0) {
        item->attack = my_getnbr_float(line[1]);
        return;
    }
    if (my_strcmp(line[0] + 9, "defense") == 0) {
        item->defense = my_getnbr_float(line[1]);
        return;
    }
    if (my_strcmp(line[0] + 9, "hp") == 0) {
        item->hp = my_getnbr_float(line[1]);
        return;
    }
    if (my_strcmp(line[0] + 9, "speed") == 0) {
        item->speed = my_getnbr_float(line[1]);
        return;
    }
    if (my_strcmp(line[0] + 9, "index") == 0)
        item->index = my_getnbr(line[1]);
}

static void load_item(char **line)
{
    entity_t *item = get_item(line[0]);
    player_t *player = get_player();

    if (item == NULL)
        return;
    load_item_stats(line, item->entity_struct);
}

void load_player(void)
{
    char **file_content = my_super_array(get_file("save/player"), "\n");
    char **tmp = NULL;
    sfSprite *sprite = load_player_sprite(file_content[0]);

    get_game()->player = init_player(&sprite);
    for (int i = 1; file_content[i]; i++) {
        tmp = my_super_array(file_content[i], " \t=");
        if (my_array_of_array_len(tmp) != 2)
            continue;
        if (my_strncmp(tmp[0], "stat", 4) == 0) {
            load_stat(tmp);
            continue;
        }
        if (my_strncmp(tmp[0], "lvl", 3) == 0) {
            load_lvl(tmp);
            continue;
        }
        if (my_strncmp(tmp[0], "item", 4) == 0)
            load_item(tmp);
    }
}
