#ifndef PT_H
# define PT_H

#include "tetris.h"

void copy_shape_on_table(char Buffer[TABLE_ROW][TABLE_COL]);
void print_table(const int final, const char Table[TABLE_ROW][TABLE_COL]);

#endif