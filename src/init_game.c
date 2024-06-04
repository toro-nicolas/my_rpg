/*
** EPITECH PROJECT, 2023
** main
** File description:
** main
*/

#include "csfml.h"

void init_levelup_sprite(void)
{
    sfSprite *sprite = create_sprite(5, get_game()->main_texture,
    (sfIntRect){512, 470, 100, 100},
    V2F {0, 0}, V2F {50, 50},
    V2F {0.5, 0.5});
    entity_t *levelup = create_entity(3, DECOR, "levelup_sprite", sprite);

    push_f_doubly(&get_game()->entities_list, levelup, UNKNOW);
}

static void init_floor_next(void)
{
    sfSprite *sprite = create_sprite(5, get_game()->main_texture,
    (sfIntRect){100, 420, 20, 30},
    V2F {0, 0}, V2F {0, 0},
    V2F {4, 4});
    sfRectangleShape *rec = create_rectangle(7, V2F {20, 30}, V2F {0, 0},
    V2F {0, 0}, V2F {4, 4}, sfTransparent, sfCyan, 2);
    entity_t *levelup = create_entity(5, DECOR, "ladder", sprite, NULL, rec);

    push_f_doubly(&get_game()->entities_list, levelup, UNKNOW);
}

static void fill_player_struct(player_t **player_struct)
{
    (*player_struct)->hp = 10;
    (*player_struct)->max_hp = 10;
    (*player_struct)->attack = 2;
    (*player_struct)->defense = 2;
    (*player_struct)->level = 0;
    (*player_struct)->xp = 0;
    (*player_struct)->speed = 1000;
    (*player_struct)->xp_to_next_level = 10;
    (*player_struct)->orientation = NONE;
    (*player_struct)->loot = 0;
    (*player_struct)->action = NULL;
    (*player_struct)->heal_clock = 0;
}

static void fill_offset_rect(entity_t **player)
{
    (*player)->offset_rect[0] = (*player)->rect.width;
    (*player)->offset_rect[1] = (*player)->rect.left + 32;
    (*player)->offset_rect[2] = (*player)->rect.left;
    (*player)->offset_rect[3] = 0;
    (*player)->offset_rect[4] = (*player)->rect.top;
    (*player)->offset_rect[5] = (*player)->rect.top;
}

entity_t *init_player(sfSprite **sprite)
{
    entity_t *player = create_entity(3, PLAYER, "player", *sprite);
    player_t *player_struct = MALLOC(sizeof(player_t));

    player->hitbox = create_rectangle(7, V2F {22, 22}, player->position,
    V2F {player->origin.x - 5, player->origin.y - 6}, player->scale,
    sfTransparent, sfRed, 1);
    player->entity_struct = player_struct;
    player_struct->orientation = NONE;
    player_struct->cur_item = 0;
    player_struct->action = &action_player;
    player_struct->is_dead = 0;
    player_struct->items = MALLOC(sizeof(entity_t *) * 4);
    player->offset_rect = MALLOC(sizeof(int) * 6);
    player->entity_struct = player_struct;
    player->position = V2F {100, 100};
    sfSprite_setPosition(player->sprite, player->position);
    sfRectangleShape_setPosition(player->hitbox, player->position);
    fill_player_struct(&player_struct);
    fill_offset_rect(&player);
    return player;
}

void init_window(void)
{
    window_info_t *window = get_window();

    window->video_mode = (sfVideoMode){1920, 1080, 32};
    window->framerate = 60;
    window->size = 1;
    window->vol_music = 50;
    window->vol_fx = 50;
    window->delay = 0;
    window->clock = sfClock_create();
    window->text = sfText_create();
    window->window = sfRenderWindow_create(window->video_mode,
    "Drysfa Xaar", sfClose, NULL);
    sfRenderWindow_setPosition(window->window, (sfVector2i){0, 0});
    window->view = sfView_createFromRect((sfFloatRect){0, 0, 1920, 1080});
    sfRenderWindow_setView(window->window, window->view);
    sfRenderWindow_setFramerateLimit(window->window, 60);
}

void init_game_help(void)
{
    srand(time(NULL));
    get_game()->user_variables = get_user();
    init_levelup_sprite();
    get_game()->map_infos = malloc(sizeof(map_t));
    get_game()->map_infos->tile = sfSprite_create();
    get_game()->map_infos->color_map = NULL;
    get_game()->map_infos->map = NULL;
    get_game()->map_infos->floor = 1;
    sfSprite_setTexture(get_game()->map_infos->tile,
    get_game()->main_texture, sfFalse);
    init_floor_next();
}

void init_game(void)
{
    get_game()->window_i = get_window();
    get_game()->main_texture = sfTexture_createFromFile(TEXTURE, NULL);
    get_game()->cur_state = MENU;
    init_window();
    play_sound(NULL, MUSIC_INTRO);
    splash_function(&init_game_help);
    play_music(MUSIC_MENU);
}
