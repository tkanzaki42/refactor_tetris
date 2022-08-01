#include "cp.h"

int check_puttable(Struct shape, const char Table[TABLE_ROW][TABLE_COL]){
	char **array = shape.array;
	int i, j;
	for(i = 0; i < shape.width;i++) {
		for(j = 0; j < shape.width ;j++){
			if((shape.col+j < 0 || shape.col+j >= TABLE_COL || shape.row+i >= TABLE_ROW)){
				if(array[i][j])
					return F;
				
			}
			else if(Table[shape.row+i][shape.col+j] && array[i][j])
				return F;
		}
	}
	return T;
}
