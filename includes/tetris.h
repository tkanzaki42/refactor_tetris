#ifndef TETRIS_H
# define TETRIS_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <time.h>
# include <sys/time.h>
# include <ncurses.h>

# define TABLE_ROW 20
# define TABLE_COL 15

typedef struct {
	suseconds_t	interval;
	int			decrease_time_of_interval;
} t_time;

typedef struct {
	char	**table_shape;
	int		side_length;  // side length of a square which can store the sphere
	int		row;
	int		col;
} t_shape;

typedef struct {
	char			table_game[TABLE_ROW][TABLE_COL];
	t_shape			current_shape;
	int				score;
	bool			is_continue_game;
	struct timeval	last_update_time;
} t_game_info;

#endif
