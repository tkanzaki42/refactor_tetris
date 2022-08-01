#ifndef TETRIS_H
# define TETRIS_H

#include <stdio.h>
#include <stdlib.h>
// # include <stdbool.h>
#include <time.h>
#include <sys/time.h>
#include <ncurses.h>

# define TABLE_ROW 20
# define TABLE_COL 15

# define INPUTKEY_DOWN   's'
# define INPUTKEY_LEFT   'a'
# define INPUTKEY_RIGHT  'd'
# define INPUTKEY_ROTATE 'w'

# define T 1
# define F 0

// enum {
// 	BOOL_TRUE = 1,
// 	BOOL_FALSE = 0
// };

typedef struct {
    char **array;
    int width, row, col;
} Struct;
Struct current;

// typedef struct {
// 	char	**table_shape;
// 	int		position_col;
// 	int		row;
// 	int		col;
// } t_shape;

// typedef struct {
// 	char	table_game[TABLE_ROW][TABLE_COL];
// 	t_shape	current_shape;
// 	int		score;
// 	bool	is_continue_game;
// } t_game_info;

#endif
