#include "tetris.h"
#include "game_body.h"

int main(void) {
	t_game_info	gameinfo;

	prepare_game(&gameinfo);
	play_game(&gameinfo);
	finalize_game(&gameinfo);
	return 0;
}
