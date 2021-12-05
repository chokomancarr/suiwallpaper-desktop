#include "reparent.hpp"
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

static BOOL findwinfunc(HWND tophandle, LPARAM topparamhandle) {
	HWND *workerw = (HWND *)topparamhandle;
	auto p = FindWindowEx(tophandle, 0, "SHELLDLL_DefView", "");
	if (p != 0)
	{
		*workerw = FindWindowEx(0, tophandle, "WorkerW", "");
	}
	return true;
}

void reparent(GLFWwindow *_window)
{
	auto w = FindWindowW(L"Progman", nullptr);
	SendMessageTimeout(w, (UINT)0x052c, 0, 0, SMTO_NORMAL, 1000, 0);
	HWND workerw;
	EnumWindows(findwinfunc, (LPARAM)&workerw);
	auto hwnd = glfwGetWin32Window(_window);
	SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) | WS_CHILD);
	SetParent(hwnd, workerw);
}
