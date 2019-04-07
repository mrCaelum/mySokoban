/*
** EPITECH PROJECT, 2018
** PSU_my_sokoban_2018
** File description:
** Player movement functions
*/

#include "my_sokoban.h"

static int edit_box(map_t *map, position_t box, position_t to)
{
    int box_nb = NOBOXES;

    for (unsigned int i = 0; i < map->boxes_number; i++)
        if (map->boxes[i].pos.x == box.x && map->boxes[i].pos.y == box.y)
            box_nb = i;
    if (box_nb == NOBOXES)
        return (1);
    map->map[box.y][box.x] = map->boxes[box_nb].on;
    map->boxes[box_nb].on = map->map[to.y][to.x];
    map->map[to.y][to.x] = map->boxes[box_nb].c;
    map->boxes[box_nb].pos.x = to.x;
    map->boxes[box_nb].pos.y = to.y;
    if (map->boxes[box_nb].on != 'O'
    && ((map->map[to.y + 1][to.x] == '#' && map->map[to.y][to.x + 1] == '#')
    || (map->map[to.y + 1][to.x] == '#' && map->map[to.y][to.x - 1] == '#')
    || (map->map[to.y - 1][to.x] == '#' && map->map[to.y][to.x + 1] == '#')
    || (map->map[to.y - 1][to.x] == '#' && map->map[to.y][to.x - 1] == '#')))
        exit(1);
    return (0);
}

void player_move_left(map_t *map, element_t *player)
{
    if (map->map[player->pos.y][player->pos.x - 1] == 'X' &&
    (map->map[player->pos.y][player->pos.x - 2] == ' ' ||
    map->map[player->pos.y][player->pos.x - 2] == 'O')) {
        edit_box(map, (position_t){player->pos.x - 1, player->pos.y},
        (position_t){player->pos.x - 2, player->pos.y});
    }
    if (map->map[player->pos.y][player->pos.x - 1] == ' ' ||
    map->map[player->pos.y][player->pos.x - 1] == 'O') {
        map->map[player->pos.y][player->pos.x] = player->on;
        player->pos.x--;
        player->on = map->map[player->pos.y][player->pos.x];
        map->map[player->pos.y][player->pos.x] = player->c;
    }
}

void player_move_right(map_t *map, element_t *player)
{
    if (map->map[player->pos.y][player->pos.x + 1] == 'X' &&
    (map->map[player->pos.y][player->pos.x + 2] == ' ' ||
    map->map[player->pos.y][player->pos.x + 2] == 'O')) {
        edit_box(map, (position_t){player->pos.x + 1, player->pos.y},
        (position_t){player->pos.x + 2, player->pos.y});
    }
    if (map->map[player->pos.y][player->pos.x + 1] == ' ' ||
    map->map[player->pos.y][player->pos.x + 1] == 'O') {
        map->map[player->pos.y][player->pos.x] = player->on;
        player->pos.x++;
        player->on = map->map[player->pos.y][player->pos.x];
        map->map[player->pos.y][player->pos.x] = player->c;
    }
}

void player_move_up(map_t *map, element_t *player)
{
    if (map->map[player->pos.y - 1][player->pos.x] == 'X' &&
    (map->map[player->pos.y - 2][player->pos.x] == ' ' ||
    map->map[player->pos.y - 2][player->pos.x] == 'O')) {
        edit_box(map, (position_t){player->pos.x, player->pos.y - 1},
        (position_t){player->pos.x, player->pos.y - 2});
    }
    if (map->map[player->pos.y - 1][player->pos.x] == ' ' ||
    map->map[player->pos.y - 1][player->pos.x] == 'O') {
        map->map[player->pos.y][player->pos.x] = player->on;
        player->pos.y--;
        player->on = map->map[player->pos.y][player->pos.x];
        map->map[player->pos.y][player->pos.x] = player->c;
    }
}

void player_move_down(map_t *map, element_t *player)
{
    if (map->map[player->pos.y + 1][player->pos.x] == 'X' &&
    (map->map[player->pos.y + 2][player->pos.x] == ' ' ||
    map->map[player->pos.y + 2][player->pos.x] == 'O')) {
        edit_box(map, (position_t){player->pos.x, player->pos.y + 1},
        (position_t){player->pos.x, player->pos.y + 2});
    }
    if (map->map[player->pos.y + 1][player->pos.x] == ' ' ||
    map->map[player->pos.y + 1][player->pos.x] == 'O') {
        map->map[player->pos.y][player->pos.x] = player->on;
        player->pos.y++;
        player->on = map->map[player->pos.y][player->pos.x];
        map->map[player->pos.y][player->pos.x] = player->c;
    }
}
