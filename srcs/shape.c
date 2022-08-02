#include "shape.h"

static t_shape create_random_shape();
static int check_line_deletion(t_game_info *gameinfo, suseconds_t *timer, int *decrease);

void rotate_shape(t_shape shape) {
	t_shape temp = duplicate_shape(shape);
	for (int i = 0; i < shape.side_length ; ++i) {
		for (int j = 0, k = shape.side_length - 1; j < shape.side_length; ++j, --k){
			shape.table_shape[i][j] = temp.table_shape[k][i];
		}
	}
	delete_shape(temp);
}

void delete_shape(t_shape shape) {
	if (shape.table_shape == NULL)
		return;
	for(int i = 0; i < shape.side_length; i++) {
		free(shape.table_shape[i]);
	}
	free(shape.table_shape);
}

t_shape duplicate_shape(t_shape shape){

	t_shape new_shape = shape;
	char **copyshape = shape.table_shape;
	new_shape.table_shape = (char**)malloc(new_shape.side_length*sizeof(char*));
    for(int i = 0; i < new_shape.side_length; i++){
		new_shape.table_shape[i] = (char*)malloc(new_shape.side_length*sizeof(char));
		for(int j = 0; j < new_shape.side_length; j++) {
			new_shape.table_shape[i][j] = copyshape[i][j];
		}
    }
    return new_shape;
}

void replace_shape(t_game_info *gameinfo) {
	delete_shape(gameinfo->current_shape);
	gameinfo->current_shape = create_random_shape();
	if(!check_puttable_shape(gameinfo->current_shape, gameinfo->table_game)){
		gameinfo->is_continue_game = false;
	}
}

bool check_puttable_shape(const t_shape shape, const char table[TABLE_ROW][TABLE_COL]) {
	for (int i = 0; i < shape.side_length; i++) {
		for (int j = 0; j < shape.side_length; j++){
			if (!shape.table_shape[i][j])
				continue ;
			if (shape.col + j < 0
				|| shape.col + j >= TABLE_COL
				|| shape.row + i >= TABLE_ROW
				|| table[shape.row + i][shape.col + j])
				return false;
		}
	}
	return true;
}

void copy_shape_to_table(const t_shape *shape, char table[TABLE_ROW][TABLE_COL]) {
	for(int i = 0; i < shape->side_length; ++i){
		for(int j = 0; j < shape->side_length; ++j){
			if(shape->table_shape[i][j])
				table[shape->row + i][shape->col + j] = shape->table_shape[i][j];
		}
	}
}

void move_shape_down(t_game_info *gameinfo, suseconds_t *timer, int *decrease, bool add_bonus) {
	t_shape temp = duplicate_shape(gameinfo->current_shape);
	temp.row++;
	if(check_puttable_shape(temp, gameinfo->table_game))
		gameinfo->current_shape.row++;
	else {
		copy_shape_to_table(&gameinfo->current_shape, gameinfo->table_game);
		int bonus_score = check_line_deletion(gameinfo, timer, decrease);
		if (add_bonus)
			gameinfo->score += 100 * bonus_score;
		replace_shape(gameinfo);
	}
	delete_shape(temp);
}

static t_shape create_random_shape() {
	const t_shape shape_list[7] = {
		{(char *[]){(char []){0,1,1}, (char []){1,1,0}, (char []){0,0,0}}, 3, 0, 0},
		{(char *[]){(char []){1,1,0}, (char []){0,1,1}, (char []){0,0,0}}, 3, 0, 0},
		{(char *[]){(char []){0,1,0}, (char []){1,1,1}, (char []){0,0,0}}, 3, 0, 0},
		{(char *[]){(char []){0,0,1}, (char []){1,1,1}, (char []){0,0,0}}, 3, 0, 0},
		{(char *[]){(char []){1,0,0}, (char []){1,1,1}, (char []){0,0,0}}, 3, 0, 0},
		{(char *[]){(char []){1,1}, (char []){1,1}}, 2, 0, 0},
		{(char *[]){(char []){0,0,0,0}, (char []){1,1,1,1}, (char []){0,0,0,0}, (char []){0,0,0,0}},
			4, 0, 0}
	};

	t_shape new_shape = duplicate_shape(shape_list[rand() % 7]);
	new_shape.col = rand() % (TABLE_COL - new_shape.side_length + 1);
	new_shape.row = 0;
	return new_shape;
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
