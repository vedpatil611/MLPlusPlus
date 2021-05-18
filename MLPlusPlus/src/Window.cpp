#include "Window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdexcept>

Window::Window()
{
	if (!glfwInit())
		throw std::runtime_error("Failed to init glfw");

	m_Window = glfwCreateWindow(1920, 1080, "ML++", nullptr, nullptr);
	if (!m_Window)
	{
		glfwTerminate();
		throw std::runtime_error("Failed to create window");
	}
	
	glfwGetFramebufferSize(m_Window, &m_BufferWidth, &m_BufferHeight);
	glfwMakeContextCurrent(m_Window);
	glfwSetWindowUserPointer(m_Window, this);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		glfwTerminate();
		throw std::runtime_error("Failed to init open gl");
	}

	glfwSetKeyCallback(m_Window, &Window::keyCallback);
	glfwSetMouseButtonCallback(m_Window, &Window::mouseKeyCallback);
	glfwSetCursorPosCallback(m_Window, &Window::mousePositionCallback);
}

Window::~Window()
{
	glfwDestroyWindow(m_Window);
	glfwTerminate();
}

void Window::clearBuffer()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Window::pollInput()
{
	glfwPollEvents();
}

void Window::swapBuffer()
{
	glfwSwapBuffers(m_Window);
}

bool Window::shouldClose() const
{
	return glfwWindowShouldClose(m_Window);
}

void Window::setShouldClose(bool v)
{
	glfwSetWindowShouldClose(m_Window, v);
}

void Window::keyCallback(GLFWwindow* m_Window, int key, int scancode, int action, int mods)
{
	Window* window = static_cast<Window*>(glfwGetWindowUserPointer(m_Window));

	if (action == GLFW_PRESS)
		window->m_Keys[key] = true;
	if (action == GLFW_RELEASE)
		window->m_Keys[key] = false;
}

void Window::mouseKeyCallback(GLFWwindow* window, int key, int action, int mods)
{
}

void Window::mousePositionCallback(GLFWwindow* window, double xPos, double yPos)
{
}
