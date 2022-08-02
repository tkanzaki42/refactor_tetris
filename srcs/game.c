#include "game.h"
#include "init.h"
#include "update.h"
#include "shape.h"
#include "print.h"

static int has_to_update(const suseconds_t *timer, const t_game_info *gameinfo);
static void set_timeout(int time);

void start_game(t_game_info *gameinfo) {
    srand(time(0));
    initscr();
	set_timeout(1);
	init_gameinfo_struct(gameinfo);
}

void play_game(t_game_info *gameinfo) {
	suseconds_t timer = 400000;
	int decrease = 1000;

	print_table(gameinfo);
	while(gameinfo->is_continue_game) {
		int key_input = getch();
		if (key_input != ERR)
			update_key_input(key_input, gameinfo, &timer, &decrease);
		gettimeofday(&gameinfo->now, NULL);
		if (has_to_update(&timer, gameinfo))
			update_screen(gameinfo, &timer, &decrease);
	}
}

void finalize_game(t_game_info *gameinfo) {
	delete_shape(gameinfo->current_shape);
	endwin();
	print_gameend_screen(gameinfo);
}

static int has_to_update(const suseconds_t *timer, const t_game_info *gameinfo) {
	suseconds_t current_time
		= gameinfo->now.tv_sec * 1000000 + gameinfo->now.tv_usec;
	suseconds_t previous_update_time
		= gameinfo->before_now.tv_sec * 1000000 + gameinfo->before_now.tv_usec;

	return ((current_time - previous_update_time) > *timer);
}

static void set_timeout(int time) {
	timeout(time);
}
