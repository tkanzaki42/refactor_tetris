#include "screen_print.h"
#include "shape_move_copy.h"

#define TITLE_OFFSET TABLE_COL - 9

void print_table(const t_game_info *gameinfo) {
	char table_shape[TABLE_ROW][TABLE_COL] = {0};

	copy_shape_to_table(&gameinfo->current_shape, table_shape);
	clear();
	for (int i = 0; i < TITLE_OFFSET; ++i)
		printw(" ");
	printw("42 Tetris\n");
	for (int i = 0; i < TABLE_ROW; ++i) {
		for (int j = 0; j < TABLE_COL; ++j) {
			printw("%c ", (gameinfo->table_game[i][j] + table_shape[i][j]) ? '#' : '.');
		}
		printw("\n");
	}
	printw("\nScore: %d\n", gameinfo->score);
}

void print_gameend_screen(const t_game_info *gameinfo) {
	for(int i = 0; i < TABLE_ROW; ++i) {
		for(int j = 0; j < TABLE_COL; ++j) {
			printf("%c ", gameinfo->table_game[i][j] ? '#' : '.');
		}
		printf("\n");
	}
	printf("\nGame over!\n");
	printf("\nScore: %d\n", gameinfo->score);
}
