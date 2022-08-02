#include "game.h"
#include "init.h"
#include "update.h"
#include "shape.h"
#include "print.h"

#define TIMER_INIT_VALUE 400000
#define DECREASE_INIT_VALUE 1000
#define USEC_PER_SEC 1000000

static int has_to_update(const suseconds_t *timer, const t_game_info *gameinfo);

void prepare_game(t_game_info *gameinfo) {
    srand(time(0));
    initscr();
	timeout(1);
	init_gameinfo_struct(gameinfo);
}

void play_game(t_game_info *gameinfo) {
	suseconds_t timer = TIMER_INIT_VALUE;
	int decrease = DECREASE_INIT_VALUE;

	print_table(gameinfo);
	while(gameinfo->is_continue_game) {
		int key_input = getch();
		if (key_input != ERR)
			update_key_input(key_input, gameinfo, &timer, &decrease);
		if (has_to_update(&timer, gameinfo))
			update_screen(gameinfo, &timer, &decrease);
	}
}

void finalize_game(t_game_info *gameinfo) {
	delete_shape(&gameinfo->current_shape);
	endwin();
	print_gameend_screen(gameinfo);
}

static int has_to_update(const suseconds_t *timer, const t_game_info *gameinfo) {
	struct timeval	current_time_timeval;
	gettimeofday(&current_time_timeval, NULL);
	suseconds_t current_time
		= current_time_timeval.tv_sec * USEC_PER_SEC + current_time_timeval.tv_usec;

	suseconds_t last_update_time
		= gameinfo->last_update_time.tv_sec * USEC_PER_SEC + gameinfo->last_update_time.tv_usec;

	return ((current_time - last_update_time) > *timer);
}
