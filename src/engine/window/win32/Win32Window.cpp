#include "Win32Window.h"
#include <windowsx.h>
#include <Windows.h>
#include "../WindowSettings.h"

#include "../../debug/Debug.h"
#include "../../userInput/inputEvent/InputHandlerCode.h"

bool Win32Window::initialized = false;
HINSTANCE Win32Window::hInstance = nullptr;
std::shared_ptr<InputMapper> Window::inMapper;
std::shared_ptr<WindowSettings> Window::settings;
std::shared_ptr<ViewportManager> Window::viewportManager;

void Win32Window::init()
{
	hInstance = GetModuleHandle(nullptr);
	staticInit();
}

void Win32Window::createWindow()
{
	DWORD dwStyle;
	DWORD dwExStyle;

	if (settings->fullscreen)
	{
		DEVMODE dmScreenSettings;
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = settings->windowResolution.x;
		dmScreenSettings.dmPelsHeight = settings->windowResolution.y;
		dmScreenSettings.dmBitsPerPel = settings->colorBits;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
		{
			if (MessageBox(NULL, TEXT("The requested fullscreen mode is not supported by your video card. Use windowed mode instead?"), TEXT("Fullscreen Error"), MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
			{
				settings->fullscreen = false;
			}
			else
			{
				MessageBox(NULL, TEXT("Program will now close"), TEXT("Error"), MB_OK | MB_ICONSTOP);
				return;
			}
		}
	}

	if (settings->fullscreen)
	{
		dwExStyle = WS_EX_APPWINDOW;
		dwStyle = WS_POPUP;
	}
	else
	{
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
		dwStyle = WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME;
	}

	RECT rect {0, 0, settings->windowResolution.x, settings->windowResolution.y};
	AdjustWindowRectEx(&rect, dwStyle, FALSE, dwExStyle);
	
#ifdef _UNICODE
	std::wstring s;
	s.assign(settings->title.begin(), settings->title.end());
#else
	std::string s = title;
#endif
	LPTSTR titleStr = (LPTSTR(s.c_str()));

	if (!(hWnd = CreateWindowEx(dwExStyle, TEXT("Win32WindowClass"), titleStr, dwStyle | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, settings->windowPosition.x, settings->windowPosition.y, rect.right - rect.left, rect.bottom - rect.top, nullptr, nullptr, hInstance, nullptr)))
	{
		killWindow();
		MessageBox(NULL, TEXT("Window creation failed."), TEXT("Error"), MB_OK | MB_ICONEXCLAMATION);
		return;
	}

	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		settings->colorBits,
		0, 0, 0, 0, 0, 0,
		settings->alphaBuffer,
		settings->shiftBit,
		settings->accumulationBuffer,
		0, 0, 0, 0,
		settings->depthBufferBits,
		settings->stencilBuffer,
		settings->auxiliaryBuffer,
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};

	if (!(hDC = GetDC(hWnd)))
	{
		killWindow();
		MessageBox(NULL, TEXT("Unable to create a GL device context."), TEXT("Error"), MB_OK | MB_ICONEXCLAMATION);
		return;
	}

	if (!(pixelFormat = ChoosePixelFormat(hDC, &pfd)))
	{
		killWindow();
		MessageBox(NULL, TEXT("Unable to find a suitable pixel format."), TEXT("Error"), MB_OK | MB_ICONEXCLAMATION);
		return;
	}

	if (!SetPixelFormat(hDC, pixelFormat, &pfd))
	{
		killWindow();
		MessageBox(NULL, TEXT("Unable to set the pixel format."), TEXT("Error"), MB_OK | MB_ICONEXCLAMATION);
		return;
	}

	if (!(hRC = wglCreateContext(hDC)))
	{
		killWindow();
		MessageBox(NULL, TEXT("Unable to create a GL rendering context."), TEXT("Error"), MB_OK | MB_ICONEXCLAMATION);
		return;
	}

	if (!wglMakeCurrent(hDC, hRC))
	{
		killWindow();
		MessageBox(NULL, TEXT("Unable to activate the GL rendering context."), TEXT("Error"), MB_OK | MB_ICONEXCLAMATION);
		return;
	}
}

void Win32Window::showWindow()
{
	if (!shown)
	{
		ShowWindow(hWnd, SW_SHOW);
		SetForegroundWindow(hWnd);
		UpdateWindow(hWnd);
		shown = true;
	}
}

void Win32Window::killWindow()
{
	shown = false;
	if (settings->fullscreen)
	{
		ChangeDisplaySettings(NULL, 0);
		ShowCursor(TRUE);
	}

	if (hRC)
	{
		if (!wglMakeCurrent(NULL, NULL))
		{
			MessageBox(NULL, TEXT("Unable to relesae HRC and DC."), TEXT("Shutdown Error"), MB_OK | MB_ICONINFORMATION);
		}
		if (!wglDeleteContext(hRC))
		{
			MessageBox(NULL, TEXT("Unable to release rendering context."), TEXT("Shutdown Error"), MB_OK | MB_ICONINFORMATION);
		}
		hRC = NULL;
	}

	if (hDC && !ReleaseDC(hWnd, hDC))
	{
		MessageBox(NULL, TEXT("Unable to release device context"), TEXT("Shutdown Error"), MB_OK | MB_ICONINFORMATION);
		hDC = NULL;
	}

	if (hWnd && !DestroyWindow(hWnd))
	{
		MessageBox(NULL, TEXT("Unable to release window handle."), TEXT("Shutdown Error"), MB_OK | MB_ICONINFORMATION);
		hWnd = NULL;
	}

	if (!UnregisterClass(TEXT("Win32WindowClass"), hInstance))
	{
		MessageBox(NULL, TEXT("Unable not unregister the window class."), TEXT("Shutdown Error"), MB_OK | MB_ICONINFORMATION);
		hInstance = NULL;
	}

}

void Win32Window::setWindowTitle(const std::string & title)
{
	settings->title = title;

#ifdef _UNICODE
	std::wstring s;
	s.assign(settings->title.begin(), settings->title.end());
#else
	std::string s = title;
#endif
	LPTSTR titleStr = (LPTSTR(s.c_str()));
	SetWindowText(hWnd, titleStr);
}

const std::shared_ptr<USIVec2> Win32Window::getMousePosition() const
{
	//WARNING: in case we want to accesss this function outside of this class we should be carefull that this window is the active window! 
	POINT pos;
	GetCursorPos(&pos);
	ScreenToClient(hWnd, &pos);

	std::shared_ptr<USIVec2> ret;
	if (pos.x >= 0 && pos.x <= settings->windowResolution.x &&
		pos.y >= 0 && pos.y <= settings->windowResolution.y)
	{
		ret = std::make_shared<USIVec2>((unsigned short)pos.x,(unsigned short)pos.y);
	}
	else
	{
		ret = std::make_shared<USIVec2>(0, 0);
	}

	return ret;
}

void Win32Window::showMouse(const bool & state)
{
	ShowCursor(state);
	settings->mouseVisible = state;
}

void Win32Window::lockMouse(const bool & state)
{
	// TODO NYI
	//cursorlock
	settings->mouseLocked = state;
}

void Win32Window::setWindowResolution(const GLuint & resX, const GLuint & resY)
{
	settings->windowResolution.x = resX;
	settings->windowResolution.y = resY;
	
	DWORD dwStyle;
	DWORD dwExStyle;

	if (settings->fullscreen)
	{
		dwExStyle = WS_EX_APPWINDOW;
		dwStyle = WS_POPUP;
	}
	else
	{
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
		dwStyle = WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME;
	}

	RECT rect {0, 0, settings->windowResolution.x, settings->windowResolution.y};
	AdjustWindowRectEx(&rect, dwStyle, FALSE, dwExStyle);
	SetWindowPos(hWnd, 0, settings->windowPosition.x, settings->windowPosition.y, rect.right - rect.left, rect.bottom - rect.top, 0);

}

const std::shared_ptr<USIVec2> Win32Window::getMonitorResolution()
{
	std::shared_ptr<USIVec2> ret;
	settings->monitorResolution.x = GetSystemMetrics(SM_CXSCREEN);
	settings->monitorResolution.y = GetSystemMetrics(SM_CYSCREEN);
	ret = std::make_shared<USIVec2>(settings->monitorResolution.x, settings->monitorResolution.y);
	return ret;
}

void Win32Window::setFullscreen(const bool state)
{
	settings->fullscreen = true;

}

void Win32Window::setFocus(const bool & state)
{
	if (state)
	{
		SetFocus(hWnd);
	}
}

const bool Win32Window::isFocused()
{
	return (GetFocus() == hWnd) ? true : false;
}

LRESULT CALLBACK Win32Window::windowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	InputEvent event;

	switch (msg)
	{
	case WM_LBUTTONDOWN:
	{
		event.type = InputEventType::MOUSE_DOWN;
		event.key = KeyCode::MOUSE_L;
		createMouseInputEvent(event, hwnd, wparam, lparam);
		inMapper->registerEvent(event, InputHandlerCode::onMouse_down);
		return 0;
	}
	case WM_LBUTTONUP:
	{
		event.type = InputEventType::MOUSE_UP;
		event.key = KeyCode::MOUSE_L;
		createMouseInputEvent(event, hwnd, wparam, lparam);
		inMapper->registerEvent(event, InputHandlerCode::onMouse_up);
		return 0;
	}
	case WM_RBUTTONDOWN:
	{
		event.type = InputEventType::MOUSE_DOWN;
		event.key = KeyCode::MOUSE_R;
		createMouseInputEvent(event, hwnd, wparam, lparam);
		inMapper->registerEvent(event, InputHandlerCode::onMouse_down);
		return 0;
	}
	case WM_RBUTTONUP:
	{
		event.type = InputEventType::MOUSE_UP;
		event.key = KeyCode::MOUSE_R;
		createMouseInputEvent(event, hwnd, wparam, lparam);
		inMapper->registerEvent(event, InputHandlerCode::onMouse_up);
		return 0;
	}
	case WM_MBUTTONDOWN:
	{
		event.type = InputEventType::MOUSE_DOWN;
		event.key = KeyCode::MOUSE_M;
		createMouseInputEvent(event, hwnd, wparam, lparam);
		inMapper->registerEvent(event, InputHandlerCode::onMouse_down);
		return 0;
	}
	case WM_MBUTTONUP:
	{
		event.type = InputEventType::MOUSE_UP;
		event.key = KeyCode::MOUSE_M;
		createMouseInputEvent(event, hwnd, wparam, lparam);
		inMapper->registerEvent(event, InputHandlerCode::onMouse_up);
		return 0;
	}
	case WM_MOUSEWHEEL:
	{
		event.type = InputEventType::MOUSE_WHEEL;
		event.key = KeyCode::MOUSE_W;
		createMouseInputEvent(event, hwnd, wparam, lparam);
		inMapper->registerEvent(event, InputHandlerCode::onMouse_wheel);
		return 0;
	}
	case WM_MOUSEMOVE:
	{
		event.type = InputEventType::NO_EVENT;
		event.key = KeyCode::NO_CODE;
		createMouseInputEvent(event, hwnd, wparam, lparam);
		inMapper->registerEvent(event, InputHandlerCode::onMouse_move);
		return 0;
	}
	case WM_KEYDOWN:
	{
		event.type = InputEventType::KEY_DOWN;
		createKeyInputEvent(event, hwnd, wparam, lparam);
		inMapper->registerEvent(event, InputHandlerCode::onKey_down);
		return 0;
	}
	case WM_KEYUP:
	{
		event.type = InputEventType::KEY_UP;
		createKeyInputEvent(event, hwnd, wparam, lparam);
		inMapper->registerEvent(event, InputHandlerCode::onKey_up);
		return 0;
	}
	case WM_CLOSE:
	{
		PostQuitMessage(0);
		return 0;
	}
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}
	case WM_SIZE:
	{
		settings->windowResolution.x = LOWORD(lparam);
		settings->windowResolution.y = HIWORD(lparam);
		if (viewportManager->getSize() != 0) viewportManager->updateLayout();
		return 0;
	}
	}
	return DefWindowProc(hwnd, msg, wparam, lparam);
}

