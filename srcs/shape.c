#include "shape.h"

#define POINT_1LINE 100
#define SHAPE_LIST_AMOUNT 7

static void create_random_shape(t_shape *new_shape);
static int check_line_deletion(t_game_info *gameinfo, suseconds_t *timer, int *decrease);

void rotate_shape(t_shape *shape) {
	t_shape shape_original;
	duplicate_shape(shape, &shape_original);
	for (int i = 0; i < shape->side_length ; ++i) {
		for (int j = 0, k = shape->side_length - 1; j < shape->side_length; ++j, --k){
			shape->table_shape[i][j] = shape_original.table_shape[k][i];
		}
	}
	delete_shape(&shape_original);
}

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

bool check_shape_puttable(const t_shape *shape, const char table[TABLE_ROW][TABLE_COL]) {
	for (int i = 0; i < shape->side_length; ++i) {
		for (int j = 0; j < shape->side_length; ++j){
			if (!shape->table_shape[i][j])
				continue ;
			if (shape->col + j < 0
				|| shape->col + j >= TABLE_COL
				|| shape->row + i >= TABLE_ROW
				|| table[shape->row + i][shape->col + j])
				return false;
		}
	}
	return true;
}

void copy_shape_to_table(const t_shape *shape, char table[TABLE_ROW][TABLE_COL]) {
	for (int i = 0; i < shape->side_length; ++i) {
		for (int j = 0; j < shape->side_length; ++j) {
			if(shape->table_shape[i][j])
				table[shape->row + i][shape->col + j] = shape->table_shape[i][j];
		}
	}
}

void move_shape_down(t_game_info *gameinfo, suseconds_t *timer, int *decrease, bool add_bonus) {
	t_shape shape_checking;
	duplicate_shape(&gameinfo->current_shape, &shape_checking);
	shape_checking.row++;
	if (check_shape_puttable(&shape_checking, gameinfo->table_game))
		gameinfo->current_shape.row++;
	else {
		copy_shape_to_table(&gameinfo->current_shape, gameinfo->table_game);
		int bonus_score = check_line_deletion(gameinfo, timer, decrease);
		if (add_bonus)
			gameinfo->score += POINT_1LINE * bonus_score;
		replace_shape(gameinfo);
	}
	delete_shape(&shape_checking);
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

static int check_line_deletion(t_game_info *gameinfo, suseconds_t *timer, int *decrease) {
	int delete_line_count = 0;

	for (int i = 0; i < TABLE_ROW; ++i) {
		int filled_cell_count_in_line = 0;
		for (int j = 0; j < TABLE_COL; ++j) {
			filled_cell_count_in_line += gameinfo->table_game[i][j];
		}
		if (filled_cell_count_in_line == TABLE_COL) {
			delete_line_count++;
			for(int k = i; k >= 1; --k)
				for(int l = 0; l < TABLE_COL; ++l)
					gameinfo->table_game[k][l] = gameinfo->table_game[k - 1][l];
			for(int l = 0; l < TABLE_COL; ++l)
				gameinfo->table_game[0][l] = 0;
			*timer -= (*decrease)--;
		}
	}
	return delete_line_count;
}
