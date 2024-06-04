/*
** EPITECH PROJECT, 2023
** Libmy
** File description:
** Store libmy functions prototypes
*/


#ifndef CSFML_H
    #define CSFML_H

    #include <SFML/Graphics.h>
    #include <SFML/System.h>
    #include <SFML/Audio.h>
    #include <stdbool.h>
    #include <malloc.h>
    #include <stdlib.h>
    #include <time.h>
    #include <threads.h>
    #include <unistd.h>
    #include <fcntl.h>
    #include <math.h>
    #include <string.h>
    #include "mylist.h"
    #include "my.h"
    #include <stdarg.h>
    #include <errno.h>
    #include <string.h>

    #define V2F (sfVector2f)
    #define TIME(x) sfClock_getElapsedTime(x).microseconds / 1000000.0
    #define CLOCKMICRO(clock) sfTime_asMilliseconds(sfClock_restart(clock))

    #define BAR_SIZEW PLAYER_DIMO.x
    #define BAR_SIZEH 10
    #define XP_GIVEN 13
    #define XP_RATIO 1.3

    #define MAX(a, b) ((a > b) ? a : b)
    #define MIN(a, b) ((a < b) ? a : b)
    #define TEXTURE "assets/map.png"

    #define EMPTY '0'
    #define WALL '1'
    #define MAP_SCALE 4

    #define FONT "assets/mc.otf"

    #define GREEN sfColor_fromRGB(15, 169, 88)
    #define RED sfColor_fromRGB(139, 0, 0)
    #define BLUE sfColor_fromRGB(30, 144, 255)

    #define LEFTM (get_keys()->keys[0])
    #define LEFTK (get_keys()->keys[get_bind()->left])
    #define RIGHTK (get_keys()->keys[get_bind()->right])
    #define UPK (get_keys()->keys[get_bind()->up])
    #define DOWNK (get_keys()->keys[get_bind()->down])
    #define ATTACKK (get_keys()->keys[get_bind()->attack])
    #define SLOT1K (get_keys()->keys[get_bind()->inv1])
    #define SLOT2K (get_keys()->keys[get_bind()->inv2])
    #define SLOT3K (get_keys()->keys[get_bind()->inv3])
    #define HITBOXK (get_keys()->keys[get_bind()->hitbox])
    #define XPK (get_keys()->keys[get_bind()->xp])
    #define ESCAPEK (get_keys()->keys[37])
    #define PAUSEK (get_keys()->keys[get_bind()->pause])
    #define HITK (get_keys()->keys[get_bind()->hit])
    #define HEALK (get_keys()->keys[get_bind()->heal])
    #define PASSKEYK (get_keys()->keys[get_bind()->pass])
    #define INTERACTK (get_keys()->keys[get_bind()->interact])
    #define INVENTORYK (get_keys()->keys[get_bind()->inv])

    #define RANDINT(min, max) (rand() % (max - min + 1) + min)
    #define MIN_INT -2147483648
    #define MAX_INT 2147483647
    #define CASE_SIZE (32 * MAP_SCALE)
    //#define SKIP(x) if (x) continue

    #define MUSIC_INTRO "assets/intro.ogg"
    #define MUSIC_MENU "assets/menu.ogg"
    #define MUSIC_GAME "assets/game.ogg"

    #define SOUND_DAMAGE "assets/hurt.ogg"
    #define SOUND_HEAL "assets/heal.ogg"
    #define SOUND_LEVELUP "assets/levelup.ogg"
    #define SOUND_LOOT "assets/loot.ogg"

    #define SOUND_DEAD_GLADIATOR "assets/dead_gladiator.ogg"
    #define SOUND_DEAD_MIMIC "assets/dead_mimic.ogg"
    #define SOUND_DEAD_MONSTER "assets/dead_monster.ogg"
    #define SOUND_HIT_GLADIATOR "assets/hit_gladiator.ogg"
    #define SOUND_HIT_MIMIC "assets/hit_mimic.ogg"
    #define SOUND_HIT_MONSTER "assets/hit_monster.ogg"
    #define SOUND_IDLE_MONSTER "assets/idle_monster.ogg"


