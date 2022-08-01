#ifndef PT_H
# define PT_H

#include "tetris.h"

void copy_shape_on_buffer(t_game_info *gameinfo, char Buffer[TABLE_ROW][TABLE_COL]);
void print_table(t_game_info *gameinfo);

#endif