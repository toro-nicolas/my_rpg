/*
** EPITECH PROJECT, 2023
** B-MUL-200-NCE-2-1-myrpg-gianni.tuero
** File description:
** generate_map.c
*/

#include <csfml.h>

static void print_maze(char **maze)
{
    for (int y = 0; maze[y] != NULL; y++) {
        for (int x = 0; maze[y][x] != 0; x++) {
            printf("%c", maze[y][x]);
        }
        printf("\n");
    }
}

static void swap_values(char **map, int i, int j)
{
    if (map[i][j] == '0') {
        map[i][j] = '1';
    } else if (map[i][j] == '1') {
        map[i][j] = '0';
    }
}

static void hardcode_values(char **map)
{
    int size = get_game()->map_infos->size;

    for (int i = 0; i <= 4; i++) {
        for (int j = 0; j <= 4; j++) {
            map[i][j] = WALL;
            map[size - 1 - i][size - 2 - j] = WALL;
        }
    }
}

static void add_links(char **map, int i, int j)
{
    int change = 0;

    if (map[i][j] == WALL)
        return;
    change = rand() % 100;
    map[i][j] = change < 15 ? WALL : EMPTY;
}

static void add_random_links(char **map)
{
    for (int i = 0; map[i] != NULL; i++) {
        for (int j = 0; map[i][j] != 0; j++) {
            add_links(map, i, j);
        }
    }
}

static char **fix_map(char **map)
{
    for (int i = 0; map[i] != NULL; i++) {
        for (int j = 0; map[i][j] != '\0'; j++) {
            swap_values(map, i, j);
        }
    }
    hardcode_values(map);
    add_random_links(map);
    return map;
}

static void search_rand(sfVector2i (*move_dir)[4])
{
    int j;
    sfVector2i temp;

    for (int i = 3; i > 0; i--) {
        j = rand() % (i + 1);
        temp = (*move_dir)[i];
        (*move_dir)[i] = (*move_dir)[j];
        (*move_dir)[j] = temp;
    }
}

static void visit(sfVector2i ind, char **maze, int **visited, int size[2])
{
    sfVector2i move_dir[4] = {{0, -2}, {0, 2}, {-2, 0}, {2, 0}};
    sfVector2i dxy;
    sfVector2i nxy;

    visited[ind.y][ind.x] = 1;
    search_rand(&move_dir);
    for (int i = 0; i < 4; i++) {
        dxy = (sfVector2i) {move_dir[i].x, move_dir[i].y};
        nxy = (sfVector2i) {ind.x + dxy.x, ind.y + dxy.y};
        if (nxy.x > 0 && nxy.x < size[0] && nxy.y > 0 &&
        nxy.y < size[1] && !visited[nxy.y][nxy.x]) {
            maze[nxy.y][nxy.x] = EMPTY;
            maze[ind.y + dxy.y / 2][ind.x + dxy.x / 2] = EMPTY;
            visit((sfVector2i){nxy.x, nxy.y}, maze, visited, size);
        }
    }
}

static void free_visit(int size[2], int **visited)
{
    for (int y = 0; y < size[1]; y++)
        free(visited[y]);
    free(visited);
}

char **generate_whole_map(int width, int height)
{
    char **maze;
    int **visited = NULL;
    int size[2] = {width, height};

    maze = malloc(sizeof(char *) * (size[1] + 1));
    visited = malloc(sizeof(int *) * size[1]);
    for (int y = 0; y < size[1]; y++) {
        maze[y] = malloc(sizeof(char) * (size[0] + 1));
        visited[y] = malloc(sizeof(int) * size[0]);
        for (int x = 0; x < size[0]; x++) {
            maze[y][x] = WALL;
            visited[y][x] = 0;
        }
        maze[y][size[0]] = '\0';
    }
    maze[size[1]] = NULL;
    maze[1][1] = EMPTY;
    visit((sfVector2i){1, 1}, maze, visited, size);
    free_visit(size, visited);
    return fix_map(maze);
}
