#include "tetris.h"

void delete_shape(t_shape shape) {
	if (shape.table_shape == NULL)
		return;
	for(int i = 0; i < shape.position_col; i++) {
		free(shape.table_shape[i]);
	}
	free(shape.table_shape);
}
