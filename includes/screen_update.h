#ifndef SCREEN_UPDATE_H
# define SCREEN_UPDATE_H

# include "tetris.h"

bool has_to_update(const t_game_info *gameinfo, const t_time *time);
void update_screen(t_game_info *gameinfo, t_time *time);

#endif
