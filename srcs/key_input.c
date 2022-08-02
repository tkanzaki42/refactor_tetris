#include "key_input.h"
#include "screen_print.h"
#include "shape_move_copy.h"
#include "shape_check.h"
#include "shape_create_delete.h"

# define INPUTKEY_DOWN   's'
# define INPUTKEY_LEFT   'a'
# define INPUTKEY_RIGHT  'd'
# define INPUTKEY_ROTATE 'w'

void accept_key_input(
		int key_input, t_game_info *gameinfo, t_time *time) {
	t_shape shape_checking;

	duplicate_shape(&gameinfo->current_shape, &shape_checking);
	switch (key_input) {
		case INPUTKEY_DOWN:
			move_shape_down(gameinfo, time, true);
			break;
		case INPUTKEY_RIGHT:
			shape_checking.col++;
			if (check_shape_puttable(&shape_checking, gameinfo->table_game))
				gameinfo->current_shape.col++;
			break;
		case INPUTKEY_LEFT:
			shape_checking.col--;
			if (check_shape_puttable(&shape_checking, gameinfo->table_game))
				gameinfo->current_shape.col--;
			break;
		case INPUTKEY_ROTATE:
			rotate_shape(&shape_checking);
			if (check_shape_puttable(&shape_checking, gameinfo->table_game))
				rotate_shape(&gameinfo->current_shape);
			break;
	}
	delete_shape(&shape_checking);
	print_table(gameinfo);
}
