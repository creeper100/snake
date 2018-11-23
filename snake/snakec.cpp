#include "stdafx.h"
#include "snake.h"
snake::snake()
{
	for (int i = 1;i < 6;i++) {
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