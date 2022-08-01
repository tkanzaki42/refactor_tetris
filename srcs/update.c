#include "update.h"
#include "shape.h"
#include "print.h"

void update_key_input(int c, t_game_info *gameinfo, suseconds_t *timer, int *decrease) {
	t_shape temp = duplicate_shape(gameinfo->current_shape);
	switch(c){
		case INPUTKEY_DOWN:
			print_shape_moved_down(gameinfo, timer, decrease, true);
			break;
		case INPUTKEY_RIGHT:
			temp.col++;
			if(check_puttable_shape(temp, gameinfo->table_game))
				gameinfo->current_shape.col++;
			break;
		case INPUTKEY_LEFT:
			temp.col--;
			if(check_puttable_shape(temp, gameinfo->table_game))
				gameinfo->current_shape.col--;
			break;
		case INPUTKEY_ROTATE:
			rotate_shape(temp);
			if(check_puttable_shape(temp, gameinfo->table_game))
				rotate_shape(gameinfo->current_shape);
			break;
	}
	delete_shape(temp);
	print_table(gameinfo);
}

void update_screen(t_game_info *gameinfo, suseconds_t *timer, int *decrease) {
	print_shape_moved_down(gameinfo, timer, decrease, false);
	print_table(gameinfo);
	gettimeofday(&gameinfo->before_now, NULL);
}
