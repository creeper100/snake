#pragma once
class GameWindowClass{
protected:
	HINSTANCE hInst;
	HWND hWnd;
public:
	void init(HINSTANCE hInstan, int nCmdShow);
	ATOM  MyRegisterClass(HINSTANCE hInstance);
	BOOL  InitInstance(HINSTANCE,int);
	HINSTANCE getInst() { return hInst; }
};

