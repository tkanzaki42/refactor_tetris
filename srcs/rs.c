#include "rs.h"
#include "cs.h"
#include "ds.h"

void rotate_shape(t_shape shape) {
	t_shape temp = create_shape(shape);
	for (int i = 0; i < shape.position_col ; ++i) {
		for (int j = 0, k = shape.position_col - 1; j < shape.position_col; ++j, --k){
			shape.table_shape[i][j] = temp.table_shape[k][i];
		}
	}
	delete_shape(temp);
}