typedef enum {
    LEFT_M,
    TOP_M,
    RIGHT_M,
    DOWN_M
} collision_e_t;

typedef enum {
    DUNGEON,
    MAP
} map_type_e_t;

typedef enum {
    INTRO,
    MENU,
    MAIN,
    PAUSE,
    SETTINGS,
    BIND,
    EXIT,
} scene_e_t;

typedef enum {
    RELEASE,
    PRESSED,
    DISABLED,
} button_e_t;

typedef enum {
    PLAYER,
    MOB,
    NPC,
    OBJECT,
    DECOR,
    ITEM,
    CUSTOM,
} entity_type_e_t;

typedef enum {
    NONE,
    LEFT,
    RIGHT,
    ATK,
} player_orientation_e_t;

typedef enum {
    STAND,
    MOVE,
    ATTACK,
    DEAD,
    DISAPPEAR,
} orientation_e_t;

typedef enum {
    GLADIATOR,
    GHOUL,
    JAR_MIMIC,
    DEMON,
    CHEST_MIMIC,
    BARREL_MIMIC
} mob_e_t;

typedef enum {
    ATK_UP,
    DEF_UP,
    HP_UP,
    SPD_UP,
    NOTHING,
    SOMETHING,
} action_player_e_t;

typedef struct {
    unsigned char *binding;
    unsigned char left;
    unsigned char right;
    unsigned char up;
    unsigned char down;
    unsigned char attack;
    unsigned char pause;
    unsigned char interact;
    unsigned char inv1;
    unsigned char inv2;
    unsigned char inv3;
    unsigned char inv;
    unsigned char hitbox;
    unsigned char hit;
    unsigned char heal;
    unsigned char pass;
    unsigned char xp;
} bind_t;

typedef struct {
    unsigned char keys[102];
} keys_t;

typedef struct path_s {
    sfVector2f position;
    float g_score; // Coût depuis le noeuds de départ jusqu'à ce node
    float f_score; // Coût total estimé depuis le départ
    // jusqu'à l'arrivée en passant par ce node
    float h_score; // Distance euclidienne entre le noeud et la fin
    struct path_s *prev; // Noeud précédent dans le chemin optimal
} path_t;

typedef struct path_info_s {
    sfVector2f start;
    sfVector2f end;
    int start_val;
    int nb_paths;
    nodes_t *possible_paths;
    path_t *tmp;
    nodes_t *visited;
} path_info_t;


typedef struct {
    int current;
    orientation_e_t orientation;
    sfClock *animation_clock;
    int max_stand;
    int max_move;
    int max_attack;
    int max_dead;
    int hit_frame;
} animation_t;

typedef struct mob_s {
    sfText *text;
    float hp;
    int attack;
    int defense;
    int xp_to_drop;
    int is_hit;
    int speed;
    int range;
    float resistance;
    animation_t animation;
    float sound_clock;
    char *idle_sound;
    char *hit_sound;
    char *dead_sound;
} mob_t;

typedef struct {
    sfSprite *sprite;
    sfVector2f origin;
    sfVector2f position;
    sfVector2f scale;
    sfVector2f move;
    sfIntRect rect;
    sfIntRect initial_rect;
    float clock;
    float hit_clock;
    sfMusic *sound;
    void *hitbox;

    entity_type_e_t type;
    void *entity_struct;
    char *id;
    int *offset_rect;
} entity_t;

typedef struct item_s {
    bool on_ground;
    bool current;

    float attack;
    float defense;
    float speed;
    float hp;

    int index;
    int (*interaction)(entity_t *);
} item_t;

typedef struct object_s {
    int (*interaction)(entity_t *);
} object_t;

