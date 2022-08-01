#include "cs.h"
#include "ds.h"
#include "cp.h"

t_shape create_random_shape() {
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
	new_shape.col = rand() % (TABLE_COL - new_shape.position_col + 1);
	new_shape.row = 0;
	return new_shape;
}

t_shape duplicate_shape(t_shape shape){

	t_shape new_shape = shape;
	char **copyshape = shape.table_shape;
	new_shape.table_shape = (char**)malloc(new_shape.position_col*sizeof(char*));
    for(int i = 0; i < new_shape.position_col; i++){
		new_shape.table_shape[i] = (char*)malloc(new_shape.position_col*sizeof(char));
		for(int j = 0; j < new_shape.position_col; j++) {
			new_shape.table_shape[i][j] = copyshape[i][j];
		}
    }
    return new_shape;
}

void replace_shape(t_game_info *gameinfo) {
	delete_shape(gameinfo->current_shape);
	gameinfo->current_shape = create_random_shape();
	if(!check_puttable(gameinfo->current_shape, gameinfo->table_game)){
		gameinfo->is_continue_game = false;
	}
}
