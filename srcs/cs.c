#include "cs.h"

t_shape create_random_shape() {
	const t_shape shape_list[7] = {
		{(char *[]){(char []){0,1,1}, (char []){1,1,0}, (char []){0,0,0}}, 3, 0, 0},
		{(char *[]){(char []){1,1,0}, (char []){0,1,1}, (char []){0,0,0}}, 3, 0, 0},
		{(char *[]){(char []){0,1,0}, (char []){1,1,1}, (char []){0,0,0}}, 3, 0, 0},
		{(char *[]){(char []){0,0,1}, (char []){1,1,1}, (char []){0,0,0}}, 3, 0, 0},
		{(char *[]){(char []){1,0,0}, (char []){1,1,1}, (char []){0,0,0}}, 3, 0, 0},
		{(char *[]){(char []){1,1}, (char []){1,1}}, 2, 0, 0},
		{(char *[]){(char []){0,0,0,0}, (char []){1,1,1,1}, (char []){0,0,0,0}, (char []){0,0,0,0}},
			4, 0, 0}
	};

	return create_shape(shape_list[rand() % 7]);
}

t_shape create_shape(t_shape shape){

	t_shape new_shape = shape;
	char **copyshape = shape.table_shape;
	new_shape.table_shape = (char**)malloc(new_shape.position_col*sizeof(char*));
    int i, j;
    for(i = 0; i < new_shape.position_col; i++){
		new_shape.table_shape[i] = (char*)malloc(new_shape.position_col*sizeof(char));
		for(j=0; j < new_shape.position_col; j++) {
			new_shape.table_shape[i][j] = copyshape[i][j];
		}
    }
    return new_shape;
}
