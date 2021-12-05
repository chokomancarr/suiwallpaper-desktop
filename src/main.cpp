#include "inc.hpp"
#include <chrono>
#include <GLFW/glfw3.h>
#include "reparent.hpp"

static void glDebugOutput(GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	const void* userParam);

static void OnWindowSizeChanged(GLFWwindow* window, int w, int h) {
	(void)window;
	glViewport(0, 0, w, h);
	Window::w = w;
	Window::h = h;
}

#define TIMENOW std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count

int main() {
	glfwInit();

	auto monitor = glfwGetPrimaryMonitor();
	glfwGetMonitorWorkarea(monitor, 0, 0, &Window::w, &Window::h);



	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_DECORATED, 0);
	glfwSwapInterval(0);
	auto& _window = Window::window = glfwCreateWindow(Window::w, Window::h, "test", NULL, NULL);
	glfwMakeContextCurrent(_window);
	glfwSetWindowSizeCallback(_window, OnWindowSizeChanged);

	glfwGetWindowSize(_window, &Window::w, &Window::h);

	glewExperimental = true;
	glewInit();

	reparent(_window);

	GLint flags; glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
	if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
	{
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(glDebugOutput, nullptr);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
	}

	glClearColor(GRAY, GRAY, GRAY, 0);
	glClearDepth(1);

	glEnable(GL_MULTISAMPLE);
	glDisable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_STENCIL_TEST);
	glDepthMask(false);
	glEnable(GL_LINE_SMOOTH);

	Texture turn1("res/turn1.png");
	Texture static1("res/static1.png");
	Texture turn2("res/turn2.png");
	Texture logo("res/logo.png");


	const auto t0 = TIMENOW();

	while (!glfwWindowShouldClose(_window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		const auto t = (TIMENOW() - t0) / 1000.f;

		const auto cx = 0.5f;
		const auto cy = -0.33f;

		Lines::DrawLongs(cx, cy, t * 0.005f, 2.4f);
		Lines::DrawCircle(cx, cy, 1.1f, 200);
		Lines::DrawCircle(cx, cy, 1.6f, 200);
		Lines::DrawCircle(cx, cy, 1.98f, 200);
		Lines::DrawCircle(cx, cy, 2.02f, 200);
		Lines::DrawCircle(cx, cy, 2.4f, 200);
		turn1.Draw(cx, cy, t * 0.03f, 1.4f);
		static1.Draw(cx, cy, 0, 1.4f);
		turn2.Draw(cx, cy, t * 0.03f, 1.4f);
		logo.Draw(-0.5f, 0, 0, 0.7f);

		glfwSwapBuffers(_window);
		glfwPollEvents();
	}
}

static void glDebugOutput(GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	const void* userParam)
{
	// ignore non-significant error/warning codes
	if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

	std::cout << "---------------" << std::endl;
	std::cout << "Debug message (" << id << "): " << message << std::endl;

	switch (source)
	{
	case GL_DEBUG_SOURCE_API:             std::cout << "Source: API"; break;
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   std::cout << "Source: Window System"; break;
	case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cout << "Source: Shader Compiler"; break;
	case GL_DEBUG_SOURCE_THIRD_PARTY:     std::cout << "Source: Third Party"; break;
	case GL_DEBUG_SOURCE_APPLICATION:     std::cout << "Source: Application"; break;
	case GL_DEBUG_SOURCE_OTHER:           std::cout << "Source: Other"; break;
	} std::cout << std::endl;

	switch (type)
	{
	case GL_DEBUG_TYPE_ERROR:               std::cout << "Type: Error"; break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cout << "Type: Deprecated Behaviour"; break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  std::cout << "Type: Undefined Behaviour"; break;
	case GL_DEBUG_TYPE_PORTABILITY:         std::cout << "Type: Portability"; break;
	case GL_DEBUG_TYPE_PERFORMANCE:         std::cout << "Type: Performance"; break;
	case GL_DEBUG_TYPE_MARKER:              std::cout << "Type: Marker"; break;
	case GL_DEBUG_TYPE_PUSH_GROUP:          std::cout << "Type: Push Group"; break;
	case GL_DEBUG_TYPE_POP_GROUP:           std::cout << "Type: Pop Group"; break;
	case GL_DEBUG_TYPE_OTHER:               std::cout << "Type: Other"; break;
	} std::cout << std::endl;

	switch (severity)
	{
	case GL_DEBUG_SEVERITY_HIGH:
#ifdef _WIN32
		__debugbreak();
#endif // _WIN32
		std::cout << "Severity: high"; break;
	case GL_DEBUG_SEVERITY_MEDIUM:
		std::cout << "Severity: medium"; break;
	case GL_DEBUG_SEVERITY_LOW:
		std::cout << "Severity: low"; break;
	case GL_DEBUG_SEVERITY_NOTIFICATION:
		std::cout << "Severity: notification"; break;
	} std::cout << std::endl;

	std::cout << std::endl;
}
