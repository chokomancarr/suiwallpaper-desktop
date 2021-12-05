#include "reparent.hpp"
#define GLFW_EXPOSE_NATIVE_X11
#include <GLFW/glfw3native.h>

enum {
	_NET_WM_STATE_ADD = 1,
};

// https://github.com/nshcat/phoenixpen_ng/blob/master/PhoenixPenNG/native/X11Wrapper.c
// https://specifications.freedesktop.org/wm-spec/wm-spec-latest.html

void reparent(GLFWwindow *_window)
{
	Display *disp = glfwGetX11Display();
	Window w = glfwGetX11Window(_window);
	Window wr = DefaultRootWindow(disp);

	Atom wmNetWmState = XInternAtom(disp, "_NET_WM_STATE", 1);
	Atom wmStateSkipPager = XInternAtom(disp, "_NET_WM_STATE_SKIP_PAGER", 1);
	Atom wmStateSkipTaskbar = XInternAtom(disp, "_NET_WM_STATE_SKIP_TASKBAR", 1);
	Atom wmStateSticky = XInternAtom(disp, "_NET_WM_STATE_STICKY", 1);
	Atom wmStateBelow = XInternAtom(disp, "_NET_WM_STATE_BELOW", 1);

	XEvent xev = {};
	// _NET_WM_STATE_BELOW indicates that the window should be below most windows
	xev.xclient.type = ClientMessage;
	xev.xclient.window = w;
	xev.xclient.message_type = wmNetWmState;
	xev.xclient.format = 32;
	xev.xclient.data.l[0] = _NET_WM_STATE_ADD;
	xev.xclient.data.l[1] = wmStateBelow;
	XSendEvent(disp, wr, False, SubstructureRedirectMask | SubstructureNotifyMask, &xev);
	// _NET_WM_STATE_STICKY indicates that the Window Manager SHOULD keep the window's position fixed on the screen, even when the virtual desktop scrolls.
	xev.xclient.type = ClientMessage;
	xev.xclient.window = w;
	xev.xclient.message_type = wmNetWmState;
	xev.xclient.format = 32;
	xev.xclient.data.l[0] = _NET_WM_STATE_ADD;
	xev.xclient.data.l[1] = wmStateSticky;
	XSendEvent(disp, wr, False, SubstructureRedirectMask | SubstructureNotifyMask, &xev);
	// _NET_WM_STATE_SKIP_PAGER indicates that the window should not be included on a Pager.
	xev.xclient.type = ClientMessage;
	xev.xclient.window = w;
	xev.xclient.message_type = wmNetWmState;
	xev.xclient.format = 32;
	xev.xclient.data.l[0] = _NET_WM_STATE_ADD;
	xev.xclient.data.l[1] = wmStateSkipPager;
	XSendEvent(disp, wr, False, SubstructureRedirectMask | SubstructureNotifyMask, &xev);
	// _NET_WM_STATE_SKIP_TASKBAR indicates that the window should not be included on a taskbar.
	xev.xclient.type = ClientMessage;
	xev.xclient.window = w;
	xev.xclient.message_type = wmNetWmState;
	xev.xclient.format = 32;
	xev.xclient.data.l[0] = _NET_WM_STATE_ADD;
	xev.xclient.data.l[1] = wmStateSkipTaskbar;
	XSendEvent(disp, wr, False, SubstructureRedirectMask | SubstructureNotifyMask, &xev);
	XFlush(disp);
}
