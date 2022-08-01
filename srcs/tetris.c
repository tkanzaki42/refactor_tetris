#include "tetris.h"
#include "cs.h"
#include "ds.h"
#include "rs.h"
#include "cp.h"
#include "pt.h"
#include "hastoupdate.h"
#include "settimeout.h"

char Table[R][C] = {0};
int final = 0;
char GameOn = T;
suseconds_t timer = 400000;
int decrease = 1000;

const Struct StructsArray[7]= {
	{(char *[]){(char []){0,1,1},(char []){1,1,0}, (char []){0,0,0}}, 3},
	{(char *[]){(char []){1,1,0},(char []){0,1,1}, (char []){0,0,0}}, 3},
	{(char *[]){(char []){0,1,0},(char []){1,1,1}, (char []){0,0,0}}, 3},
	{(char *[]){(char []){0,0,1},(char []){1,1,1}, (char []){0,0,0}}, 3},
	{(char *[]){(char []){1,0,0},(char []){1,1,1}, (char []){0,0,0}}, 3},
	{(char *[]){(char []){1,1},(char []){1,1}}, 2},
	{(char *[]){(char []){0,0,0,0}, (char []){1,1,1,1}, (char []){0,0,0,0}, (char []){0,0,0,0}}, 4}
};

struct timeval before_now, now;

void game_init() {
    srand(time(0));
    final = 0;
    initscr();
	gettimeofday(&before_now, NULL);
	set_timeout(1);
}

Struct create_new_shape() {
	Struct new_shape;

	FunctionCS(StructsArray[rand()%7]);
    new_shape.col = rand()%(C-new_shape.width+1);
    new_shape.row = 0;
    FunctionDS(current);
	return (new_shape);
}

void reflect_key_input(int c) {
	Struct temp = FunctionCS(current);
	switch(c){
		case 's':
			temp.row++;  //move down
			if(FunctionCP(temp))
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
						timer-=decrease--;
					}
				}
				final += 100*count;
				Struct new_shape = FunctionCS(StructsArray[rand()%7]);
				new_shape.col = rand()%(C-new_shape.width+1);
				new_shape.row = 0;
				FunctionDS(current);
				current = new_shape;
				if(!FunctionCP(current)){
					GameOn = F;
				}
			}
			break;
		case 'd':
			temp.col++;
			if(FunctionCP(temp))
				current.col++;
			break;
		case 'a':
			temp.col--;
			if(FunctionCP(temp))
				current.col--;
			break;
		case 'w':
			FunctionRS(temp);
			if(FunctionCP(temp))
				FunctionRS(current);
			break;
	}
	FunctionDS(temp);
	FunctionPT();
}

void update_screen() {
	Struct temp = FunctionCS(current);
	switch('s') {
		case 's':
			temp.row++;
			if(FunctionCP(temp))
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
						timer-=decrease--;
					}
				}
				Struct new_shape = FunctionCS(StructsArray[rand()%7]);
				new_shape.col = rand()%(C-new_shape.width+1);
				new_shape.row = 0;
				FunctionDS(current);
				current = new_shape;
				if(!FunctionCP(current)){
					GameOn = F;
				}
			}
			break;
		case 'd':
			temp.col++;
			if(FunctionCP(temp))
				current.col++;
			break;
		case 'a':
			temp.col--;
			if(FunctionCP(temp))
				current.col--;
			break;
		case 'w':
			FunctionRS(temp);
			if(FunctionCP(temp))
				FunctionRS(current);
			break;
	}
	FunctionDS(temp);
	FunctionPT();
	gettimeofday(&before_now, NULL);
}

void play_game() {
    int c;

	while(GameOn){
		if ((c = getch()) != ERR)
			reflect_key_input(c);
		gettimeofday(&now, NULL);
		if (hasToUpdate())
			update_screen();
	}
}

void print_gameend_screen() {
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
	game_init();
	current = create_new_shape();
	if(!FunctionCP(current)){
		GameOn = F;
	}
    FunctionPT();
	play_game();
	FunctionDS(current);
	endwin();
	print_gameend_screen();
    return 0;
}
