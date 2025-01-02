#include <windows.h>

bool running = true;

LRESULT CALLBACK windowCall(HWND unnamedParam1, UINT uMsg, WPARAM unnamedParam3, LPARAM unnamedParam4) {
	LRESULT result = 0;
	switch (uMsg) {
	case WM_DESTROY: {
		running = false;
		PostQuitMessage(0);
	} break;
	default: {
		return DefWindowProc(unnamedParam1, uMsg, unnamedParam3, unnamedParam4);
		}
	}
	return result;
}

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	WNDCLASS windowClass{};


	windowClass.style = CS_HREDRAW | CS_VREDRAW;
	windowClass.lpszClassName = "Pong Game";
	windowClass.lpfnWndProc = windowCall;

	RegisterClass(&windowClass);

	const char* lpWindowName = "Pong Game Window";
	
	HWND window1 = CreateWindowExA(0, windowClass.lpszClassName,lpWindowName, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,  800, 600, nullptr, nullptr, hInstance, nullptr);

	if (window1 == nullptr) {
		MessageBoxA(nullptr, "Window creation failed", "Error", MB_ICONERROR);
		return -1;
	}

	ShowWindow(window1, nCmdShow);
	UpdateWindow(window1);

	while (running) {

		MSG message;
		while (PeekMessage(&message, window1, 0, 0, PM_REMOVE)) {
			TranslateMessage(&message);
			DispatchMessage(&message);
		}

	}
	return 0;
}


