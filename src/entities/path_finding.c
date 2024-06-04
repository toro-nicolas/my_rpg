/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** The path_finding.c
*/
/**
 * @file path_finding.c
 * @brief The path_finding.c
 * @author Nicolas TORO
 */

#include "csfml.h"

static int is_already_visited(nodes_t *visited, sfVector2f position)
{
    for (nodes_t *tmp = visited; tmp; tmp = tmp->next) {
        if (vector_cmp(((path_t *)tmp->data)->position, position))
            return 1;
    }
    return 0;
}

static int get_best_neighbor(sfVector2f start, sfVector2f end)
{
    int distance = 1;
    sfVector2f tmp = {0};
    static sfVector2f vector[4] = {{0, -CASE_SIZE}, {0, CASE_SIZE},
        {-CASE_SIZE, 0}, {CASE_SIZE, 0}};

    if (vector_cmp(start, end))
        return 0;
    for (int i = 0; i < 4; i++) {
        tmp = vector_add(start, vector[i]);
        if (vector_cmp(tmp, end))
            return distance;
        distance++;
    }
    return -1;
}

static path_t *create_path(path_info_t *path_info, sfVector2f start)
{
    path_t *new_path = calloc(1, sizeof(path_t));
    int cost = 0;

    new_path->position = start;
    if (path_info->tmp != NULL) {
        new_path->prev = path_info->tmp;
        new_path->h_score = distance_heuristic(start, path_info->end);
        new_path->g_score = (path_info->tmp->g_score + 1) / 10;
        cost = get_best_neighbor(start, path_info->end);
        new_path->f_score = (cost == -1) ?
            new_path->g_score + new_path->h_score : MIN_INT + cost;
    }
    return new_path;
}

static path_t *get_lowest_score_node(nodes_t *possible_paths)
{
    path_t *lowest_node = NULL;

    for (nodes_t *tmp = possible_paths; tmp; tmp = tmp->next) {
        if (tmp->data == NULL)
            continue;
        if (lowest_node == NULL ||
        ((path_t *)tmp->data)->f_score < lowest_node->f_score)
            lowest_node = tmp->data;
    }
    return lowest_node;
}

static void browse_neighbors(path_info_t *path_info)
{
    path_t *new_path;
    static sfVector2f vector[4] = {{0, -CASE_SIZE}, {0, CASE_SIZE},
        {-CASE_SIZE, 0}, {CASE_SIZE, 0}};
    sfVector2f current_vector = {0};

    for (int i = 0; i < 4; i++) {
        current_vector = vector_add(path_info->tmp->position, vector[i]);
        if (is_already_visited(path_info->visited, current_vector) ||
        is_invalid_case(current_vector))
            continue;
        new_path = create_path(path_info, current_vector);
        if (my_find_node(path_info->possible_paths, new_path, NULL) == NULL) {
            path_info->nb_paths++;
            super_push_b(&path_info->possible_paths, new_path, UNKNOW);
        }
    }
}

static path_info_t *create_path_info(sfVector2f start, sfVector2f end)
{
    path_info_t *path_info = calloc(1, sizeof(path_info_t));

    my_memset(path_info, 0, sizeof(path_info_t));
    path_info->start = start;
    path_info->end = end;
    path_info->start_val = 1;
    if ((start.x == 0 && start.y == 0) || (end.x == 0 && end.y == 0))
        return path_info;
    path_info->nb_paths = 1;
    return path_info;
}

nodes_t *get_visited_list(nodes_t *visited)
{
    static nodes_t *visited_list = NULL;

    if (visited != NULL)
        visited_list = visited;
    return visited_list;
}

static path_t *end_path(path_info_t *path_info, path_t *path)
{
    delete_list(&path_info->possible_paths, "nd");
    if (path == NULL) {
        delete_list(&path_info->visited, "nd");
    } else {
        get_visited_list(path_info->visited);
    }
    free(path_info);
    return path;
}

static sfVector2f valid(sfVector2f end)
{
    static sfVector2f vector[4] = {{0, CASE_SIZE}, {0, -CASE_SIZE},
        {CASE_SIZE, 0}, {-CASE_SIZE, 0}};
    sfVector2f tmp = {0};

    if (is_invalid_case(end) == 0)
        return end;
    for (int i = 0; i < 4; i++) {
        tmp = vector_add(end, vector[i]);
        if (is_invalid_case(tmp) == 0)
            return tmp;
    }
    return V2F {0, 0};
}

path_t *get_best_path(sfVector2f start, sfVector2f end)
{
    path_info_t *path_info = create_path_info(valid(start), valid(end));

    super_push_f(&path_info->possible_paths,
        create_path(path_info, path_info->start), UNKNOW);
    while (path_info->nb_paths > 0) {
        path_info->tmp = get_lowest_score_node(path_info->possible_paths);
        super_push_b(&path_info->visited, path_info->tmp, UNKNOW);
        free(previous_to_next(&path_info->possible_paths,
            my_find_node(path_info->possible_paths, path_info->tmp, NULL)));
        if (path_info->start_val == 0 &&
        vector_cmp(path_info->tmp->position, path_info->start))
            return end_path(path_info, NULL);
        path_info->start_val = 0;
        if (vector_cmp(path_info->tmp->position, path_info->end))
            return end_path(path_info, path_info->tmp);
        path_info->nb_paths--;
        browse_neighbors(path_info);
    }
    return end_path(path_info, NULL);
}
