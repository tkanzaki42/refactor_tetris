#include "tetris.h"
#include "game.h"

int main() {
	t_game_info	gameinfo;

	start_game(&gameinfo);
	play_game(&gameinfo);
	finalize_game(&gameinfo);
	return 0;
}
