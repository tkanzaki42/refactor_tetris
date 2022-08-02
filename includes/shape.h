#ifndef SHAPE_H
# define SHAPE_H

#include "tetris.h"

t_shape duplicate_shape(t_shape shape);
void replace_shape(t_game_info *gameinfo);
void delete_shape(t_shape shape);
void rotate_shape(t_shape shape);
bool check_puttable_shape(t_shape shape, const char Table[TABLE_ROW][TABLE_COL]);
void copy_shape_on_buffer(t_game_info *gameinfo, char Buffer[TABLE_ROW][TABLE_COL]);
void move_shape_down(t_game_info *gameinfo, suseconds_t *timer, int *decrease, bool add_bonus);

#endif