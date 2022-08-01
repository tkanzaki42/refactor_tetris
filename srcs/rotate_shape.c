#include "rotate_shape.h"
#include "create_random_shape.h"
#include "delete_shape.h"

void rotate_shape(t_shape shape) {
	t_shape temp = duplicate_shape(shape);
	for (int i = 0; i < shape.side_length ; ++i) {
		for (int j = 0, k = shape.side_length - 1; j < shape.side_length; ++j, --k){
			shape.table_shape[i][j] = temp.table_shape[k][i];
		}
	}
	delete_shape(temp);
}
