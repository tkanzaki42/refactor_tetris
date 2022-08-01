#include "pt.h"

void copy_shape_on_table(char Buffer[R][C]) {
	for(int i = 0; i < current.width; ++i){
		for(int j = 0; j < current.width; ++j){
			if(current.array[i][j])
				Buffer[current.row + i][current.col + j] = current.array[i][j];
		}
	}
}

void print_table(const int final, const char Table[R][C]){
	char Buffer[R][C] = {0};

	copy_shape_on_table(Buffer);
	clear();
	for(int i=0; i<C-9; i++)
		printw(" ");
	printw("42 Tetris\n");
	for(int i = 0; i < R ;i++){
		for(int j = 0; j < C ; j++){
			printw("%c ", (Table[i][j] + Buffer[i][j])? '#': '.');
		}
		printw("\n");
	}
	printw("\nScore: %d\n", final);
}
