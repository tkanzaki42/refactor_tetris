#include "game_body.h"
#include "game_init.h"
#include "key_input.h"
#include "screen_print.h"
#include "screen_update.h"
#include "shape_create_delete.h"

#define INTERVAL_INIT_VALUE 400000
#define DECREASE_TIME_INIT_VALUE 1000

void prepare_game(t_game_info *gameinfo) {
	srand(time(0));
	initscr();
	timeout(1);
	init_gameinfo_struct(gameinfo);
}

void play_game(t_game_info *gameinfo) {
	t_time time = {
		.interval = INTERVAL_INIT_VALUE,
		.decrease_time_of_interval = DECREASE_TIME_INIT_VALUE
	};

	print_table(gameinfo);
	while (gameinfo->is_continue_game) {
		int key_input = getch();
		if (key_input != ERR) {
			accept_key_input(key_input, gameinfo, &time);
			print_table(gameinfo);
		}
		if (has_to_update(gameinfo, &time))
			update_screen(gameinfo, &time);
	}
}

void finalize_game(t_game_info *gameinfo) {
	delete_shape(&gameinfo->current_shape);
	endwin();
	print_gameend_screen(gameinfo);
}
