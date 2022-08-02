#include "screen_update.h"
#include "screen_print.h"
#include "shape_move_copy.h"

#define USEC_PER_SEC 1000000

int has_to_update(const suseconds_t *timer, const t_game_info *gameinfo) {
	struct timeval	current_time_timeval;
	gettimeofday(&current_time_timeval, NULL);
	suseconds_t current_time
		= current_time_timeval.tv_sec * USEC_PER_SEC + current_time_timeval.tv_usec;

	suseconds_t last_update_time
		= gameinfo->last_update_time.tv_sec * USEC_PER_SEC + gameinfo->last_update_time.tv_usec;

	return ((current_time - last_update_time) > *timer);
}

void update_screen(t_game_info *gameinfo, suseconds_t *timer, int *decrease) {
	move_shape_down(gameinfo, timer, decrease, false);
	print_table(gameinfo);
	gettimeofday(&gameinfo->last_update_time, NULL);
}