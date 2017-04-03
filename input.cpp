#include "input.h"

#include "mode.h"
#include "shaders.h"

#include <iostream>
#include <algorithm>
using namespace std;

void init_input(){
	cout<<"\n\n\n\n\n";
	cout<<"\e[A\e[A\e[A\e[A";
	cout<<"======================================\n";
	// spaces here are for writing over existing characters
 	cout<<"Edge detection threshold:\t"<<shaders::canny_threshold<<"                \n";
 	cout<<"                \n";
	cout<<"======================================\n";
}

void print_debug(){
	cout<<"\e[A\e[A\e[A\e[A";
	cout<<"======================================\n";
	// spaces here are for writing over existing characters
 	cout<<"Edge detection threshold:\t"<<shaders::canny_threshold<<"                \n";
 	cout<<"                \n";
	cout<<"======================================\n";
}

// handles keyboard input events
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	if(mode::mode == EDGE_DETECT_MODE){
		shaders::canny_threshold += MODIFY_EPS*yoffset;
		shaders::canny_threshold = max(shaders::canny_threshold, 0.0f);
	}
	print_debug();
}
