#ifndef SCREEN_UPDATE_H
# define SCREEN_UPDATE_H

#include "tetris.h"

int has_to_update(const suseconds_t *timer, const t_game_info *gameinfo);
void update_screen(t_game_info *gameinfo, suseconds_t *timer, int *decrease);

#endif