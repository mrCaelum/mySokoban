/*
** EPITECH PROJECT, 2018
** PSU_my_sokoban_2018
** File description:
** Function to get sokoban map
*/

#include "my_sokoban.h"

static int is_valid_char(char c)
{
    if (c == ' ' || c == '#' || c == '\n' || c == 'P' || c == 'X' || c == 'O')
        return (1);
    return (0);
}

static int fill_map(map_t *map, char const *buffer, unsigned int const filesize)
{
    map->map = malloc(sizeof(char *) * map->height);
    for (unsigned int y = 0; y < map->height; y++)
        map->map[y] = malloc(sizeof(char) * map->width);
    map->boxes = malloc(sizeof(element_t) * map->boxes_number);
    for (unsigned int i = 0, y = 0, x = 0; i < filesize; i++, x++) {
        if (x >= map->width) {
            y++;
            x = -1;
        } else if (buffer[i] == '\n') {
            i--;
            map->map[y][x] = ' ';
        } else
            map->map[y][x] = buffer[i];
    }
    return (0);
}

int get_map(map_t *map, char const *pathname, unsigned int const filesize)
{
    char buffer[filesize];
    int fd = open(pathname, O_RDONLY);

    if(!fd || read(fd, buffer, filesize) != filesize)
        return (1);
    close(fd);
    for (unsigned int i = 0, tmp_width = 0; i < filesize; i++, tmp_width++) {
        if (!is_valid_char(buffer[i]))
            return (1);
        if (buffer[i] == '\n') {
            map->width = tmp_width > map->width ? tmp_width : map->width;
            map->height++;
            tmp_width = -1;
        } else if (buffer[i] == 'X')
            map->boxes_number++;
    }
    return (fill_map(map, buffer, filesize));
}

static int get_box_color(map_t const *map, unsigned int x, unsigned int y)
{
    for (unsigned int i = 0; i < map->boxes_number; i++)
        if (map->boxes[i].pos.x == x && map->boxes[i].pos.y == y)
            return (map->boxes[i].on == 'O' ? 6 : 4);
    return (4);
}

int print_map(map_t const *map)
{
    clear();
    for (unsigned int y = 0; y < map->height; y++) {
        for (unsigned int x = 0; x < map->width; x++) {
            attron(COLOR_PAIR(map->map[y][x] == 'P' ? 2
            : map->map[y][x] == '#' ? 3
            : map->map[y][x] == 'X' ? get_box_color(map, x, y)
            : map->map[y][x] == 'O' ? 5 : 1));
            printw("%s", map->map[y][x] == 'P' ? "**" : "  ");
        }
        attron(COLOR_PAIR(1));
        printw("\n");
    }
    refresh();
    return (0);
}

int free_map(map_t *map)
{
    free(map->boxes);
    for (unsigned int y = 0; y < map->height; y++)
        free(map->map[y]);
    free(map->map);
    return (0);
}
