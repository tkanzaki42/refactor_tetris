#ifndef SHAPE_MOVE_COPY_H
# define SHAPE_MOVE_COPY_H

#include "tetris.h"

void rotate_shape(t_shape *shape);
void move_shape_down(t_game_info *gameinfo, suseconds_t *timer, int *decrease, bool add_bonus);
void copy_shape_to_table(const t_shape *shape, char table[TABLE_ROW][TABLE_COL]);

#endif