typedef struct npc_s {
    int is_interacting;
    int (*action_npc)(entity_t *);
} npc_t;

typedef struct map_s {
    int type;
    int mob;
    int size;
    int floor;
    char **map;
    sfSprite *tile;
    sfImage *color_map;
} map_t;


typedef struct player_s {
    float hp;
    float max_hp;
    float max_hpw;
    int is_dead;

    float attack;
    float max_attackw;

    int is_attacking;
    int is_hit;

    float defense;
    float max_defensew;

    float speed;
    float max_speedw;

    int xp_to_next_level;
    int xp;
    int level;
    int old_level;

    int loot;
    int (*action)(action_player_e_t action);
    player_orientation_e_t orientation;
    float heal_clock;

    entity_t **items;
    int cur_item;
} player_t;

typedef struct rect_s {
    sfVector2f *origin;
    sfVector2f *scale;
    sfColor *fill_color;
    sfColor *outline_color;
    float outline_thickness;
    sfVector2f *size;
    float rotation;
} rect_t;

typedef struct {
    sfVideoMode video_mode;
    sfRenderWindow *window;
    sfView *view;
    sfSprite *sprite;
    sfTexture *texture;
    sfVector2i mouse_pos;
    sfVector2i old_mouse_pos;
    sfClock *clock;
    sfEvent event;
    sfMusic *music;
    sfMusic *fx;
    sfText *text;

    int vol_music;
    int vol_fx;
    int size;
    float delay;
    int framerate;
    sfVector2i position;
} window_info_t;

typedef struct variables {
    int standby;
    int show_hitbox;
    int show_equipments;
} user_variables_t;

typedef struct button {
    int id;
    char *text;
    int state;
    sfVector2f pos;
    sfVector2f scale;
    void (*function)(void);
} button_t;

typedef struct thread_info {
    char active;
    thrd_t thread;
} thread_info_t;

typedef struct {
    window_info_t *window_i;
    user_variables_t *user_variables;
    sfTexture *main_texture;

    int old_state;
    int cur_state;

    map_t *map_infos;
    nodes_t *entities_list;
    entity_t *player;
    sfText *text_chatbox;
} game_info_t;


//// GET PTR if ()
game_info_t *get_game(void);
entity_t *get_player_entity(void);
window_info_t *get_window(void);
thread_info_t *get_thread(void);
user_variables_t *get_user(void);
player_t *get_player(void);
entity_t *get_entity(char *id);
sfIntRect get_stat_rect(char *stat);
keys_t *get_keys(void);
bind_t *get_bind(void);
sfFont *get_font(void);
button_t **get_buttons_menu(void);
button_t **get_buttons_settings(void);
button_t **get_buttons_pause(void);
button_t **get_buttons_bind(void);
entity_t *get_new_item(sfVector2f pos, int id);
void init_bg2(void);

    #define RANDOM_ITEM(pos) get_new_item(pos, rand() % 12)

int normalize_vector(sfVector2f *vector);
///////////////////////////////////

///////////
void text_center(sfText **text, sfVector2f pos, sfIntRect rect);
void move_rect(entity_t *entity,
    int *offX_maX_miX_offY_maX_miY, ...);
void letter_by_letter(float *clock, char **str, int *j);
////////////////////////////////////////////////////////////////
//////ACTION

//ENTITY OBJECT
int interact(entity_t *);
int stat_object(entity_t *);

//NPC
int quest(entity_t *self);
int troll(entity_t *self);
int speak(entity_t *self);
int thief_npc(entity_t *self);
int mob_npc_one(entity_t *self);
int mob_npc_two(entity_t *self);
int you_are_dead(entity_t *self);
int drop_itemnpc(entity_t *self);
int end_npc(entity_t *self);
int remove_me(entity_t *self);
int display_chatnpc(char **dialog, sfVector2f pos, int reset);

////////////////////////////////////////////////////////////////

