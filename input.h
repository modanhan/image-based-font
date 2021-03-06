#pragma once

#include "graphics.h"

#define MODIFY_EPS 0.01
#define MAX_CONNECT_DISTANCE 5

void init_input();

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

void print_mode_debug();

namespace input{
	extern float mousex, mousey;
	extern float lmousex, lmousey;
	extern int ldown;
}
