/*
** EPITECH PROJECT, 2023
** main
** File description:
** main
*/

#include <string.h>
#include "csfml.h"

static int display_char(sfSprite **sprite,
    sfIntRect texture_rect, sfVector2f pos)
{
    sfFloatRect rect;
    sfRectangleShape *rectangle =
    create_rectangle(7, (sfVector2f){32, 32}, pos,
    V2F {16, 16}, V2F {5, 5}, sfTransparent, sfRed, 2);

    sfSprite_setPosition(*sprite, pos);
    rect = sfSprite_getGlobalBounds(*sprite);
    sfSprite_setTextureRect(*sprite, texture_rect);
    if (sfFloatRect_contains(&rect, get_window()->mouse_pos.x,
        get_window()->mouse_pos.y)) {
        sfSprite_setScale(*sprite, V2F {5, 5});
        sfRectangleShape_setScale(rectangle, V2F {5, 5});
        sfRenderWindow_drawRectangleShape(get_window()->window,
        rectangle, NULL);
        if (LEFTM)
            return 1;
    } else
        sfSprite_setScale(*sprite, (sfVector2f) {4, 4});
    sfRenderWindow_drawSprite(get_window()->window, *sprite, NULL);
    return 0;
}

static void kill_entity(char *name)
{
    for (nodes_t *tmp = get_game()->entities_list; tmp; tmp = tmp->next) {
        if (strcmp(((entity_t *)tmp->data)->id, name) == 0) {
            previous_to_next(&get_game()->entities_list, tmp);
            break;
        }
    }
}

void display_bonus(void)
{
    static sfSprite *sprite = NULL;

    if (sprite == NULL) {
        sprite = sfSprite_create();
        sfSprite_setTexture(sprite, get_game()->main_texture, sfTrue);
        sfSprite_setScale(sprite, (sfVector2f){5, 5});
        sfSprite_setOrigin(sprite, (sfVector2f){16, 16});
    }
    if (display_char(&sprite,
        (sfIntRect){1922, 2559, 32, 32}, V2F {1300, 200})
        || display_char(&sprite,
        (sfIntRect){1922, 2847, 32, 32}, V2F {1300, 500})
        || display_char(&sprite,
        (sfIntRect){1922, 3135, 32, 32}, V2F {1300, 800})) {
        get_game()->player = init_player(&sprite);
        get_game()->cur_state = MAIN;
        kill_entity("sage");
        loading_function(&create_new_map);
        play_music(MUSIC_GAME);
    }
}
