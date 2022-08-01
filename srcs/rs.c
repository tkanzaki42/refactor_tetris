#include "rs.h"
#include "cs.h"
#include "ds.h"

void rotate_shape(Struct shape) {
	Struct temp = create_shape(shape);
	for (int i = 0; i < shape.width ; ++i) {
		for (int j = 0, k = shape.width - 1; j < shape.width; ++j, --k){
			shape.array[i][j] = temp.array[k][i];
		}
	}
	delete_shape(temp);
}
