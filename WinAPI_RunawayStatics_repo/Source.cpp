#include <windows.h>
#include "resource.h"
//using namespace std;

#define AROUND_THE_STATICS 25
#define SIZE_STATIC 25

// Прототип функции DlgProc.
BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

void MoveRight(HWND &hwnd, RECT &rcStatic, RECT &rcClient);
void MoveLeft(HWND &hwnd, RECT &rcStatic, RECT &rcClient);
void MoveDown(HWND &hwnd, RECT &rcStatic, RECT &rcClient);
void MoveUp(HWND &hwnd, RECT &rcStatic, RECT &rcClient);



int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpszCmdLine, int nCmdShow)
{

	MSG msg;	// структура.
				// создаём главное окно приложения на основе немодального диалога
	HWND hDialog = CreateDialog(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
	// Отображаем окно	
	ShowWindow(hDialog, nCmdShow);


	//Запускаем цикл обработки сообщений
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}



BOOL CALLBACK DlgProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{

	static HWND hStatic;	// дескриптор созданного статика.
	static RECT rcStaticRect;	// храним координаты статика.
	static RECT rcClientRect;		// координаты главного окна.

	TCHAR szStr[MAX_PATH];	// переменная для вывода строки в заголовок.	// TODO delete

	static int widthClientRect;
	static int heightClientRect;

	switch (uMessage)
	{

	case WM_CLOSE:
		// Закрываем немодальный диалог.
		DestroyWindow(hWnd); // разрушаем окно.
		PostQuitMessage(0); // останавливаем цикл обработки сообщений.
		return TRUE;

	case WM_INITDIALOG:

		GetClientRect(hWnd, &rcClientRect);

		rcStaticRect.left = 55;
		rcStaticRect.top = 55;
		rcStaticRect.right = rcStaticRect.left + SIZE_STATIC;
		rcStaticRect.bottom = rcStaticRect.top + SIZE_STATIC;

		// Cоздаем статик.
		hStatic = CreateWindowEx(0, TEXT("STATIC"), 0,
			WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER | WS_EX_CLIENTEDGE,
			rcStaticRect.left, rcStaticRect.top,	// x, y
			rcStaticRect.right - rcStaticRect.left,	// ширина.
			rcStaticRect.bottom - rcStaticRect.top,	// высота.
			hWnd, 0, GetModuleHandle(NULL), 0);

		// Выведем в заголовок информацию о статике.	// TODO delete
		wsprintf(szStr, L"Width: %d, height: %d. X: %d, Y:%d.",
			rcStaticRect.right - rcStaticRect.left,
			rcStaticRect.bottom - rcStaticRect.top,
			rcStaticRect.left,
			rcStaticRect.top);
		SetWindowText(hWnd, szStr);

		return TRUE;

	case WM_MOUSEMOVE:

		//GetClientRect(hStatic, &rcStaticRect);
		widthClientRect = rcClientRect.right - rcClientRect.left;
		heightClientRect = rcClientRect.bottom - rcClientRect.top;

		// Если мышка указатель мыши близко к статику.
		if (
			(LOWORD(lParam) > rcStaticRect.left - 25)
			&&
			(LOWORD(lParam) < rcStaticRect.right + 25)
			&&
			(HIWORD(lParam) > rcStaticRect.top - 25)
			&&
			(HIWORD(lParam) < rcStaticRect.bottom + 25)
			)
		{

			// Движения при приближении к стенке.

			// 1й квадрат.
			if (
				(LOWORD(lParam) < (rcClientRect.right / 2))
				&&
				(HIWORD(lParam) < (rcClientRect.bottom / 2))
				)
			{
				// Если впритык к левой стенке.
				if (rcStaticRect.left < rcClientRect.left + 5)
				{
					// То вниз.
					MoveDown(hStatic, rcStaticRect, rcClientRect);
					MoveRight(hStatic, rcStaticRect, rcClientRect);
				}
				// Если впритык к верхней стенке.
				else if (rcStaticRect.top < rcClientRect.top + 5)	// TODO !
				{
					// То вправо.
					MoveRight(hStatic, rcStaticRect, rcClientRect);
					MoveDown(hStatic, rcStaticRect, rcClientRect);
				}
			}
			// 2й квадрат.
			else if (
				(LOWORD(lParam) >(rcClientRect.right / 2))
				&&
				(HIWORD(lParam) < (rcClientRect.bottom / 2))
				)
			{

				// Если впритык к правой стенке.
				if (rcStaticRect.right > rcClientRect.right - 5)
				{
					// То вниз.
					MoveDown(hStatic, rcStaticRect, rcClientRect);
					MoveLeft(hStatic, rcStaticRect, rcClientRect);
				}
				// Если впритык к верхней стенке.
				else if (rcStaticRect.top < rcClientRect.top + 5)	// TODO !
				{
					// То влево.
					MoveLeft(hStatic, rcStaticRect, rcClientRect);
					MoveDown(hStatic, rcStaticRect, rcClientRect);
				}




			}
			// 3й квадрат.
			else if (
				(LOWORD(lParam) < (rcClientRect.right / 2))
				&&
				(HIWORD(lParam) > (rcClientRect.bottom / 2))
				)
			{

				// Если впритык к левой стенке.
				if (rcStaticRect.left < rcClientRect.left + 5)
				{
					// То вверх.
					MoveUp(hStatic, rcStaticRect, rcClientRect);
					MoveRight(hStatic, rcStaticRect, rcClientRect);
				}
				// Если впритык к нижней стенке.
				else if (rcStaticRect.bottom > rcClientRect.bottom - 5)	// TODO !
				{
					// То вправо.
					MoveRight(hStatic, rcStaticRect, rcClientRect);
					MoveUp(hStatic, rcStaticRect, rcClientRect);
				}

			}
			// 4й квадрат.
			else if (
				(LOWORD(lParam) > (rcClientRect.right / 2))
				&&
				(HIWORD(lParam) > (rcClientRect.bottom / 2))
				)
			{
				// Если впритык к правой стенке.
				if (rcStaticRect.right > rcClientRect.right - 5)
				{
					// То вверх.
					MoveUp(hStatic, rcStaticRect, rcClientRect);
					MoveLeft(hStatic, rcStaticRect, rcClientRect);
				}
				// Если впритык к нижней стенке.
				else if (rcStaticRect.bottom > rcClientRect.bottom - 5)	// TODO !
				{
					// То влево.
					MoveLeft(hStatic, rcStaticRect, rcClientRect);
					MoveUp(hStatic, rcStaticRect, rcClientRect);
				}
			}




			// Движения в разные стороны.
			if (
				(LOWORD(lParam) > rcStaticRect.left - AROUND_THE_STATICS)
				&&
				(LOWORD(lParam) < (rcStaticRect.right - (SIZE_STATIC / 2)))
				&&
				(HIWORD(lParam) > rcStaticRect.top)
				&&
				(HIWORD(lParam) < rcStaticRect.bottom)
				)
			{
				MoveRight(hStatic, rcStaticRect, rcClientRect);
			}
			else if (
				(LOWORD(lParam) < rcStaticRect.right + AROUND_THE_STATICS)
				&&
				(LOWORD(lParam) > (rcStaticRect.left + (SIZE_STATIC / 2)))
				&&
				(HIWORD(lParam) > rcStaticRect.top)
				&&
				(HIWORD(lParam) < rcStaticRect.bottom)
				)
			{
				MoveLeft(hStatic, rcStaticRect, rcClientRect);
			}
			else if (
				(HIWORD(lParam) > rcStaticRect.top - AROUND_THE_STATICS)
				&&
				(HIWORD(lParam) < rcStaticRect.bottom - (SIZE_STATIC / 2))
				&&
				(LOWORD(lParam) > rcStaticRect.left)
				&&
				(LOWORD(lParam) < rcStaticRect.right)
				)
			{
				MoveDown(hStatic, rcStaticRect, rcClientRect);
			}
			else if (
				(HIWORD(lParam) < rcStaticRect.bottom + AROUND_THE_STATICS)
				&&
				(HIWORD(lParam) > rcStaticRect.top + (SIZE_STATIC / 2))
				&&
				(LOWORD(lParam) > rcStaticRect.left)
				&&
				(LOWORD(lParam) < rcStaticRect.right)
				)
			{
				MoveUp(hStatic, rcStaticRect, rcClientRect);
			}
			// Слева снизу (диагональ)
			else if (
				(LOWORD(lParam) < rcStaticRect.left)
				&&
				(HIWORD(lParam) > rcStaticRect.bottom)
				)
			{
				MoveRight(hStatic, rcStaticRect, rcClientRect);
				MoveUp(hStatic, rcStaticRect, rcClientRect);
			}
			// Слева сверху (диагональ)
			else if (
				(LOWORD(lParam) < rcStaticRect.left)
				&&
				(HIWORD(lParam) < rcStaticRect.top)
				)
			{
				MoveRight(hStatic, rcStaticRect, rcClientRect);
				MoveDown(hStatic, rcStaticRect, rcClientRect);
			}





		}

		// Выведем в заголовок информацию о статике.	// TODO delete
		wsprintf(szStr, L"Width: %d, height: %d. X: %d, Y:%d.",
			rcStaticRect.right - rcStaticRect.left,
			rcStaticRect.bottom - rcStaticRect.top,
			rcStaticRect.left,
			rcStaticRect.top);
		SetWindowText(hWnd, szStr);

		return TRUE;
	}
	return FALSE;
}



void MoveRight(HWND &hwnd, RECT &rcStatic, RECT &rcClient) {
	if (rcStatic.right < rcClient.right - 4)
	{
		++rcStatic.left;
		++rcStatic.right;
		MoveWindow(hwnd, rcStatic.left, rcStatic.top, SIZE_STATIC, SIZE_STATIC, true);
	}
}

void MoveLeft(HWND &hwnd, RECT &rcStatic, RECT &rcClient) {
	if (rcStatic.left > rcClient.left + 4)
	{
		--rcStatic.left;
		--rcStatic.right;
		MoveWindow(hwnd, rcStatic.left, rcStatic.top, SIZE_STATIC, SIZE_STATIC, true);
	}
}

void MoveDown(HWND &hwnd, RECT &rcStatic, RECT &rcClient) {
	if (rcStatic.bottom < rcClient.bottom - 4)
	{
		++rcStatic.top;
		++rcStatic.bottom;
		MoveWindow(hwnd, rcStatic.left, rcStatic.top, SIZE_STATIC, SIZE_STATIC, true);
	}
}

void MoveUp(HWND &hwnd, RECT &rcStatic, RECT &rcClient) {
	if (rcStatic.top > rcClient.top + 4)
	{
		--rcStatic.top;
		--rcStatic.bottom;
		MoveWindow(hwnd, rcStatic.left, rcStatic.top, SIZE_STATIC, SIZE_STATIC, true);
	}
}