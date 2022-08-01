#ifndef PRINT_H
# define PRINT_H

#include "tetris.h"

void print_gameend_screen(t_game_info *gameinfo);
void print_table(t_game_info *gameinfo);
void print_shape_moved_down(t_game_info *gameinfo, suseconds_t *timer, int *decrease, bool add_bonus);

#endif