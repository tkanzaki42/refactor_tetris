#ifndef SHAPE_CREATE_DELETE_H
# define SHAPE_CREATE_DELETE_H

# include "tetris.h"

void delete_shape(t_shape *shape);
void duplicate_shape(const t_shape *shape, t_shape *dup);
void replace_shape(t_game_info *gameinfo);

#endif