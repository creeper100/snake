#pragma once
class grid
{
private:
	bool **cells;
	int wight, height;
public:
	grid(int x=10,int y=10);
	~grid();
	bool getcell(int x, int y);
	void setcell(int x, int y, bool isactive);
};

