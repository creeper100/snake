#include "stdafx.h"
#include "GameWindowClass.h"
#include "message.h"

void GameWindowClass::init(HINSTANCE hInstan,int nCmdShow)
{
	hInst = hInstan;
	MyRegisterClass(hInst);
	if (!InitInstance(hInst, nCmdShow))
		exit(555);
}

ATOM GameWindowClass::MyRegisterClass(HINSTANCE hInstance) {
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = NULL;
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = L"w1";
	wcex.hIconSm = NULL;

	return RegisterClassExW(&wcex);
}
BOOL GameWindowClass::InitInstance(HINSTANCE hInstance,int cmd){
	hInst = hInstance;

	hWnd = CreateWindowW(L"w1", L"game", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd,cmd);
	UpdateWindow(hWnd);

	return TRUE;
}


