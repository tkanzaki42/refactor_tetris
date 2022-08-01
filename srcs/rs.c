#include "rs.h"
#include "cs.h"
#include "ds.h"

void FunctionRS(Struct shape){
	Struct temp = FunctionCS(shape);
	int i, j, k, width;
	width = shape.width;
	for(i = 0; i < width ; i++){
		for(j = 0, k = width-1; j < width ; j++, k--){
				shape.array[i][j] = temp.array[k][i];
		}
	}
	FunctionDS(temp);
}
