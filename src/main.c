/*
** EPITECH PROJECT, 2018
** PSU_my_sokoban_2018
** File description:
** main
*/

#include "my_sokoban.h"

static int str_lenth(char const *str)
{
    int counter = 0;

    for (; str[counter]; counter++);
    return (counter);
}

void init_colors(void)
{
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_MAGENTA, COLOR_YELLOW);
    init_pair(3, COLOR_RED, COLOR_RED);
    init_pair(4, COLOR_BLUE, COLOR_BLUE);
    init_pair(5, COLOR_CYAN, COLOR_CYAN);
    init_pair(6, COLOR_BLUE, COLOR_GREEN);
}

void close_game(void)
{
    endwin();
    system("stty -raw && stty echo && stty onlcr");
}

int main(int argc, char const **argv)
{
    struct stat file;
    map_t map = (map_t){NULL, 0, 0, 0, NULL};
    element_t player = (element_t){'P', ' ', {0, 0}};

    if (argc == 2 && argv[1][0] == '-' && ((argv[1][1] == 'h' && !argv[1][2])
    || (argv[1][1] == '-' && argv[1][2] == 'h' && argv[1][3] == 'e' &&
    argv[1][4] == 'l' && argv[1][5] == 'p' && !argv[1][6]))) {
        write(1, HELP, str_lenth(HELP));
        return (0);
    }
    initscr();
    if (stat(argv[1], &file) < 0 || file.st_size < 10 || argc != 2)
        return (84);
    if (get_map(&map, argv[1], file.st_size))
        return (84);
    if (game_loop(&map, &player))
        return (close_game(), 84);
    free_map(&map);
    close_game();
    return (0);
}
