#ifndef SHAPE_CHECK_H
# define SHAPE_CHECK_H

# include "tetris.h"

bool check_shape_puttable(
		const t_shape *shape, const char table[TABLE_ROW][TABLE_COL]);

#endif
