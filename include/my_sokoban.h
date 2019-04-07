/*
** EPITECH PROJECT, 2018
** PSU_my_sokoban_2018
** File description:
** Header
*/

#ifndef MY_SOKOBAN_H_
#define MY_SOKOBAN_H_

#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ncurses.h>

#define HEIGHT 10
#define WIDTH 30
#define NOBOXES -1
#define HELP USAGE DESC DESC2 DESC3
#define USAGE "USAGE\n\t./my_sokoban map\n"
#define DESC "DESCRIPTION\n\tmap\tfile representing the warehouse map,"
#define DESC2 " containing '#' for walls,\n\t\t'P' for player, 'X' for boxes"
#define DESC3 " and 'O' for storage locations.\n"

typedef struct position {
    int x;
    int y;
} position_t;

typedef struct element {
    char c;
    char on;
    position_t pos;
} element_t;

typedef struct map {
    char **map;
    unsigned int width;
    unsigned int height;
    unsigned int boxes_number;
    element_t *boxes;
} map_t;

typedef struct call_function {
    int key;
    void (*ptr)(map_t *map, element_t *player);
} call_function_t;

int get_map(map_t *map, char const *pathname, unsigned int const filesize);
int print_map(map_t const *map);
int free_map(map_t *map);

void init_colors(void);

int game_loop(map_t *map, element_t *player);
void close_game(void);

void player_move_left(map_t *map, element_t *player);
void player_move_right(map_t *map, element_t *player);
void player_move_up(map_t *map, element_t *player);
void player_move_down(map_t *map, element_t *player);

#endif
