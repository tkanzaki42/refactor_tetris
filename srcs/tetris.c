#include "tetris.h"
#include "cs.h"
#include "ds.h"
#include "rs.h"
#include "cp.h"
#include "pt.h"
#include "hastoupdate.h"
#include "settimeout.h"

void init_gameinfo_struct(t_game_info *gameinfo) {
	gameinfo->score = 0;
	for(int i = 0; i < TABLE_ROW; ++i)
		for(int j = 0; j < TABLE_COL; ++j)
			gameinfo->table_game[i][j] = 0;
	gameinfo->is_continue_game = true;
	gameinfo->current_shape.side_length = 0;
	gameinfo->current_shape.row = 0;
	gameinfo->current_shape.col = 0;
	gameinfo->current_shape.table_shape = NULL;
	replace_shape(gameinfo);
}

void init_game(t_game_info *gameinfo) {
    srand(time(0));
    initscr();
	gettimeofday(&before_now, NULL);
	set_timeout(1);
	init_gameinfo_struct(gameinfo);
}

int check_line_deletion(t_game_info *gameinfo, suseconds_t *timer, int *decrease) {
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

void move_shape_down(t_game_info *gameinfo, suseconds_t *timer, int *decrease, bool add_bonus) {
	t_shape temp = duplicate_shape(gameinfo->current_shape);
	temp.row++;
	if(check_puttable(temp, gameinfo->table_game))
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

void reflect_key_input(int c, t_game_info *gameinfo, suseconds_t *timer, int *decrease) {
	t_shape temp = duplicate_shape(gameinfo->current_shape);
	switch(c){
		case INPUTKEY_DOWN:
			move_shape_down(gameinfo, timer, decrease, true);
			break;
		case INPUTKEY_RIGHT:
			temp.col++;
			if(check_puttable(temp, gameinfo->table_game))
				gameinfo->current_shape.col++;
			break;
		case INPUTKEY_LEFT:
			temp.col--;
			if(check_puttable(temp, gameinfo->table_game))
				gameinfo->current_shape.col--;
			break;
		case INPUTKEY_ROTATE:
			rotate_shape(temp);
			if(check_puttable(temp, gameinfo->table_game))
				rotate_shape(gameinfo->current_shape);
			break;
	}
	delete_shape(temp);
	print_table(gameinfo);
}

void update_screen(t_game_info *gameinfo, suseconds_t *timer, int *decrease) {
	move_shape_down(gameinfo, timer, decrease, false);
	print_table(gameinfo);
	gettimeofday(&before_now, NULL);
}

void play_game(t_game_info *gameinfo) {
    int c;
	suseconds_t timer = 400000;
	int decrease = 1000;

	while(gameinfo->is_continue_game){
		if ((c = getch()) != ERR)
			reflect_key_input(c, gameinfo, &timer, &decrease);
		gettimeofday(&now, NULL);
		if (hasToUpdate(&timer))
			update_screen(gameinfo, &timer, &decrease);
	}
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

void finalize_game(t_game_info *gameinfo) {
	print_gameend_screen(gameinfo);
	delete_shape(gameinfo->current_shape);
	endwin();
}

int main() {
	t_game_info	gameinfo;

	init_game(&gameinfo);
	print_table(&gameinfo);
	play_game(&gameinfo);
	finalize_game(&gameinfo);
	return 0;
}
