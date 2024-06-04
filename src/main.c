/*
** EPITECH PROJECT, 2023
** main
** File description:
** main
*/

#include "csfml.h"

static void set_clock(float delay)
{
    if (get_game()->cur_state == MAIN)
        get_player()->heal_clock += delay;
    for (nodes_t *tmp = get_game()->entities_list; tmp != NULL;
    tmp = tmp->next) {
        ((entity_t *)(tmp->data))->clock += delay;
        ((entity_t *)(tmp->data))->hit_clock += delay;
        if (((entity_t *)(tmp->data))->type == MOB)
            ((mob_t *)((entity_t *)(tmp->data))->entity_struct)->sound_clock
            += delay;
    }
    if (get_game()->cur_state == MAIN) {
        get_player_entity()->clock += delay;
        get_player_entity()->hit_clock += delay;
    }
}

void game_core(void)
{
    window_info_t *window = get_window();
    void (*update_fct[])(void) =
    {&update_intro, &update_menu, &update_main, &update_pause,
    &update_settings, &update_bind, NULL};
    void (*display_fct[])(void) =
    {&display_intro, &display_menu, &display_main, &display_pause,
    &display_settings, &display_bind, NULL};

    while (sfRenderWindow_isOpen(window->window)) {
        window->delay = sfClock_restart(window->clock).microseconds
        / 1000000.0;
        set_clock(window->delay);
        analyse_events();
        if (get_game()->cur_state == EXIT)
            break;
        update_fct[get_game()->cur_state]();
        sfRenderWindow_clear(window->window, sfCyan);
        display_fct[get_game()->cur_state]();
        sfRenderWindow_display(window->window);
    }
}

int main(int ac, char **av)
{
    if (ac == 2 && my_strcmp(av[1], "-h") == 0) {
        my_putstr("USAGE\n\t./my_rpg\n\nDESCRIPTION\n"
            "\tA role-playing game made by "
            "Gianni TUERO, Lou PELLEGRINO, "
            "Nicolas TORO and Raphaël LAUNAY.\n");
        return 84;
    }
    init_game();
    game_core();
    FREE;
    return 0;
}
