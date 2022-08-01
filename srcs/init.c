#include "init.h"
#include "shape.h"

void init_gameinfo_struct(t_game_info *gameinfo) {
	gameinfo->score = 0;
	for(int i = 0; i < TABLE_ROW; ++i)
		for(int j = 0; j < TABLE_COL; ++j)
			gameinfo->table_game[i][j] = 0;
	gettimeofday(&gameinfo->before_now, NULL);
	gameinfo->is_continue_game = true;
	gameinfo->current_shape.side_length = 0;
	gameinfo->current_shape.row = 0;
	gameinfo->current_shape.col = 0;
	gameinfo->current_shape.table_shape = NULL;
	replace_shape(gameinfo);
}
