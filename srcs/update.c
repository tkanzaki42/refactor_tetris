#include "update.h"
#include "shape.h"
#include "print.h"

void update_key_input(
		int key_input, t_game_info *gameinfo, suseconds_t *timer, int *decrease) {
	t_shape shape_checking = duplicate_shape(gameinfo->current_shape);

	switch (key_input) {
		case INPUTKEY_DOWN:
			move_shape_down(gameinfo, timer, decrease, true);
			break;
		case INPUTKEY_RIGHT:
			shape_checking.col++;
			if(check_puttable_shape(shape_checking, gameinfo->table_game))
				gameinfo->current_shape.col++;
			break;
		case INPUTKEY_LEFT:
			shape_checking.col--;
			if(check_puttable_shape(shape_checking, gameinfo->table_game))
				gameinfo->current_shape.col--;
			break;
		case INPUTKEY_ROTATE:
			rotate_shape(shape_checking);
			if(check_puttable_shape(shape_checking, gameinfo->table_game))
				rotate_shape(gameinfo->current_shape);
			break;
	}
	delete_shape(shape_checking);
	print_table(gameinfo);
}

void update_screen(t_game_info *gameinfo, suseconds_t *timer, int *decrease) {
	move_shape_down(gameinfo, timer, decrease, false);
	print_table(gameinfo);
	gettimeofday(&gameinfo->before_now, NULL);
}
