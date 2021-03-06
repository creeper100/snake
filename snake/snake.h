#pragma once


#include "stdafx.h"
class snake
{
	std::vector<int> tailx;
	std::vector<int> taily;
	int turn = 0;
	int xgr;
	int ygr;
public:
	snake(int xkl,int ykl);
	~snake();
	int getx(int num);
	int gety(int num);
	int size();
	void goforward();
	void gobackward();
	void goleft();
	void goright();
	void go();
	void turnforward() { if (turn != 2) turn = 0; }
	void turnbackward() { if(turn!=0)turn = 2; }
	void turnleft() { if (turn != 1)turn = 3; }
	void turnright() { if (turn != 3) turn = 1; }
	void eat();
	bool hitTest();
};

