/*
** EPITECH PROJECT, 2024
** B-MUL-200-NCE-2-1-myrpg-gianni.tuero
** File description:
** The check_file.c
*/
/**
 * @file check_file.c
 * @brief The check_file.c
 * @author Nicolas TORO
 */

#include "csfml.h"

int save_found(void)
{
    const char *files[] = {"save/player", "save/map", "save/entities"};
    struct stat folder;
    struct stat file;

    if (stat("save", &folder) != 0 || !S_ISDIR(folder.st_mode))
        return 0;
    for (int i = 0; i < 3; i++) {
        if (stat(files[i], &file) != 0 || !S_ISREG(file.st_mode)) {
            return 0;
        }
    }
    return 1;
}

char *get_file(char *file)
{
    int fd = 0;
    struct stat file_info;
    char *content = NULL;

    fd = open(file, O_RDONLY);
    if (fd == -1 || stat(file, &file_info) == -1)
        return NULL;
    content = MALLOC(sizeof(char) * (file_info.st_size + 1));
    if (read(fd, content, file_info.st_size) <= 0)
        return NULL;
    content[file_info.st_size] = '\0';
    close(fd);
    return content;
}
