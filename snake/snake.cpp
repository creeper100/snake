#include "stdafx.h"
#include "resource.h"
#include "GameWindowClass.h"
#include "message.h"

GameWindowClass mwnd;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
		UNREFERENCED_PARAMETER(hPrevInstance);
		UNREFERENCED_PARAMETER(lpCmdLine);

		mwnd.init(hInstance, nCmdShow);

		MSG msg;

		while (GetMessage(&msg, nullptr, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

		}

		return (int)msg.wParam;
}

