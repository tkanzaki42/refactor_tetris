#include "shape_check.h"

bool check_shape_puttable(const t_shape *shape, const char table[TABLE_ROW][TABLE_COL]) {
	for (int i = 0; i < shape->side_length; ++i) {
		for (int j = 0; j < shape->side_length; ++j) {
			if (!shape->table_shape[i][j])
				continue ;
			if (shape->col + j < 0
				|| shape->col + j >= TABLE_COL
				|| shape->row + i >= TABLE_ROW
				|| table[shape->row + i][shape->col + j])
				return false;
		}
	}
	return true;
}
