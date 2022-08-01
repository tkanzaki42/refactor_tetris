#include "tetris.h"
#include "cs.h"
#include "ds.h"
#include "rs.h"
#include "cp.h"
#include "pt.h"
#include "hastoupdate.h"
#include "settimeout.h"

const Struct StructsArray[7]= {
	{(char *[]){(char []){0,1,1},(char []){1,1,0}, (char []){0,0,0}}, 3, 0, 0},
	{(char *[]){(char []){1,1,0},(char []){0,1,1}, (char []){0,0,0}}, 3, 0, 0},
	{(char *[]){(char []){0,1,0},(char []){1,1,1}, (char []){0,0,0}}, 3, 0, 0},
	{(char *[]){(char []){0,0,1},(char []){1,1,1}, (char []){0,0,0}}, 3, 0, 0},
	{(char *[]){(char []){1,0,0},(char []){1,1,1}, (char []){0,0,0}}, 3, 0, 0},
	{(char *[]){(char []){1,1},(char []){1,1}}, 2, 0, 0},
	{(char *[]){(char []){0,0,0,0}, (char []){1,1,1,1}, (char []){0,0,0,0}, (char []){0,0,0,0}}, 4, 0, 0}
};

struct timeval before_now, now;

void game_init() {
    srand(time(0));
    initscr();
	gettimeofday(&before_now, NULL);
	set_timeout(1);
}

Struct create_new_shape() {
	Struct new_shape;

	new_shape = create_shape(StructsArray[rand()%7]);
    new_shape.col = rand()%(C-new_shape.width+1);
    new_shape.row = 0;
    delete_shape(current);
	return (new_shape);
}

void reflect_key_input(int c, int *final, char Table[R][C], char *GameOn, suseconds_t *timer, int *decrease) {
	Struct temp = create_shape(current);
	switch(c){
		case 's':
			temp.row++;  //move down
			if(FunctionCP(temp, Table))
				current.row++;
			else {
				copy_shape_on_table(Table);
				int n, m, sum, count=0;
				for(n=0;n<R;n++){
					sum = 0;
					for(m=0;m< C;m++) {
						sum+=Table[n][m];
					}
					if(sum==C){
						count++;
						int l, k;
						for(k = n;k >=1;k--)
							for(l=0;l<C;l++)
								Table[k][l]=Table[k-1][l];
						for(l=0;l<C;l++)
							Table[k][l]=0;
						*timer-=(*decrease)--;
					}
				}
				*final += 100*count;
				Struct new_shape = create_shape(StructsArray[rand()%7]);
				new_shape.col = rand()%(C-new_shape.width+1);
				new_shape.row = 0;
				delete_shape(current);
				current = new_shape;
				if(!FunctionCP(current, Table)){
					*GameOn = F;
				}
			}
			break;
		case 'd':
			temp.col++;
			if(FunctionCP(temp, Table))
				current.col++;
			break;
		case 'a':
			temp.col--;
			if(FunctionCP(temp, Table))
				current.col--;
			break;
		case 'w':
			rotate_shape(temp);
			if(FunctionCP(temp, Table))
				rotate_shape(current);
			break;
	}
	delete_shape(temp);
	FunctionPT(*final, Table);
}

void update_screen(const int final, char Table[R][C], char *GameOn, suseconds_t *timer, int *decrease) {
	Struct temp = create_shape(current);
	temp.row++;
	if(FunctionCP(temp, Table))
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
		for(n=0;n<R;n++){
			sum = 0;
			for(m=0;m< C;m++) {
				sum+=Table[n][m];
			}
			if(sum==C){
				count++;
				int l, k;
				for(k = n;k >=1;k--)
					for(l=0;l<C;l++)
						Table[k][l]=Table[k-1][l];
				for(l=0;l<C;l++)
					Table[k][l]=0;
				*timer-=(*decrease)--;
			}
		}
		Struct new_shape = create_shape(StructsArray[rand()%7]);
		new_shape.col = rand()%(C-new_shape.width+1);
		new_shape.row = 0;
		delete_shape(current);
		current = new_shape;
		if(!FunctionCP(current, Table)){
			*GameOn = F;
		}
	}
	delete_shape(temp);
	FunctionPT(final, Table);
	gettimeofday(&before_now, NULL);
}

void play_game(int *final, char Table[R][C], char *GameOn) {
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

void print_gameend_screen(const int final, const char Table[R][C]) {
	int i, j;

	for(i = 0; i < R ;i++){
		for(j = 0; j < C ; j++){
			printf("%c ", Table[i][j] ? '#': '.');
		}
		printf("\n");
	}
	printf("\nGame over!\n");
	printf("\nScore: %d\n", final);
}

int main() {
	int final = 0;
	char Table[R][C] = {0};
	char GameOn = T;
	game_init();
	current = create_new_shape();
	if(!FunctionCP(current, Table)){
		GameOn = F;
	}
    FunctionPT(final, Table);
	play_game(&final, Table, &GameOn);
	delete_shape(current);
	endwin();
	print_gameend_screen(final, Table);
    return 0;
}
