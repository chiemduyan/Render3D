// Render3dProject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <Windows.h>
#include <WinUser.h>
#include <windowsx.h>

#include <glm/glm.hpp>
using namespace glm;


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HWND configWindow;
GLFWwindow* window;

HWND okButton;
HWND openglRadioButton;
HWND directxRadioButton;
bool isOpenNewWindow;

void InitializeOpenGL();
void CreateOpenGLWindow();

int main()
{
	std::cout << "Hello World!\n";

	const wchar_t CLASS_NAME[] = L"Config Window Class";

	WNDCLASS wc = { };

	wc.lpfnWndProc = WindowProc;
	wc.hInstance = NULL;
	wc.lpszClassName = CLASS_NAME;

	RegisterClass(&wc);

	configWindow = CreateWindowEx(0,
								  CLASS_NAME,
								  L"Configs",
								  WS_OVERLAPPEDWINDOW,
								  600, 337, 400, 225,
								  NULL,
								  NULL,
								  NULL,
								  NULL);

	okButton = CreateWindowEx(0,
							  L"BUTTON",
							  L"OK",
							  WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
							  150,
							  120,
							  100,
							  30,
							  configWindow,
							  (HMENU)1001,
							  (HINSTANCE)GetWindowLongPtr(configWindow, GWLP_HINSTANCE),
							  NULL);

	openglRadioButton = CreateWindowEx(0,
									   L"BUTTON",
									   L"OpenGL",
									   WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
									   50,
									   30,
									   200,
									   30,
									   configWindow,
									   (HMENU)1002,
									   (HINSTANCE)GetWindowLongPtr(configWindow, GWLP_HINSTANCE),
									   NULL);

	directxRadioButton = CreateWindowEx(0,
										   L"BUTTON",
										   L"Unsupported",
										   WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
										   50,
										   60,
										   200,
										   30,
										   configWindow,
										   (HMENU)1003,
										   (HINSTANCE)GetWindowLongPtr(configWindow, GWLP_HINSTANCE),
										   NULL);

	Button_SetCheck(openglRadioButton, true);

	if (configWindow != NULL)
	{
		std::cout << "Show Window\n";
		ShowWindow(configWindow, SW_SHOWDEFAULT);
	}

	isOpenNewWindow = false;

	MSG msg = { };
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	if (isOpenNewWindow)
	{
		glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

		do
		{
			glClear(GL_COLOR_BUFFER_BIT);

			glfwSwapBuffers(window);
			glfwPollEvents();

		} // Check if the ESC key was pressed or the window was closed
		while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
			   glfwWindowShouldClose(window) == 0);
	}
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);

			FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW));

			EndPaint(hwnd, &ps);
			break;
		}

		case WM_COMMAND:
		{
			if (LOWORD(wParam) == 1001)
			{
				if (Button_GetCheck(openglRadioButton))
				{
					InitializeOpenGL();
					CreateOpenGLWindow();

					printf("Button clicked\n");
					DestroyWindow(hwnd);

					isOpenNewWindow = true;
				}
				else
				{
					printf("Unsupported\n");
				}
			}
			break;
		}

		case WM_DESTROY:
		{
			PostQuitMessage(0);
			break;
		}

		default:
		{
			POINT cursorPosition;
			GetCursorPos(&cursorPosition);
			//std::cout << cursorPosition.x << " " << cursorPosition.y << "\n";
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
		}
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void InitializeOpenGL()
{
	// Initialise GLFW
	glewExperimental = true; // Needed for core profile
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return;
	}
}

void CreateOpenGLWindow()
{
	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL 

	// Open a window and create its OpenGL context

	window = glfwCreateWindow(1024, 768, "Tutorial 01", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(window); // Initialize GLEW
	glewExperimental = true; // Needed in core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return;
	}
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
