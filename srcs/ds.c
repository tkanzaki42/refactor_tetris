#include "tetris.h"

void delete_shape(t_shape shape){
    int i;
    for(i = 0; i < shape.position_col; i++){
		free(shape.table_shape[i]);
    }
    free(shape.table_shape);
}
