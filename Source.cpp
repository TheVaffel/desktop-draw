
#include "Windows.h"

#include <iostream>

#include <time.h>
#include <random>

HWND workerw;

BOOL CALLBACK findWWorker(HWND top, LPARAM lparam) {
	HWND p = FindWindowEx(top, NULL,
		"SHELLDLL_DefView",
		NULL);
	
	if (p != NULL) {
		workerw = FindWindowEx(NULL, top,
				"WorkerW", NULL);
	}

	return TRUE;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	HWND progman = FindWindow("Progman", NULL);

	srand(time(NULL));
	
	SendMessageTimeout(progman, 0x052C,
		0, 0, SMTO_NORMAL,
		1000, NULL);

	EnumWindows(findWWorker, 0);


	HDC dc = GetDCEx(workerw, NULL, 0x403);

	int curr = rand();

	float th0 = 0.01f;
	float th1 = 0.0337f;
	float th2 = 0.00732f;
	float th3 = 0.02231f;
	float th4 = 0.013f;
	float th5 = 0.0354f;
	float th6 = 0.02544f;

	int screen_width = GetSystemMetrics(SM_CXSCREEN);
	int screen_height = GetSystemMetrics(SM_CYSCREEN);

	COLORREF bg_color = RGB(0, 0, 0);
	HBRUSH bg_brush = CreateSolidBrush(bg_color);
	HPEN bg_pen = CreatePen(PS_SOLID, 2, bg_color);

	SelectObject(dc, bg_brush);
	SelectObject(dc, bg_pen);

	Rectangle(dc, 0, 0, screen_width, screen_height);

	while (true) {
		
		int x0 = (int)(screen_width / 2 * (1 + sin(curr * th0)));
		int x1 = (int)(screen_width / 2 * (1 + cos(curr * th1)));

		int y0 = (int)(screen_height / 2 * (1 + sin(curr * th2)));
		int y1 = (int)(screen_height / 2 * (1 + cos(curr * th3)));

		COLORREF color = RGB((int)(128 * (1 + sin(curr * th4))),
							 (int)(128 * (1 + sin(curr * th5))),
							 (int)(128 * (1 + sin(curr * th6))));


		HPEN pen = CreatePen(PS_SOLID, 2, color);
		SelectObject(dc, pen);
		
		// HBRUSH brush = CreateSolidBrush(color);
		// SetDCBrushColor(dc, color);
		// SelectObject(dc, brush);


		MoveToEx(dc, x0, y0, NULL);
		LineTo(dc, x1, y1);

		curr++;

		if ((curr & ((1 << 10) - 1)) == 0) {
			// Wait a sec, so that we can appreciate the art
			
			Sleep(5 * 1000);

			SelectObject(dc, bg_brush);
			SelectObject(dc, bg_pen);
			Rectangle(dc, 0, 0, screen_width, screen_height);
		}
		Sleep(32);

	}

	ReleaseDC(workerw, dc);
}