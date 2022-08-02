#ifndef UPDATE_H
# define UPDATE_H

#include "tetris.h"

void update_key_input(
		int key_input, t_game_info *gameinfo, suseconds_t *timer, int *decrease);
void update_screen(t_game_info *gameinfo, suseconds_t *timer, int *decrease);

#endif