#include "cs.h"

Struct create_random_shape() {
	const Struct shape_list[7] = {
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

Struct create_shape(Struct shape){

	Struct new_shape = shape;
	char **copyshape = shape.array;
	new_shape.array = (char**)malloc(new_shape.width*sizeof(char*));
    int i, j;
    for(i = 0; i < new_shape.width; i++){
		new_shape.array[i] = (char*)malloc(new_shape.width*sizeof(char));
		for(j=0; j < new_shape.width; j++) {
			new_shape.array[i][j] = copyshape[i][j];
		}
    }
    return new_shape;
}
