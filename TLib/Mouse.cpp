#include "Mouse.h"

double Mouse::x = 0.0;
double Mouse::y = 0.0;

double Mouse::lastX = 0.0;
double Mouse::lastY = 0.0;

double Mouse::dx = 0.0;
double Mouse::dy = 0.0;

double Mouse::scrollDX = 0;
double Mouse::scrollDY = 0;

bool Mouse::first = true;

void Mouse::CursorPosCB(GLFWwindow* window, double _x, double _y)
{
    x = _x;
    y = _y;

    if (first) {
        lastX = _x;
        lastY = _y;
        first = false;
    }

    dx = _x - lastX;
    dy = lastY - _y;
    lastX = _x;
    lastY = _y;
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

double Mouse::GetDX()
{
	double n_dx = dx;
	dx = 0;

	return n_dx;
}

double Mouse::GetDY()
{
	double n_dy = dy;
	dy = 0;

	return n_dy;
}
