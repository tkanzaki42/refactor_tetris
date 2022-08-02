#ifndef SHAPE_H
# define SHAPE_H

#include "tetris.h"

void duplicate_shape(const t_shape *shape, t_shape *dup);
void replace_shape(t_game_info *gameinfo);
void delete_shape(t_shape *shape);
void rotate_shape(t_shape *shape);
bool check_shape_puttable(const t_shape *shape, const char Table[TABLE_ROW][TABLE_COL]);
void copy_shape_to_table(const t_shape *shape, char table[TABLE_ROW][TABLE_COL]);
void move_shape_down(t_game_info *gameinfo, suseconds_t *timer, int *decrease, bool add_bonus);

#endif