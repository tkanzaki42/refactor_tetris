#include "game_init.h"
#include "shape_create_delete.h"

void init_gameinfo_struct(t_game_info *gameinfo) {
	for(int i = 0; i < TABLE_ROW; ++i)
		for(int j = 0; j < TABLE_COL; ++j)
			gameinfo->table_game[i][j] = 0;
	gameinfo->score = 0;
	gameinfo->is_continue_game = true;
	gettimeofday(&gameinfo->last_update_time, NULL);
	gameinfo->current_shape.table_shape = NULL;
	gameinfo->current_shape.side_length = 0;
	gameinfo->current_shape.row = 0;
	gameinfo->current_shape.col = 0;
	replace_shape(gameinfo);
}
