#pragma once
#include "stdafx.h"
#include "snake.h"
#include "drawFunc.h"
extern GameWindowClass mwnd;
int xkl = 100;
int ykl = 100;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hDC;
	switch (message)
	{
	case WM_CREATE:
		
		break;
	case WM_PAINT:
	{
		
		hDC = BeginPaint(hWnd, &ps);
		SetBkMode(hDC, TRANSPARENT);
		grid(xkl, ykl, hDC, hWnd);
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