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
    int c;
	suseconds_t timer = 400000;
	int decrease = 1000;

	print_table(gameinfo);
	while(gameinfo->is_continue_game){
		if ((c = getch()) != ERR)
			update_key_input(c, gameinfo, &timer, &decrease);
		gettimeofday(&gameinfo->now, NULL);
		if (has_to_update(&timer, gameinfo))
			update_screen(gameinfo, &timer, &decrease);
		gettimeofday(&gameinfo->before_now, NULL);
	}
}

void finalize_game(t_game_info *gameinfo) {
	delete_shape(gameinfo->current_shape);
	endwin();
	print_gameend_screen(gameinfo);
}

static int has_to_update(const suseconds_t *timer, const t_game_info *gameinfo){
	return
		(
			(suseconds_t)(gameinfo->now.tv_sec*1000000
				+ gameinfo->now.tv_usec)
			-((suseconds_t)gameinfo->before_now.tv_sec*1000000
				+ gameinfo->before_now.tv_usec)
		)
		> *timer;
}

static void set_timeout(int time) {
	timeout(time);
}
