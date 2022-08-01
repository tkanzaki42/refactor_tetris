#include "pt.h"

void copy_shape_on_buffer(t_game_info *gameinfo, char Buffer[TABLE_ROW][TABLE_COL]) {
	for(int i = 0; i < gameinfo->current_shape.position_col; ++i){
		for(int j = 0; j < gameinfo->current_shape.position_col; ++j){
			if(gameinfo->current_shape.table_shape[i][j])
				Buffer[gameinfo->current_shape.row + i][gameinfo->current_shape.col + j]
					= gameinfo->current_shape.table_shape[i][j];
		}
	}
}

void print_table(t_game_info *gameinfo) {
	char Buffer[TABLE_ROW][TABLE_COL] = {0};

	copy_shape_on_buffer(gameinfo, Buffer);
	clear();
	for (int i = 0; i < TABLE_COL - 9; ++i)
		printw(" ");
	printw("42 Tetris\n");
	for (int i = 0; i < TABLE_ROW; ++i) {
		for (int j = 0; j < TABLE_COL; ++j){
			printw("%c ", (gameinfo->table_game[i][j] + Buffer[i][j])? '#': '.');
		}
		printw("\n");
	}
	printw("\nScore: %d\n", gameinfo->score);
}
