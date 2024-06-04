/*
** EPITECH PROJECT, 2023
** main
** File description:
** main
*/

#include "csfml.h"

static char **get_allchars(void)
{
    static char *bind[] =
        {"...", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L",
        "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z",
        "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "ESC", "Ctrl-L",
        "Shift-L", "Alt-L", "Win", "Ctrl-R", "Shift-R", "Alt-R", "Win", "Menu",
        "[", "]", ";", ",", ".", "'", "/", "\\", "~", "=", "-", "Space",
        "Enter", "Return", "Tab", "Page Up", "Page Down", "End", "Home",
        "Insert", "Delete", "+ Pad", "- Pad", "* Pad", "/ Pad", "Left Arrow",
        "Right Arrow", "Up Arrow", "Down Arrow", "0 Pad", "1 Pad", "2 Pad",
        "3 Pad", "4 Pad", "5 Pad", "6 Pad", "7 Pad", "8 Pad", "9 Pad", "F1",
        "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", "F11", "F12",
        "F13", "F14", "F15", "Pause", NULL};

    return bind;
}

static void display_grid(void)
{
    static sfRectangleShape *grid = NULL;

    if (!grid)
        grid = create_rectangle(7, V2F {CASE_SIZE, CASE_SIZE},
            V2F {CASE_SIZE / 2, CASE_SIZE / 2},
            V2F {0, 0}, V2F {1, 1}, sfTransparent, sfGreen, -1);
    for (int x = 0; x < get_game()->map_infos->size - 2; x++)
        for (int y = 0; y < get_game()->map_infos->size - 1; y++) {
            sfRectangleShape_setPosition(grid,
                (sfVector2f){x * CASE_SIZE, y * CASE_SIZE});
            sfRenderWindow_drawRectangleShape(
                get_window()->window, grid, NULL);
        }
}

static void bubble_sort_help(nodes_t *act, nodes_t *temp)
{
    if (((entity_t *)(act->data))->position.y
    + ABS(((entity_t *)(act->data))->rect.height / 2
    * ((entity_t *)(act->data))->scale.y)
    > ((entity_t *)(act->next->data))->position.y
    + ABS(((entity_t *)(act->data))->rect.height / 2
    * ((entity_t *)(act->data))->scale.y)) {
        temp = act->data;
        act->data = act->next->data;
        act->next->data = temp;
    }
}

static void bubble_sort(nodes_t *head)
{
    nodes_t *act = head;
    nodes_t *end = NULL;
    nodes_t *temp = NULL;

    if (head == NULL)
        return;
    do {
        temp = NULL;
        act = head;
        while (act->next != end) {
            bubble_sort_help(act, temp);
            act = act->next;
        }
        end = act;
    } while (temp);
}

static void display_hitbox(void)
{
    entity_t *entity = NULL;

    if (!get_user()->show_hitbox)
        return;
    for (nodes_t *tmp = get_game()->entities_list; tmp; tmp = tmp->next) {
        entity = tmp->data;
        if (!entity->hitbox)
            continue;
        if (entity->type != ITEM)
            sfRectangleShape_setPosition(entity->hitbox, entity->position);
        sfRenderWindow_drawRectangleShape(get_window()->window,
        entity->hitbox, NULL);
    }
    sfRenderWindow_drawRectangleShape(get_window()->window,
    get_player_entity()->hitbox, NULL);
    display_grid();
}

static void display_bind_inv(void)
{
    sfVector2f old_pos = sfText_getPosition(get_game()->text_chatbox);
    sfVector2f pos[] = {{1920 / 2 - 440, 1080 - 100},
                        {1920 / 2 - 140, 1080 - 100},
                        {1920 / 2 + 160, 1080 - 100}};
    unsigned char bind[] = {get_bind()->inv1, get_bind()->inv2,
                            get_bind()->inv3};

    for (int i = 0; i < 3; i++) {
        sfText_setPosition(get_game()->text_chatbox, pos[i]);
        sfText_setCharacterSize(get_game()->text_chatbox, 20);
        sfText_setColor(get_game()->text_chatbox, sfWhite);
        sfText_setString(get_game()->text_chatbox, get_allchars()[bind[i]]);
        sfRenderWindow_drawText(get_window()->window,
        get_game()->text_chatbox, NULL);
    }
    sfText_setPosition(get_game()->text_chatbox, old_pos);
}

void display_suite(void)
{
    sfView_setCenter(get_window()->view, (sfVector2f){960, 540});
    sfRenderWindow_setView(get_window()->window, get_window()->view);
    display_hud();
    if (get_user()->show_equipments)
        display_equipments();
    display_levelbar(get_player());
    display_bind_inv();
}

void display_main(void)
{
    char player = 0;

    draw_map();
    bubble_sort(get_game()->entities_list);
    sfView_setCenter(get_window()->view, get_player_entity()->position);
    sfRenderWindow_setView(get_window()->window, get_window()->view);
    for (nodes_t *tmp = get_game()->entities_list;; tmp = tmp->next) {
        if (!player && (tmp == NULL || get_player_entity()->position.y
        < ((entity_t *)(tmp->data))->position.y)) {
            display_player();
            player = 1;
        }
        if (tmp == NULL)
            break;
        display_entity((entity_t *)(tmp->data));
    }
    display_hitbox();
    display_suite();
}
