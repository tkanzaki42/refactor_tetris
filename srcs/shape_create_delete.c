#include "shape_create_delete.h"
#include "shape_check.h"

#define POINT_1LINE 100
#define SHAPE_LIST_AMOUNT 7

static void create_random_shape(t_shape *new_shape);

void delete_shape(t_shape *shape) {
	if (shape->table_shape == NULL)
		return;
	for(int i = 0; i < shape->side_length; i++) {
		free(shape->table_shape[i]);
		shape->table_shape[i] = NULL;
	}
	free(shape->table_shape);
	shape->table_shape = NULL;
}

void duplicate_shape(const t_shape *shape, t_shape *dup) {
	dup->table_shape = NULL;
	dup->side_length = shape->side_length;
	dup->row = shape->row;
	dup->col = shape->col;
	dup->table_shape = (char**)malloc(dup->side_length * sizeof(char*));
	for (int i = 0; i < dup->side_length; ++i) {
		dup->table_shape[i] = (char*)malloc(dup->side_length * sizeof(char));
		for (int j = 0; j < dup->side_length; ++j) {
			dup->table_shape[i][j] = shape->table_shape[i][j];
		}
	}
}

void replace_shape(t_game_info *gameinfo) {
	delete_shape(&gameinfo->current_shape);
	create_random_shape(&gameinfo->current_shape);
	if(!check_shape_puttable(&gameinfo->current_shape, gameinfo->table_game)) {
		gameinfo->is_continue_game = false;
	}
}

static void create_random_shape(t_shape *new_shape) {
	const t_shape shape_list[SHAPE_LIST_AMOUNT] = {
		{(char *[]){(char []){0,1,1}, (char []){1,1,0}, (char []){0,0,0}}, 3, 0, 0},
		{(char *[]){(char []){1,1,0}, (char []){0,1,1}, (char []){0,0,0}}, 3, 0, 0},
		{(char *[]){(char []){0,1,0}, (char []){1,1,1}, (char []){0,0,0}}, 3, 0, 0},
		{(char *[]){(char []){0,0,1}, (char []){1,1,1}, (char []){0,0,0}}, 3, 0, 0},
		{(char *[]){(char []){1,0,0}, (char []){1,1,1}, (char []){0,0,0}}, 3, 0, 0},
		{(char *[]){(char []){1,1}, (char []){1,1}}, 2, 0, 0},
		{(char *[]){(char []){0,0,0,0}, (char []){1,1,1,1}, (char []){0,0,0,0}, (char []){0,0,0,0}},
			4, 0, 0}
	};
	;
	duplicate_shape(&shape_list[rand() % SHAPE_LIST_AMOUNT], new_shape);
	new_shape->col = rand() % (TABLE_COL - new_shape->side_length + 1);
	new_shape->row = 0;
}
