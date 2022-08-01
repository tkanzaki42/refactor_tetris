#include "pt.h"

void copy_shape_on_table(char Buffer[TABLE_ROW][TABLE_COL]) {
	for(int i = 0; i < current.width; ++i){
		for(int j = 0; j < current.width; ++j){
			if(current.array[i][j])
				Buffer[current.row + i][current.col + j] = current.array[i][j];
		}
	}
}

void print_table(const int final, const char Table[TABLE_ROW][TABLE_COL]){
	char Buffer[TABLE_ROW][TABLE_COL] = {0};

	copy_shape_on_table(Buffer);
	clear();
	for (int i = 0; i < TABLE_COL - 9; ++i)
		printw(" ");
	printw("42 Tetris\n");
	for (int i = 0; i < TABLE_ROW; ++i) {
		for (int j = 0; j < TABLE_COL; ++j){
			printw("%c ", (Table[i][j] + Buffer[i][j])? '#': '.');
		}
		printw("\n");
	}
	printw("\nScore: %d\n", final);
}
