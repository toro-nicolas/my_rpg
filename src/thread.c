/*
** EPITECH PROJECT, 2023
** my_rpg
** File description:
** thread.c
*/

#include "csfml.h"

static void loading_logo(void)
{
    static sfSprite *logo = NULL;
    static sfClock *clock = NULL;
    static int delay = 0;

    if (logo == NULL) {
        logo = sfSprite_create();
        sfSprite_setTexture(logo, get_game()->main_texture, sfFalse);
        sfSprite_setTextureRect(logo, (sfIntRect){680, 2160, 384, 384});
        sfSprite_setPosition(logo, (sfVector2f){1840, 1000});
        sfSprite_setOrigin(logo, (sfVector2f){192, 192});
        sfSprite_setScale(logo, (sfVector2f){0.2, 0.2});
        sfSprite_setColor(logo, (sfColor){109, 71, 100, 255});
    }
    if (clock == NULL)
        clock = sfClock_create();
    for (delay += sfTime_asMilliseconds(sfClock_restart(clock));
    delay > 360 * 4; delay -= 360 * 4);
    for (; delay > 4; delay -= 4)
        sfSprite_rotate(logo, 1.0);
    sfRenderWindow_drawSprite(get_window()->window, logo, NULL);
}

static void loading_screen(void)
{
    static sfClock *time = NULL;

    if (time == NULL)
        time = sfClock_create();
    init_bg();
    while (1) {
        if (get_thread()->active == 0)
            return;
        while (sfRenderWindow_pollEvent(get_window()->window,
        &(get_window()->event)))
            get_game()->cur_state = (get_window()->event.type == sfEvtClosed)
            ? EXIT : get_game()->cur_state;
        move_rect(get_entity("bg"), get_entity("bg")->offset_rect,
        &get_entity("bg")->rect.left, &get_entity("bg")->rect.top, &time, 1.0);
        sfRenderWindow_drawSprite(get_window()->window,
        get_entity("bg")->sprite, NULL);
        loading_logo();
        sfRenderWindow_display(get_window()->window);
    }
}

static void fade_up(sfSprite *bg, sfClock *clock, int delay, int anim)
{
    sfSprite_setPosition(bg, (sfVector2f){0, 0});
    sfSprite_setTexture(bg, get_game()->main_texture, sfFalse);
    sfSprite_setTextureRect(bg, (sfIntRect){6548, 2700, 1920, 1080});
    while (anim < 255) {
        while (sfRenderWindow_pollEvent(get_window()->window,
        &(get_window()->event)))
            get_game()->cur_state = (get_window()->event.type == sfEvtClosed)
            ? EXIT : get_game()->cur_state;
        for (delay += CLOCKMICRO(clock); delay > 50; delay -= 50)
            anim += 5;
        sfRenderWindow_clear(get_window()->window, sfBlack);
        sfSprite_setColor(bg, (sfColor){255, 255, 255, anim});
        sfRenderWindow_drawSprite(get_window()->window, bg, NULL);
        sfRenderWindow_display(get_window()->window);
    }
}

static void set_bounce(sfSprite *boom, int anim)
{
    if (anim < 8) {
        sfSprite_setScale(boom,
        (sfVector2f){0.8 * (8 - anim % 8), 0.8 * (8 - anim % 8)});
        return;
    }
    if (anim < 16) {
        sfSprite_setScale(boom,
        (sfVector2f){0.8 + 0.1 * (anim % 8), 0.8 + 0.1 * (anim % 8)});
        return;
    }
    if (anim < 24) {
        sfSprite_setScale(boom,
        (sfVector2f){0.8 + 0.1 * (8 - anim % 8), 0.8 + 0.1 * (8 - anim % 8)});
        return;
    }
    if (anim < 32) {
        sfSprite_setScale(boom,
        (sfVector2f){0.8 + 0.028 * (anim % 8), 0.8 + 0.028 * (anim % 8)});
        return;
    }
}

static void display_splash(sfSprite *bg, sfSprite *boom, int anim)
{
    set_bounce(boom, anim);
    sfRenderWindow_clear(get_window()->window, sfBlack);
    sfRenderWindow_drawSprite(get_window()->window, bg, NULL);
    sfRenderWindow_drawSprite(get_window()->window, boom, NULL);
    sfRenderWindow_display(get_window()->window);
}

static void splash_screen(void)
{
    sfSprite *bg = sfSprite_create();
    sfSprite *boom = sfSprite_create();
    sfClock *clock = sfClock_create();
    int delay = 0;
    int anim = 0;

    fade_up(bg, clock, delay, anim);
    sfSprite_setTexture(boom, get_game()->main_texture, sfFalse);
    sfSprite_setTextureRect(boom, (sfIntRect){3020, 2560, 846, 362});
    sfSprite_setOrigin(boom, (sfVector2f){423, 181});
    sfSprite_setPosition(boom, (sfVector2f){960, 260});
    while (anim < 48) {
        while (sfRenderWindow_pollEvent(get_window()->window,
        &(get_window()->event)))
            get_game()->cur_state = (get_window()->event.type == sfEvtClosed)
            ? EXIT : get_game()->cur_state;
        for (delay += CLOCKMICRO(clock); delay > 50; delay -= 50)
            anim++;
        display_splash(bg, boom, anim);
    }
}

static int thread_function(void *arg)
{
    void (*func)(void) = arg;

    func();
    get_thread()->active = 0;
    return 0;
}

void loading_function(void (*func)(void))
{
    thread_info_t *tmp = get_thread();

    tmp->active = 1;
    if (thrd_create(&(tmp->thread), &thread_function, (void *)func)
    != thrd_success)
        exit(84);
    loading_screen();
    if (thrd_join(tmp->thread, NULL) != thrd_success)
        exit(84);
}

void splash_function(void (*func)(void))
{
    thread_info_t *tmp = get_thread();

    tmp->active = 1;
    if (thrd_create(&(tmp->thread), &thread_function, (void *)func)
    != thrd_success)
        exit(84);
    splash_screen();
    if (thrd_join(tmp->thread, NULL) != thrd_success)
        exit(84);
}
