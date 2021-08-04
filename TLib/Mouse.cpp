#include "Mouse.h"

double Mouse::x = 0.0;
double Mouse::y = 0.0;

void Mouse::CursorPosCB(GLFWwindow* window, double _x, double _y)
{
	x = _x;
	x = _y;
}

void Mouse::MouseButtonCB(GLFWwindow* window, int button, int action, int mods)
{
}

void Mouse::MouseWheelCB(GLFWwindow* window, double dx, double dy)
{
}

double Mouse::GetMouseX()
{
	return x;
}

double Mouse::GetMouseY()
{
	return y;
}
