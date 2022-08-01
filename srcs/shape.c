#include "shape.h"

static t_shape create_random_shape();

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
