#ifndef MOUSE_H_INCLUDED
#define MOUSE_H_INCLUDED

#include "libs/glfw/include/GLFW/glfw3.h"

class Mouse {
private:
	static double x;
	static double y;

public:
	static void CursorPosCB(GLFWwindow* window, double _x, double _y);
	static void MouseButtonCB(GLFWwindow* window, int button, int action, int mods);
	static void MouseWheelCB(GLFWwindow* window, double dx, double dy);

	static double GetMouseX();
	static double GetMouseY();

};

#endif