//// LOADING SCREEN
void splash_function(void (*func)(void));
void loading_function(void (*func)(void));
/////////////////////////////////////////////////////////////

//// DISPLAY
void display_menu(void);
void display_main(void);
void display_pause(void);
void display_settings(void);
void display_bind(void);
void display_exit(void);
void display_npc(entity_t *entity);
void display_equipments(void);
void display_globalstat(void);

void draw_map(void);
void create_new_map(void);
char **generate_whole_map(int width, int height);

void display_entity(entity_t *entity);
void display_stat(entity_t *entity);
void display_hud(void);
////////////////////////////////////////////////////////////

//////////////UPDATE
void update_menu(void);
void update_main(void);
void update_pause(void);
void update_settings(void);
void update_bind(void);
void update_hud(void);
void update_player2(void);
////////////////////////////////////////////////////////////

/////////////////////// INTRO
int *get_offset_rect(char *id);
void display_intro(void);
void update_intro(void);
void init_sage(void);
void init_bg(void);
int display_talk(char reset);
void display_bonus(void);
////////////////////////////////////////////////////////////

//////////////////PLAYER
sfVector2f player_pos(void);
sfVector2f player_dim(void);
sfVector2f player_dimo(void);
    #define PLAYER_POS player_pos()
    #define PLAYER_DIM player_dim()
    #define PLAYER_DIMO player_dimo()

void choose_offset(char *action, int *offset_rect, sfIntRect rect);
void display_player(void);
void display_levelbar(player_t *player);
void display_level_up(char *id, action_player_e_t action,
    float value, int other);
void display_hit_on_mob(void);
void display_player_stat(entity_t *player_e);
void update_player(void);
void stat_up(char *id, action_player_e_t stat, int other);
entity_t *init_player(sfSprite **sprite);

//// ACTIONS
int action_player(action_player_e_t action);
void atk_up(sfText *text, float value);
void def_up(sfText *text, float value);
void hp_up(sfText *text, float value);
void attack_mob(void);

//// ITEMS
void update_item(void);
void display_item(entity_t *);
void events_item(sfEvent event);
entity_t *current_weapon(void);

////// NPC
entity_t *random_npc(sfVector2f pos);


/////////////////////////////////////////////////////////

/////////////////////BUTTON FUNCTION
void event_button(button_t **buttons);
void display_button(button_t **buttons);

void menu_play(void);
void menu_resume(void);
void menu_settings(void);
void menu_quit(void);

void settings_quit(void);

void pause_resume(void);
void pause_bind(void);
void pause_settings(void);
void pause_menu(void);

void bind_quit(void);
void bind_left(void);
void bind_right(void);
void bind_up(void);
void bind_down(void);
void bind_attack(void);
void bind_pause(void);
void bind_interact(void);
void bind_slot1(void);
void bind_slot2(void);
void bind_slot3(void);
void bind_inv(void);
/////////////////////////////////////////////////////////

/////////////////////EVENTS
void analyse_events(void);

void events_intro(sfEvent event);
void events_main(sfEvent event);
void events_player(sfEvent event);
void events_menu(sfEvent event);
void events_pause(sfEvent event);
void events_settings(sfEvent event);
void events_bind(sfEvent event);
void events_exit(sfEvent event);
////////////////////////////////////////////////////////////

////////////////// INIT
void init_gladiator(sfVector2f pos);
void init_chest_mimic(sfVector2f pos);
void init_jar_mimic(sfVector2f pos);
void init_barrel_mimic(sfVector2f pos);
void init_demon(sfVector2f pos);
void init_ghoul(sfVector2f pos);

void init_game(void);
void init_game_help(void);


//////////////// ENTITIES
void update_entity(entity_t *entity);
void update_mob_animation(entity_t *entity);
int is_hitbox_intersecting(sfRectangleShape *hitbox1,
    sfRectangleShape *hitbox2);
void check_mob_action(void);
float calculate_damage(float attack, float defense);
void check_mob_alive(void);
void knockback(entity_t *entity, entity_t *knockbacked_entity,
    float resitance);