void Win32Window::createKeyInputEvent(InputEvent & event, HWND hwnd, WPARAM wparam, LPARAM lparam)
{
	event.altDown = GetKeyState(VK_MENU) & 0x8000;
	event.ctrlDown = GetKeyState(VK_CONTROL) & 0x8000;
	event.shiftDown = GetKeyState(VK_SHIFT) & 0x8000;
	event.hwnd = hwnd;
	event.key = (KeyCode) wparam;
}

void Win32Window::createMouseInputEvent(InputEvent & event, HWND hwnd, WPARAM wparam, LPARAM lparam)
{
	event.altDown = GetKeyState(VK_MENU) & 0x8000;
	event.ctrlDown = GetKeyState(VK_CONTROL) & 0x8000;
	event.shiftDown = GetKeyState(VK_SHIFT) & 0x8000;
	event.hwnd = hwnd;

	event.mouseLDown = wparam & MK_LBUTTON;
	event.mouseRDown = wparam & MK_RBUTTON;
	event.mouseMDown = wparam & MK_MBUTTON;

	event.posX = GET_X_LPARAM(lparam);
	event.posY = GET_Y_LPARAM(lparam);
	event.wheelDelta = GET_WHEEL_DELTA_WPARAM(wparam);
}

void Win32Window::staticInit()
{
	if (initialized)
	{
		return;
	}

	WNDCLASS wc {0};

	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = Win32Window::windowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = NULL;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = TEXT("Win32WindowClass");

	if (!RegisterClass(&wc))
	{
		MessageBox(NULL, TEXT("Unable to register the window class"), TEXT("Error"), MB_OK | MB_ICONEXCLAMATION);
		exit(1);
	}

	initialized = true;
}
