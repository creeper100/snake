#pragma once


#include "stdafx.h"
class snake
{
	std::vector<int> tailx;
	std::vector<int> taily;
	
public:
	snake();
	~snake();
	int getx(int num);
	int gety(int num);
	int size();
	void goforward();
	void gobackward();
	void goleft();
	void goright();
};