int is_invalid_case(sfVector2f map_case);
void knockback_mob(entity_t *mob);

///////////////// PATHFINDING
float distance_heuristic(sfVector2f a, sfVector2f b);
int vector_cmp(sfVector2f a, sfVector2f b);
sfVector2f vector_add(sfVector2f a, sfVector2f b);
path_t *get_best_path(sfVector2f start, sfVector2f end);
void display_path(path_t *path);
nodes_t *get_visited_list(nodes_t *visited);
sfVector2f pos_to_case(sfVector2f vector);
sfVector2f move_to_next_point(sfVector2f start, sfVector2f end,
    int speed, entity_t *entity);
void check_collision(entity_t *entity1, entity_t *entity2);
int a_ov(int side, float speed, entity_t *player);
sfVector2f get_valid_random_pos(void);


////////////////////////MUSIC
void play_music(char *path);
void play_sound(entity_t *entity, char *path);
void update_volume(void);

/////////////////////SAVE
int save_found(void);
char *get_file(char *file);
void save_entities(void);
void save_map(void);
void save_player(void);
void save_game(void);
void load_entities(void);
void load_map(void);
void load_player(void);
void load_save(void);

/**
 * @brief Create a button object
 * @param text Text on the button
 * @param rect Struct that contain the center-pos of the button and his scale
 * @param function The function call when the button is pressed
 * @return <b>button_t *</b>
*/
button_t *create_button(char *text, sfFloatRect rect, void (*function)(void));


/**
 * @brief Create a text object
 * @param nb Number of arguments
 * @param  ... Arguments : <br>
 * 1st <b>char *</b> : String <br>
 * 2nd <b>sfFont *</b> : Font <br>
 * 3rd <b>int</b> : CharacterSize <br>
 * 4th <b>sfColor</b> : Color <br>
 * 5th <b>sfVector2f</b> : Position <br>
 * 6th <b>sfVector2f</b> : Scale <br>
 * @return <b>sfText*</b>
*/
sfText *create_text(int nb, ...);


/**
 * @brief Create a sprite object
 *
 * @param nb
 * @param sfTexture texture
 * @param sfIntRect texture rect
 * @param sfVector2f position
 * @param sfVector2f origin
 * @param sfVector2f scale
 * @return sfSprite*
 */
sfSprite *create_sprite(int nb, ...);


/**
 * @brief Create a rectangle object
 *
 * @param nb
 * @param ... Arguments : <br>
 * 1st <b>sfVector2f</b> : Size <br>
 * 2nd <b>sfVector2f</b> : Position <br>
 * 3rd <b>sfVector2f</b> : Origin <br>
 * 4th <b>sfVector2f</b> : Scale <br>
 * 5th <b>sfColor</b> : FillColor <br>
 * 6th <b>sfColor</b> : OutlineColor <br>
 * 7th <b>float</b> : OutlineThickness <br>
 * @return sfRectangleShape*
 */
sfRectangleShape *create_rectangle(int nb, ...);


/**
 * @brief Create an entity object
 *
 * @param nb
 * @param ... <br>
 * 1st : <b>entity_type_e</b> : entity_type <br>
 * 2nd : <b>char *</b> : id <br>
 * 3rd : <b>sfSprite *</b> : sprite <br>
 * 4th : <b>void *</b> : entity_struct / action for entity <br>
 * 5th : <b>void *</b> : hitbox <br>
 * @return <b>entity_t*<b>
 */
entity_t *create_entity(int nb, ...);
void update_entity(entity_t *entity);

////////////////////////////////////////////////////////////

//MAP
char **generate_whole_map(int width, int height);
void place_mobs_map(void);
void remove_mobs_fl(void);
void restart_game(void);
void move_end_ladder(void);
void place_npc_map(void);

////////////////// EVENTS
void analyse_events(void);

#endif //CSFML_H
