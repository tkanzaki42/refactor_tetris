#include "shape_move_copy.h"
#include "shape_create_delete.h"
#include "shape_check.h"

#define POINT_1LINE 100

static int check_line_deletion(t_game_info *gameinfo, suseconds_t *timer, int *decrease);

void rotate_shape(t_shape *shape) {
	t_shape shape_original;

	duplicate_shape(shape, &shape_original);
	for (int i = 0; i < shape->side_length ; ++i) {
		for (int j = 0, k = shape->side_length - 1; j < shape->side_length; ++j, --k) {
			shape->table_shape[i][j] = shape_original.table_shape[k][i];
		}
	}
	delete_shape(&shape_original);
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

static int check_line_deletion(t_game_info *gameinfo, suseconds_t *timer, int *decrease) {
	int delete_line_count = 0;

	for (int i = 0; i < TABLE_ROW; ++i) {
		int filled_cell_count_in_line = 0;
		for (int j = 0; j < TABLE_COL; ++j) {
			filled_cell_count_in_line += gameinfo->table_game[i][j];
		}
		if (filled_cell_count_in_line == TABLE_COL) {
			delete_line_count++;
			for (int k = i; k >= 1; --k)
				for (int l = 0; l < TABLE_COL; ++l)
					gameinfo->table_game[k][l] = gameinfo->table_game[k - 1][l];
			for (int l = 0; l < TABLE_COL; ++l)
				gameinfo->table_game[0][l] = 0;
			*timer -= (*decrease)--;
		}
	}
	return delete_line_count;
}

void copy_shape_to_table(const t_shape *shape, char table[TABLE_ROW][TABLE_COL]) {
	for (int i = 0; i < shape->side_length; ++i) {
		for (int j = 0; j < shape->side_length; ++j) {
			if (shape->table_shape[i][j])
				table[shape->row + i][shape->col + j] = shape->table_shape[i][j];
		}
	}
}
