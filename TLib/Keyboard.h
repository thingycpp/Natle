#ifndef KEYBOARD_H_INCLUDED
#define KEYBOARD_H_INCLUDED

#include "libs/glfw/include/GLFW/glfw3.h"

class Keyboard {
public:
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);


private:
	Keyboard() { }
	~Keyboard() { }

};

#endif