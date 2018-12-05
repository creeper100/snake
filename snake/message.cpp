#pragma once
#include "stdafx.h"
#include "resource.h"
#include "GameWindowClass.h"
#include "message.h"
#include "drawFunc.h"
#include "grid.h"
#include "snake.h"

extern GameWindowClass mwnd;
int xkl = 30;
int ykl = 30;
int xe = rand() % xkl;
int ye = rand() % ykl;
grid grd;
snake snk;
DWORD WINAPI ThreadFunc(LPVOID lpv);
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hDC;
	switch (message)
	{
	static HANDLE hreadA;
	case WM_CREATE:
		hreadA = CreateThread(NULL, 0, ThreadFunc, NULL, 0, NULL);
		break;
		case WM_CHAR:
		switch (char(wParam)) {
		case 'w':
			snk.turnforward();			
		break;
		case 's':
			snk.turnbackward();
			break;
		case 'a':
			snk.turnleft();
			break;
		case 'd':
			snk.turnright();
			break;
		}
		RECT rec;
		GetClientRect(hWnd, &rec);
		InvalidateRect(hWnd, &rec, true);
		break;
	case WM_PAINT:
	{
		snk.go();
		if (snk.hitTest()) {
			std::wstring out=L"You score: ";
			wchar_t str[3];
			swprintf_s(str, L"%d", snk.size());
			for (unsigned int i = 0;i < sizeof(str)-1;i++)
				if(str[i]!=0)
				out.push_back(str[i]);
				else
					out.push_back(L' ');
			MessageBox(hWnd,(LPWSTR)out.c_str(), L"You lose", MB_OK);
			exit(snk.size());
		}
		hDC = BeginPaint(hWnd, &ps);
		SetBkMode(hDC, TRANSPARENT);
		for (int iks = 0;iks < xkl;iks++)
			for (int igr = 0;igr < xkl; igr++)
				grd.setcell(iks, igr, false);
		if (snk.getx(0) == xe && snk.gety(0) == ye) {
			snk.eat();
			xe = rand() % xkl;
			ye = rand() % ykl;
		}
		grd.setcell(xe, ye, true);
		for (int i = 0;i < snk.size();i++) {
			grd.setcell(snk.getx(i), snk.gety(i), true);
		}
		HBRUSH hbr = CreateSolidBrush(RGB(0, 0, 0));
		RECT rec;
		GetClientRect(hWnd, &rec);
		int wight = rec.right - rec.left;
		int height = rec.top = rec.bottom;
		cell(xkl, ykl, hDC, hWnd, wight, height);
		for (int iks=0;iks<xkl;iks++)
			for (int igr = 0;igr < xkl; igr++)
				if (grd.getcell(iks, igr)) {
					RECT rst;
					rst.left = wight / xkl * (iks + 1);
					rst.top = height / ykl * (ykl-igr-1);
					rst.right = wight / xkl * iks;
					rst.bottom = height / ykl * (ykl-igr);
					FillRect(hDC, &rst, hbr);
						
				}
		
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

DWORD WINAPI ThreadFunc(LPVOID lpv) {
	HWND hWnd = mwnd.gethwnd();
	DWORD dwResult = 0;
	RECT rec;
	GetClientRect(hWnd, &rec);
	while (1) {
		Sleep(1000);
		InvalidateRect(hWnd, &rec, true);
	}
	return dwResult;
}