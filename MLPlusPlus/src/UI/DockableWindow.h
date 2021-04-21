#pragma once

class DockableWindow
{
private:
	inline static class Window* s_Window;
public:
	static void init(class Window* window);
	static void destroy();

	static void begin();
	static void end();
};