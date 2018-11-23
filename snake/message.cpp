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
grid grd;
snake snk;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hDC;
	switch (message)
	{
	case WM_CREATE:
	
		break;
		case WM_CHAR:
		switch (char(wParam)) {
		case 'w':
			snk.goforward();			
		break;
		case 's':
			snk.gobackward();
			break;
		case 'a':
			snk.goleft();
			break;
		case 'd':
			snk.goright();
			break;
		}
		RECT rec;
		GetClientRect(hWnd, &rec);
		InvalidateRect(hWnd, &rec, true);
		break;
	case WM_PAINT:
	{
		
		hDC = BeginPaint(hWnd, &ps);
		SetBkMode(hDC, TRANSPARENT);
		for (int iks = 0;iks < xkl;iks++)
			for (int igr = 0;igr < xkl; igr++)
				grd.setcell(iks, igr, false);
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