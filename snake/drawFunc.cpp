#include "stdafx.h"
void grid(int xkl, int ykl,HDC hDC,HWND hWnd) {
	RECT rec;
	GetClientRect(hWnd, &rec);
	int wight = rec.right - rec.left;
	int height = rec.top = rec.bottom;
	for (int i = 0;i <= xkl;i++) {
		MoveToEx(hDC, wight / xkl * i, 0, NULL);
		LineTo(hDC, wight / xkl * i, height);
	}
	for (int i = 0;i <= ykl;i++) {
		MoveToEx(hDC, 0, height / ykl * i, NULL);
		LineTo(hDC, wight, height / ykl * i);
	}
}