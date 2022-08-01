#ifndef CS_H
# define CS_H

#include "tetris.h"

t_shape create_random_shape();
t_shape duplicate_shape(t_shape shape);
void replace_shape(t_game_info *gameinfo);

#endif