#include "stdafx.h"
#include "snake.h"
snake::snake(int xkl,int ykl)
{
	xgr = xkl;
	ygr = ykl;
	for (int i = 5;i >=0;i--) {
		tailx.push_back(5);
		taily.push_back(i);
	}
}


snake::~snake()
{
	
}
int snake::getx(int num) {
	return tailx[num];
}
int snake::gety(int num) {
	return taily[num];
}
int snake::size() {
	return tailx.size();
}
void snake::goforward() {
	for (int i = tailx.size()-1;i >0;i--) {
		tailx[i] = tailx[i - 1];
		taily[i] = taily[i - 1];
	}
	taily[0]++;
}
void snake::gobackward() {

	for (int i = tailx.size() - 1;i > 0;i--) {
		tailx[i] = tailx[i - 1];
		taily[i] = taily[i - 1];
	}
	taily[0]--;
}
void snake::goleft() {

	for (int i = tailx.size() - 1;i > 0;i--) {
		tailx[i] = tailx[i - 1];
		taily[i] = taily[i - 1];
	}
	tailx[0]--;
}
void snake::goright() {

	for (int i = tailx.size() - 1;i > 0;i--) {
		tailx[i] = tailx[i - 1];
		taily[i] = taily[i - 1];
	}
	tailx[0]++;
}
void snake::go() {
	switch (turn) {
	case 0:
		goforward();
		break;
	case 1:
		goright();
		break;
	case 2:
		gobackward();
		break;
	case 3:
		goleft();
		break;
	}
}
void snake::eat() {
	switch (turn) {
	case 0:
		tailx.push_back(tailx[tailx.size() - 1]);
		taily.push_back(taily[taily.size() - 1] - 1);
		break;
	case 1:
		tailx.push_back(tailx[tailx.size() - 1] + 1);
		taily.push_back(taily[taily.size() - 1]);
		break;
	case 2:
		tailx.push_back(tailx[tailx.size() - 1]);
		taily.push_back(taily[taily.size() - 1] + 1);
		break;
	case 3:
		tailx.push_back(tailx[tailx.size() - 1] - 1);
		taily.push_back(taily[taily.size() - 1]);
		break;
	}
}
bool snake::hitTest() {
	if ((tailx[0] >= xgr) || (tailx[0] <0) || (taily[0]>= ygr) || (taily[0] < 0))
		return true;
	for (unsigned int i = 1;i < tailx.size();i++)
		for (unsigned int o= 1;o < taily.size();o++)
			if (tailx[0] == tailx[i] && taily[0] == taily[i])
				return true;
	return false;
}