#ifndef GAME_H
# define GAME_H

#include "tetris.h"

void start_game(t_game_info *gameinfo);
void play_game(t_game_info *gameinfo);
void finalize_game(t_game_info *gameinfo);

#endif