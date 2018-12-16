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
snake snk(xkl, ykl);
bool isgrid=1;
bool background = 1;
bool running = true;
int speed = 1000;
int rec=0;
void loadsettings();
void savesettings();
DWORD WINAPI ThreadFunc(LPVOID lpv);
BOOL CALLBACK changesizefunc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK changespeedfunc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	grid grd(xkl,ykl);
	PAINTSTRUCT ps;
	HDC hDC;
	static HMENU mnu;
	switch (message)
	{
	static HANDLE hreadA;
	case WM_CREATE:
		hreadA = CreateThread(NULL, 0, ThreadFunc, NULL, 0, NULL);
		mnu = GetMenu(hWnd);
		loadsettings();
		break;
		case WM_CHAR:
		switch (char(wParam)) {
		case 'w':
			if(running)
			snk.turnforward();			
		break;
		case 's':
			if (running)
			snk.turnbackward();
			break;
		case 'a':
			if (running)
			snk.turnleft();
			break;
		case 'd':
			if (running)
			snk.turnright();
			break;
		case 'p':
			running = !running;
			break;
		}
		if (running) {
			RECT rec;
			GetClientRect(hWnd, &rec);
			InvalidateRect(hWnd, &rec, true);
		}
		break;
		case WM_COMMAND: {
			int wmId = LOWORD(wParam);
			
			switch (wmId)
			{
			case ID_GRID: 
				isgrid = !isgrid;
				if (isgrid)
					CheckMenuItem(GetSubMenu(mnu,0), ID_GRID, MF_BYCOMMAND | MF_CHECKED);
				else
					CheckMenuItem(GetSubMenu(mnu, 0), ID_GRID, MF_BYCOMMAND | MF_UNCHECKED);
				break;
			case ID_BACKGROUND:
				background = !background;
				if (background)
					CheckMenuItem(GetSubMenu(mnu, 0), ID_BACKGROUND, MF_BYCOMMAND | MF_CHECKED);
				else
					CheckMenuItem(GetSubMenu(mnu, 0), ID_BACKGROUND, MF_BYCOMMAND | MF_UNCHECKED);
				break;
			case ID_SIZE:
				running = false;
				DialogBox(mwnd.getInst(), MAKEINTRESOURCE(IDD_CHSIZE), mwnd.gethwnd(), changesizefunc);
				//xkl++;
				//ykl++;
				grd = grid(xkl, ykl);
				snk = snake(xkl, ykl);
				running = true;
				break;
			case ID_SPEED:
				running = false;
				DialogBox(mwnd.getInst(), MAKEINTRESOURCE(IDD_CHSPEED), mwnd.gethwnd(), changespeedfunc);
				//xkl++;
				//ykl++;
				grd = grid(xkl, ykl);
				snk = snake(xkl, ykl);
				running = true;
				break;
			}
		}
	case WM_PAINT:
	{
		snk.go();
		if (snk.hitTest()) {
			running = false;
			std::wstring out;
			if (snk.size() > rec) {
				out = L"You new score: ";
				rec = snk.size();
			}
				else
					out = L"You score: ";
				wchar_t str[3];
				swprintf_s(str, L"%d", snk.size());
				for (unsigned int i = 0;i < sizeof(str)-1;i++)
					if(str[i]!=0)
					out.push_back(str[i]);
					else
						out.push_back(L' ');
				snk = snake(xkl, ykl);
			MessageBox(hWnd,(LPWSTR)out.c_str(), L"You lose", MB_OK);
			running = true;
		}
		hDC = BeginPaint(hWnd, &ps);
		SetBkMode(hDC, TRANSPARENT);
		RECT rec;
		GetClientRect(hWnd, &rec);
		HBRUSH hbr = CreateSolidBrush(RGB(0,0,0));
		HBRUSH hbr2;
		if(background)
		hbr2 = CreateSolidBrush(RGB((snk.size()*10)%256, (snk.getx(0)*(256/xkl))%256, (snk.gety(0)*(256 / xkl))%256));
		else
		hbr2 = CreateSolidBrush(RGB(255, 255, 255));
		FillRect(hDC, &rec, hbr2);
		for (int iks = 0;iks < xkl;iks++)
			for (int igr = 0;igr < xkl; igr++)
				grd.setcell(iks, igr, false);
		if (snk.getx(0) == xe && snk.gety(0) == ye) {
			snk.eat();
			xe = rand() % xkl;
			ye = rand() % ykl;
			for (int i = 0;i < snk.size();i++)
				if (xe == snk.getx(1) && ye == snk.gety(i)) {
					i = 0;
					xe = rand() % xkl;
					ye = rand() % ykl;
				}
		}
		grd.setcell(xe, ye, true);
		for (int i = 0;i < snk.size();i++) {
			grd.setcell(snk.getx(i), snk.gety(i), true);
		}
		double wight = rec.right - rec.left;
		double height = rec.top = rec.bottom;
		if(isgrid)
		cell(xkl, ykl, hDC, hWnd, wight, height);
		for (int iks=0;iks<xkl;iks++)
			for (int igr = 0;igr < xkl; igr++) {
				if (grd.getcell(iks, igr)) {
					RECT rst;
					rst.left = wight / xkl * (iks + 1);
					rst.top = height / ykl * (ykl - igr - 1);
					rst.right = wight / xkl * iks;
					rst.bottom = height / ykl * (ykl - igr);
					FillRect(hDC, &rst, hbr);
					}
			}
		
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		savesettings();
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
			Sleep(speed);
			if (running) {
			InvalidateRect(hWnd, &rec, true);
		}
	}
	return dwResult;
}
BOOL CALLBACK changesizefunc(HWND hDlg, UINT uMsg, WPARAM wParam,
	LPARAM lParam)
{
	switch (uMsg) {
	case WM_INITDIALOG:
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDOK:
			if (GetDlgItemInt(hDlg, IDC_XSIZE, NULL, false) > 0 && GetDlgItemInt(hDlg, IDC_XSIZE, NULL, false) > 0) {
			xkl = GetDlgItemInt(hDlg, IDC_XSIZE, NULL, false);
			ykl = GetDlgItemInt(hDlg, IDC_XSIZE, NULL, false);
		}
			EndDialog(hDlg, 0);
			return TRUE;
			break;
		case IDCANCEL:
			EndDialog(hDlg, 0);
			return TRUE;
			break;
		}
	}
	return FALSE;
}
BOOL CALLBACK changespeedfunc(HWND hDlg, UINT uMsg, WPARAM wParam,
	LPARAM lParam)
{
	switch (uMsg) {
	case WM_INITDIALOG:
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDOK:
			if (GetDlgItemInt(hDlg, IDC_SPEEDINP, NULL, false) > 0) {
				speed = GetDlgItemInt(hDlg, IDC_SPEEDINP, NULL, false);
			}
			EndDialog(hDlg, 0);
			return TRUE;
			break;
		case IDCANCEL:
			EndDialog(hDlg, 0);
			return TRUE;
			break;
		}
	}
	return FALSE;
}
void loadsettings() {
	std::ifstream fin;
	fin.open("snake.conf");
	fin >> xkl;
	fin >> ykl;
	fin >> speed;
	fin >> background;
	fin >> isgrid;
	fin >> rec;
}
void savesettings() {
	std::ofstream fout;
	fout.open("snake.conf");
	fout << xkl << std::endl << ykl << std::endl << speed << std::endl << background << std::endl << isgrid << std::endl<<rec<<std::endl;
}
