#include "tetris.h"
#include "cs.h"
#include "ds.h"
#include "rs.h"
#include "cp.h"
#include "pt.h"
#include "hastoupdate.h"
#include "settimeout.h"

struct timeval before_now, now;

void game_init() {
    srand(time(0));
    initscr();
	gettimeofday(&before_now, NULL);
	set_timeout(1);
}

Struct create_new_shape() {
	Struct new_shape;

	new_shape = create_random_shape();
    new_shape.col = rand()%(TABLE_COL - new_shape.width + 1);
    new_shape.row = 0;
    delete_shape(current);
	return (new_shape);
}

void reflect_key_input(int c, int *final, char Table[TABLE_ROW][TABLE_COL],
		char *GameOn, suseconds_t *timer, int *decrease) {
	Struct temp = create_shape(current);
	switch(c){
		case INPUTKEY_DOWN:
			temp.row++;  //move down
			if(check_puttable(temp, Table))
				current.row++;
			else {
				copy_shape_on_table(Table);
				int n, m, sum, count=0;
				for(n = 0; n < TABLE_ROW; ++n){
					sum = 0;
					for(m = 0; m < TABLE_COL; ++m) {
						sum+=Table[n][m];
					}
					if(sum == TABLE_COL){
						count++;
						int l, k;
						for(k = n;k >=1;k--)
							for(l = 0; l < TABLE_COL; ++l)
								Table[k][l]=Table[k-1][l];
						for(l = 0; l < TABLE_COL; ++l)
							Table[k][l]=0;
						*timer-=(*decrease)--;
					}
				}
				*final += 100*count;
				Struct new_shape = create_random_shape();
				new_shape.col = rand()%(TABLE_COL - new_shape.width + 1);
				new_shape.row = 0;
				delete_shape(current);
				current = new_shape;
				if(!check_puttable(current, Table)){
					*GameOn = F;
				}
			}
			break;
		case INPUTKEY_RIGHT:
			temp.col++;
			if(check_puttable(temp, Table))
				current.col++;
			break;
		case INPUTKEY_LEFT:
			temp.col--;
			if(check_puttable(temp, Table))
				current.col--;
			break;
		case INPUTKEY_ROTATE:
			rotate_shape(temp);
			if(check_puttable(temp, Table))
				rotate_shape(current);
			break;
	}
	delete_shape(temp);
	print_table(*final, Table);
}

void update_screen(const int final, char Table[TABLE_ROW][TABLE_COL], char *GameOn, suseconds_t *timer, int *decrease) {
	Struct temp = create_shape(current);
	temp.row++;
	if(check_puttable(temp, Table))
		current.row++;
	else {
		int i, j;
		for(i = 0; i < current.width ;i++){
			for(j = 0; j < current.width ; j++){
				if(current.array[i][j])
					Table[current.row+i][current.col+j] = current.array[i][j];
			}
		}
		int n, m, sum, count=0;
		for(n = 0; n < TABLE_ROW; ++n){
			sum = 0;
			for(m = 0; m < TABLE_COL; ++m) {
				sum+=Table[n][m];
			}
			if(sum == TABLE_COL){
				count++;
				int l, k;
				for(k = n;k >=1;k--)
					for(l = 0; l < TABLE_COL; ++l)
						Table[k][l]=Table[k-1][l];
				for(l = 0; l < TABLE_COL; ++l)
					Table[k][l]=0;
				*timer-=(*decrease)--;
			}
		}
		Struct new_shape = create_random_shape();
		new_shape.col = rand() % (TABLE_COL - new_shape.width + 1);
		new_shape.row = 0;
		delete_shape(current);
		current = new_shape;
		if(!check_puttable(current, Table)){
			*GameOn = F;
		}
	}
	delete_shape(temp);
	print_table(final, Table);
	gettimeofday(&before_now, NULL);
}

void play_game(int *final, char Table[TABLE_ROW][TABLE_COL], char *GameOn) {
    int c;
	suseconds_t timer = 400000;
	int decrease = 1000;

	while(*GameOn){
		if ((c = getch()) != ERR)
			reflect_key_input(c, final, Table, GameOn, &timer, &decrease);
		gettimeofday(&now, NULL);
		if (hasToUpdate(&timer))
			update_screen(*final, Table, GameOn, &timer, &decrease);
	}
}

void print_gameend_screen(const int final, const char Table[TABLE_ROW][TABLE_COL]) {
	int i, j;

	for(i = 0; i < TABLE_ROW; ++i){
		for(j = 0; j < TABLE_COL; ++j){
			printf("%c ", Table[i][j] ? '#': '.');
		}
		printf("\n");
	}
	printf("\nGame over!\n");
	printf("\nScore: %d\n", final);
}

int main() {
	int final = 0;
	char Table[TABLE_ROW][TABLE_COL] = {0};
	char GameOn = T;
	game_init();
	current = create_new_shape();
	if(!check_puttable(current, Table)){
		GameOn = F;
	}
	print_table(final, Table);
	play_game(&final, Table, &GameOn);
	delete_shape(current);
	endwin();
	print_gameend_screen(final, Table);
	return 0;
}
