#include "stdafx.h"
#include "grid.h"


grid::grid(int x, int y)
{
	cells = new bool*[x];
	for (int i = 0;i < x;i++)
		cells[i] = new bool[y];

	for (int i = 0;i < x;i++)
		for (int f = 0;f < y;f++)
			setcell(i, f,false);
}


grid::~grid()
{
	for (int i = 0;i < wight;i++)
		delete[] cells[i];
}
bool grid::getcell(int x, int y) {
	return cells[x][y];
}
void grid::setcell(int x, int y,bool isactive) {
	cells[x][y]= isactive;
}
