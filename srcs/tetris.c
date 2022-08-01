#include "tetris.h"
#include "cs.h"
#include "ds.h"
#include "rs.h"
#include "cp.h"
#include "pt.h"
#include "hastoupdate.h"
#include "settimeout.h"

struct timeval before_now, now;

t_shape create_new_shape(t_game_info *gameinfo) {
	t_shape new_shape;

	new_shape = create_random_shape();
    new_shape.col = rand()%(TABLE_COL - new_shape.position_col + 1);
    new_shape.row = 0;
    delete_shape(gameinfo->current_shape);
	return (new_shape);
}

void init_game(t_game_info *gameinfo) {
    srand(time(0));
    initscr();
	gettimeofday(&before_now, NULL);
	set_timeout(1);
	gameinfo->score = 0;
	for(int i = 0; i < TABLE_ROW; ++i)
		for(int j = 0; j < TABLE_COL; ++j)
			gameinfo->table_game[i][j] = 0;
	gameinfo->is_continue_game = true;
	gameinfo->current_shape.position_col = 0;
	gameinfo->current_shape.row = 0;
	gameinfo->current_shape.col = 0;
	gameinfo->current_shape.table_shape = NULL;
	gameinfo->current_shape = create_new_shape(gameinfo);
	if(!check_puttable(gameinfo->current_shape, gameinfo->table_game)) {
		gameinfo->is_continue_game = false;
	}
}

void reflect_key_input(int c, t_game_info *gameinfo, suseconds_t *timer, int *decrease) {
	t_shape temp = create_shape(gameinfo->current_shape);
	switch(c){
		case INPUTKEY_DOWN:
			temp.row++;  //move down
			if(check_puttable(temp, gameinfo->table_game))
				gameinfo->current_shape.row++;
			else {
				copy_shape_on_buffer(gameinfo, gameinfo->table_game);
				int n, m, sum, count=0;
				for(n = 0; n < TABLE_ROW; ++n){
					sum = 0;
					for(m = 0; m < TABLE_COL; ++m) {
						sum += gameinfo->table_game[n][m];
					}
					if(sum == TABLE_COL){
						count++;
						int l, k;
						for(k = n;k >=1;k--)
							for(l = 0; l < TABLE_COL; ++l)
								gameinfo->table_game[k][l]=gameinfo->table_game[k-1][l];
						for(l = 0; l < TABLE_COL; ++l)
							gameinfo->table_game[k][l]=0;
						*timer-=(*decrease)--;
					}
				}
				gameinfo->score += 100*count;
				t_shape new_shape = create_random_shape();
				new_shape.col = rand()%(TABLE_COL - new_shape.position_col + 1);
				new_shape.row = 0;
				delete_shape(gameinfo->current_shape);
				gameinfo->current_shape = new_shape;
				if(!check_puttable(gameinfo->current_shape, gameinfo->table_game)){
					gameinfo->is_continue_game = false;
				}
			}
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
	t_shape temp = create_shape(gameinfo->current_shape);
	temp.row++;
	if(check_puttable(temp, gameinfo->table_game))
		gameinfo->current_shape.row++;
	else {
		int i, j;
		for(i = 0; i < gameinfo->current_shape.position_col ;i++){
			for(j = 0; j < gameinfo->current_shape.position_col ; j++){
				if(gameinfo->current_shape.table_shape[i][j])
					gameinfo->table_game[gameinfo->current_shape.row + i][gameinfo->current_shape.col + j]
						= gameinfo->current_shape.table_shape[i][j];
			}
		}
		int n, m, sum, count=0;
		for(n = 0; n < TABLE_ROW; ++n){
			sum = 0;
			for(m = 0; m < TABLE_COL; ++m) {
				sum+=gameinfo->table_game[n][m];
			}
			if(sum == TABLE_COL){
				count++;
				int l, k;
				for(k = n;k >=1;k--)
					for(l = 0; l < TABLE_COL; ++l)
						gameinfo->table_game[k][l]=gameinfo->table_game[k-1][l];
				for(l = 0; l < TABLE_COL; ++l)
					gameinfo->table_game[k][l]=0;
				*timer-=(*decrease)--;
			}
		}
		t_shape new_shape = create_random_shape();
		new_shape.col = rand() % (TABLE_COL - new_shape.position_col + 1);
		new_shape.row = 0;
		delete_shape(gameinfo->current_shape);
		gameinfo->current_shape = new_shape;
		if(!check_puttable(gameinfo->current_shape, gameinfo->table_game)){
			gameinfo->is_continue_game = false;
		}
	}
	delete_shape(temp);
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
	int i, j;

	for(i = 0; i < TABLE_ROW; ++i){
		for(j = 0; j < TABLE_COL; ++j){
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
