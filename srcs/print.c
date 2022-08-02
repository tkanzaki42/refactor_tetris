#include "print.h"
#include "shape.h"

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

void print_gameend_screen(t_game_info *gameinfo) {
	for(int i = 0; i < TABLE_ROW; ++i){
		for(int j = 0; j < TABLE_COL; ++j){
			printf("%c ", gameinfo->table_game[i][j] ? '#': '.');
		}
		printf("\n");
	}
	printf("\nGame over!\n");
	printf("\nScore: %d\n", gameinfo->score);
}
