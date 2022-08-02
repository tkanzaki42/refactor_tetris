#include "key_input.h"
#include "screen_print.h"
#include "shape_move_copy.h"
#include "shape_check.h"
#include "shape_create_delete.h"

void update_key_input(
		int key_input, t_game_info *gameinfo, suseconds_t *timer, int *decrease) {
	t_shape shape_checking;
	duplicate_shape(&gameinfo->current_shape, &shape_checking);
	switch (key_input) {
		case INPUTKEY_DOWN:
			move_shape_down(gameinfo, timer, decrease, true);
			break;
		case INPUTKEY_RIGHT:
			shape_checking.col++;
			if(check_shape_puttable(&shape_checking, gameinfo->table_game))
				gameinfo->current_shape.col++;
			break;
		case INPUTKEY_LEFT:
			shape_checking.col--;
			if(check_shape_puttable(&shape_checking, gameinfo->table_game))
				gameinfo->current_shape.col--;
			break;
		case INPUTKEY_ROTATE:
			rotate_shape(&shape_checking);
			if(check_shape_puttable(&shape_checking, gameinfo->table_game))
				rotate_shape(&gameinfo->current_shape);
			break;
	}
	delete_shape(&shape_checking);
	print_table(gameinfo);
}
