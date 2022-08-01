#ifndef TETRIS_H
# define TETRIS_H

#include <stdio.h>
#include <stdlib.h>
# include <stdbool.h>
#include <time.h>
#include <sys/time.h>
#include <ncurses.h>

# define TABLE_ROW 20
# define TABLE_COL 15

# define INPUTKEY_DOWN   's'
# define INPUTKEY_LEFT   'a'
# define INPUTKEY_RIGHT  'd'
# define INPUTKEY_ROTATE 'w'

typedef struct {
	char	**table_shape;
	int		side_length;  // side length of a square which can store the sphere
	int		row;
	int		col;
} t_shape;

typedef struct {
	char	table_game[TABLE_ROW][TABLE_COL];
	t_shape	current_shape;
	int		score;
	bool	is_continue_game;
} t_game_info;

struct timeval before_now, now;

#endif
