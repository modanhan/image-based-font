#pragma once

#include "graphics.h"

#define MODIFY_EPS 0.01

void init_input();

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
