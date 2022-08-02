#ifndef GAME_BODY_H
# define GAME_BODY_H

#include "tetris.h"

void prepare_game(t_game_info *gameinfo);
void play_game(t_game_info *gameinfo);
void finalize_game(t_game_info *gameinfo);

#endif