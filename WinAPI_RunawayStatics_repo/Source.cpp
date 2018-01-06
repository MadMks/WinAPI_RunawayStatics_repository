#include <windows.h>
#include "resource.h"
//using namespace std;

#define AROUND_THE_STATICS 25
#define SIZE_STATIC 25

// �������� ������� DlgProc.
BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

void MoveRight(HWND &hwnd, RECT &rcStatic, RECT &rcClient);
void MoveLeft(HWND &hwnd, RECT &rcStatic, RECT &rcClient);
void MoveDown(HWND &hwnd, RECT &rcStatic, RECT &rcClient);
void MoveUp(HWND &hwnd, RECT &rcStatic, RECT &rcClient);



int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpszCmdLine, int nCmdShow)
{

	MSG msg;	// ���������.
				// ������ ������� ���� ���������� �� ������ ������������ �������
	HWND hDialog = CreateDialog(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
	// ���������� ����	
	ShowWindow(hDialog, nCmdShow);


	//��������� ���� ��������� ���������
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}



BOOL CALLBACK DlgProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{

	static HWND hStatic;	// ���������� ���������� �������.
	static RECT rcStaticRect;	// ������ ���������� �������.
	static RECT rcClientRect;		// ���������� �������� ����.

	TCHAR szStr[MAX_PATH];	// ���������� ��� ������ ������ � ���������.	// TODO delete

	static int widthClientRect;
	static int heightClientRect;

	switch (uMessage)
	{

	case WM_CLOSE:
		// ��������� ����������� ������.
		DestroyWindow(hWnd); // ��������� ����.
		PostQuitMessage(0); // ������������� ���� ��������� ���������.
		return TRUE;

	case WM_INITDIALOG:

		GetClientRect(hWnd, &rcClientRect);

		rcStaticRect.left = 55;
		rcStaticRect.top = 55;
		rcStaticRect.right = rcStaticRect.left + SIZE_STATIC;
		rcStaticRect.bottom = rcStaticRect.top + SIZE_STATIC;

		// C������ ������.
		hStatic = CreateWindowEx(0, TEXT("STATIC"), 0,
			WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER | WS_EX_CLIENTEDGE,
			rcStaticRect.left, rcStaticRect.top,	// x, y
			rcStaticRect.right - rcStaticRect.left,	// ������.
			rcStaticRect.bottom - rcStaticRect.top,	// ������.
			hWnd, 0, GetModuleHandle(NULL), 0);

		// ������� � ��������� ���������� � �������.	// TODO delete
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

		// ���� ����� ��������� ���� ������ � �������.
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

			// �������� ��� ����������� � ������.

			// 1� �������.
			if (
				(LOWORD(lParam) < (rcClientRect.right / 2))
				&&
				(HIWORD(lParam) < (rcClientRect.bottom / 2))
				)
			{
				// ���� ������� � ����� ������.
				if (rcStaticRect.left < rcClientRect.left + 5)
				{
					// �� ����.
					MoveDown(hStatic, rcStaticRect, rcClientRect);
					MoveRight(hStatic, rcStaticRect, rcClientRect);
				}
				// ���� ������� � ������� ������.
				else if (rcStaticRect.top < rcClientRect.top + 5)	// TODO !
				{
					// �� ������.
					MoveRight(hStatic, rcStaticRect, rcClientRect);
					MoveDown(hStatic, rcStaticRect, rcClientRect);
				}
			}
			// 2� �������.
			else if (
				(LOWORD(lParam) >(rcClientRect.right / 2))
				&&
				(HIWORD(lParam) < (rcClientRect.bottom / 2))
				)
			{

				// ���� ������� � ������ ������.
				if (rcStaticRect.right > rcClientRect.right - 5)
				{
					// �� ����.
					MoveDown(hStatic, rcStaticRect, rcClientRect);
					MoveLeft(hStatic, rcStaticRect, rcClientRect);
				}
				// ���� ������� � ������� ������.
				else if (rcStaticRect.top < rcClientRect.top + 5)	// TODO !
				{
					// �� �����.
					MoveLeft(hStatic, rcStaticRect, rcClientRect);
					MoveDown(hStatic, rcStaticRect, rcClientRect);
				}




			}
			// 3� �������.
			else if (
				(LOWORD(lParam) < (rcClientRect.right / 2))
				&&
				(HIWORD(lParam) > (rcClientRect.bottom / 2))
				)
			{

				// ���� ������� � ����� ������.
				if (rcStaticRect.left < rcClientRect.left + 5)
				{
					// �� �����.
					MoveUp(hStatic, rcStaticRect, rcClientRect);
					MoveRight(hStatic, rcStaticRect, rcClientRect);
				}
				// ���� ������� � ������ ������.
				else if (rcStaticRect.bottom > rcClientRect.bottom - 5)	// TODO !
				{
					// �� ������.
					MoveRight(hStatic, rcStaticRect, rcClientRect);
					MoveUp(hStatic, rcStaticRect, rcClientRect);
				}

			}
			// 4� �������.
			else if (
				(LOWORD(lParam) > (rcClientRect.right / 2))
				&&
				(HIWORD(lParam) > (rcClientRect.bottom / 2))
				)
			{
				// ���� ������� � ������ ������.
				if (rcStaticRect.right > rcClientRect.right - 5)
				{
					// �� �����.
					MoveUp(hStatic, rcStaticRect, rcClientRect);
					MoveLeft(hStatic, rcStaticRect, rcClientRect);
				}
				// ���� ������� � ������ ������.
				else if (rcStaticRect.bottom > rcClientRect.bottom - 5)	// TODO !
				{
					// �� �����.
					MoveLeft(hStatic, rcStaticRect, rcClientRect);
					MoveUp(hStatic, rcStaticRect, rcClientRect);
				}
			}




			// �������� � ������ �������.
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
			// ����� ����� (���������)
			else if (
				(LOWORD(lParam) < rcStaticRect.left)
				&&
				(HIWORD(lParam) > rcStaticRect.bottom)
				)
			{
				MoveRight(hStatic, rcStaticRect, rcClientRect);
				MoveUp(hStatic, rcStaticRect, rcClientRect);
			}
			// ����� ������ (���������)
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

		// ������� � ��������� ���������� � �������.	// TODO delete
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