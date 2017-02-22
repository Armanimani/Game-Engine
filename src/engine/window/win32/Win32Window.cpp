#include "Win32Window.h"
#include "../../userInput/rawInput/win32/Win32RawInput.h"

bool Win32Window::initialized = false;
HINSTANCE Win32Window::hInstance = nullptr;

void Win32Window::init()
{
	staticInit();
	hInstance = GetModuleHandle(nullptr);
}

void Win32Window::createWindow()
{
	init(); // removee later when engine class is created;
#ifdef _UNICODE
	std::wstring s;
	s.assign(settings.title.begin(), settings.title.end());
#else
	std::string s = title;
#endif
	LPTSTR titleStr = (LPTSTR(s.c_str()));

	hWnd = CreateWindow(TEXT("Win32WindowClass"), titleStr, WS_OVERLAPPEDWINDOW, settings.windowPosX, settings.windowPosY, settings.resolutionX, settings.resolutionY, nullptr, nullptr, hInstance, nullptr);
}

void Win32Window::showWindow()
{
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);
}

void Win32Window::killWinodw()
{
	if (!UnregisterClass(TEXT("Win32WindowClass"), hInstance))
	{
		MessageBox(NULL, TEXT("Unable not unregister the window class."), TEXT("Shutdown Error"), MB_OK | MB_ICONINFORMATION);
		hInstance = NULL;
	}
}

void Win32Window::staticInit()
{
	if (initialized)
	{
		return;
	}

	WNDCLASS wc;

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = Win32RawInput::windowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = TEXT("Win32WindowClass");

	if (!RegisterClass(&wc))
	{
		MessageBox(NULL, TEXT("Unable to register the window class"), TEXT("Error"), MB_OK | MB_ICONEXCLAMATION);
		exit(1);
	}

	initialized = true;
}
