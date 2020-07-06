/*
** EPITECH PROJECT, 2018
** PSU_my_sokoban_2018
** File description:
** Game loop
*/

#include "my_sokoban.h"

static const call_function_t functions[] = {
    {KEY_LEFT, &player_move_left},
    {KEY_RIGHT, &player_move_right},
    {KEY_UP, &player_move_up},
    {KEY_DOWN, &player_move_down},
    {0, NULL}
};

static int init_character(map_t *map, position_t here, element_t *player,
int *box)
{
    if (map->map[here.y][here.x] == player->c) {
        player->pos.x = here.x;
        player->pos.y = here.y;
    } else if (map->map[here.y][here.x] == 'X') {
        map->boxes[*box].c = 'X';
        map->boxes[*box].on = ' ';
        map->boxes[*box].pos.x = here.x;
        map->boxes[*box].pos.y = here.y;
        (*box)++;
    }
    return (map->map[here.y][here.x] == player->c ? 1 : 0);
}

static int init_game(map_t *map, element_t *player)
{
    int player_nbr = 0;
    int box = 0;

    for (unsigned int y = 0; y < map->height; y++)
        for (unsigned int x = 0; x < map->width; x++)
            player_nbr += init_character(map, (position_t){x, y}, player,
            &box);
    print_map(map);
    return (player_nbr == 1 ? 0 : 1);
}

static void player_move(map_t *map, element_t *player, int key)
{
    for (unsigned int i = 0; functions[i].key; i++)
        if (key == functions[i].key)
            functions[i].ptr(map, player);
}

static int victory(map_t *map, element_t *player)
{
    if (player->on == 'O')
        return (0);
    for (unsigned int y = 0, x = 0; y < map->height; x++) {
        if (x >= map->width) {
            x = -1;
            y++;
        } else if (map->map[y][x] == 'O')
            return (0);
    }
    return (1);
}

int game_loop(map_t *map, element_t *player)
{
    int key = 0;
    WINDOW *window = newwin(HEIGHT, WIDTH, 12 - HEIGHT / 2, 40 - WIDTH / 2);

    keypad(window, TRUE);
    init_colors();
    if (init_game(map, player))
        return (1);
    while (key != 27) {
        key = wgetch(window);
        player_move(map, player, key);
        if ((unsigned int)COLS < map->height
        || (unsigned int)LINES < map->width) {
            clear();
            attron(COLOR_PAIR(1));
            printw("Invalid terminal size !");
            refresh();
        } else
            print_map(map);
        if (victory(map, player))
            break;
    }
    return (0);
}
