// Render3dProject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <Windows.h>
#include <iostream>
#include <WinUser.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int main()
{
    std::cout << "Hello World!\n"; 

	const wchar_t CLASS_NAME[] = L"Sample Window Class";

	WNDCLASS wc = { };

	wc.lpfnWndProc = WindowProc;
	wc.hInstance = NULL;
	wc.lpszClassName = CLASS_NAME;

	RegisterClass(&wc);

	HWND hwnd = CreateWindowEx(0,
		CLASS_NAME,
		L"Sample Window Name",
		WS_OVERLAPPEDWINDOW,
		600, 337, 400, 225,
		NULL,
		NULL,
		NULL,
		NULL);

	HWND hwndButton = CreateWindow(
		L"BUTTON",  // Predefined class; Unicode assumed 
		L"OK",      // Button text 
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
		150,         // x position 
		120,         // y position 
		100,        // Button width
		30,        // Button height
		hwnd,     // Parent window
		NULL,       // No menu.
		(HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
		NULL);      // Pointer not needed.

	if (hwnd != NULL)
	{
		std::cout << "ShowWindow\n";
		ShowWindow(hwnd, SW_SHOWDEFAULT);
	}

	MSG msg = { };
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;

		default:
			POINT cursorPosition;
			GetCursorPos(&cursorPosition);
			std::cout << cursorPosition.x << " " << cursorPosition.y << "\n";
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
