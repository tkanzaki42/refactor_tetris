#include "print.h"
#include "shape.h"

static int check_line_deletion(t_game_info *gameinfo, suseconds_t *timer, int *decrease);
static void copy_shape_on_buffer(t_game_info *gameinfo, char Buffer[TABLE_ROW][TABLE_COL]);

void print_shape_moved_down(t_game_info *gameinfo, suseconds_t *timer, int *decrease, bool add_bonus) {
	t_shape temp = duplicate_shape(gameinfo->current_shape);
	temp.row++;
	if(check_puttable_shape(temp, gameinfo->table_game))
		gameinfo->current_shape.row++;
	else {
		copy_shape_on_buffer(gameinfo, gameinfo->table_game);
		int bonus_score = check_line_deletion(gameinfo, timer, decrease);
		if (add_bonus)
			gameinfo->score += 100 * bonus_score;
		replace_shape(gameinfo);
	}
	delete_shape(temp);
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

static int check_line_deletion(t_game_info *gameinfo, suseconds_t *timer, int *decrease) {
	int count = 0;

	for(int n = 0; n < TABLE_ROW; ++n){
		int sum = 0;
		for(int m = 0; m < TABLE_COL; ++m) {
			sum += gameinfo->table_game[n][m];
		}
		if(sum == TABLE_COL){
			count++;
			for(int k = n; k >=1; k--)
				for(int l = 0; l < TABLE_COL; ++l)
					gameinfo->table_game[k][l]=gameinfo->table_game[k-1][l];
			for(int l = 0; l < TABLE_COL; ++l)
				gameinfo->table_game[0][l] = 0;
			*timer-=(*decrease)--;
		}
	}
	return count;
}

static void copy_shape_on_buffer(t_game_info *gameinfo, char Buffer[TABLE_ROW][TABLE_COL]) {
	for(int i = 0; i < gameinfo->current_shape.side_length; ++i){
		for(int j = 0; j < gameinfo->current_shape.side_length; ++j){
			if(gameinfo->current_shape.table_shape[i][j])
				Buffer[gameinfo->current_shape.row + i][gameinfo->current_shape.col + j]
					= gameinfo->current_shape.table_shape[i][j];
		}
	}
}
