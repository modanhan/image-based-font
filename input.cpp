#include "input.h"

#include "mode.h"
#include "shaders.h"

#include "point_geometry.h"
#include "curve_generation.h"

#include <iostream>
#include <algorithm>
using namespace std;

void print_debug(){
if(mode::mode<=CORNER_DETECT_MODE){
	cout<<"\e[A\e[A\e[A\e[A";
	cout<<"======================================\n";
	
	// spaces here are for writing over existing characters
 	cout<<"Edge detection threshold:\t"<<shaders::canny_threshold<<"                \n";
 	cout<<"Corner detection threshold:\t"<<shaders::harris_threshold<<"                \n";
	cout<<"======================================\n";
}
if(mode::mode==CORNER_CONNECT_MODE){
	cout<<"\e[A\e[A";
		cout<<"Max connect distance:\t"<<point_geometry::corner_connect_distance<<"                \n";
	cout<<"======================================\n";
}
if(mode::mode==CURVE_GEN_MODE){
	cout<<"\e[A\e[A";
		cout<<"Details:\t"<<1/curve_generation::detail<<"                \n";
	cout<<"======================================\n";
}
}

void init_input(){
	cout<<"\n\n\n\n\n";
	print_debug();
}

void print_mode_debug(){
	if(mode::mode==GENERATE_MODE){
		cout<<"Point geometry generated\n";
		cout<<"======================================\n";
	}
	if(mode::mode==CORNER_MERGE_MODE){
		cout<<"Merging corners\n";
		cout<<"======================================\n";
	}
	if(mode::mode==CORNER_CONNECT_MODE){
		cout<<"Connecting corners to edges\n";
		cout<<"Max connect distance:\t"<<point_geometry::corner_connect_distance<<"                \n";
		cout<<"======================================\n";
	}
	if(mode::mode==EDGE_REMOVE_MODE){
		cout<<"Removing edges\n";
		cout<<"======================================\n";
	}
	if(mode::mode==TARGET_GEN_MODE){
		cout<<"Generating target cuves, "<<point_geometry::target_curves.size()
		<<" curves detected\n";
		cout<<"======================================\n";
	}
	if(mode::mode==CURVE_GEN_MODE){
		cout<<"Details:\t"<<1/curve_generation::detail<<"                \n";
	cout<<"======================================\n";
}
}


// handles keyboard input events
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    if (key == GLFW_KEY_ENTER && action == GLFW_PRESS)
    	mode::advance();
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	if(mode::mode == EDGE_DETECT_MODE){
		shaders::canny_threshold += MODIFY_EPS*yoffset;
		shaders::canny_threshold = max(shaders::canny_threshold, 0.0f);
		print_debug();
	}
	if(mode::mode == CORNER_DETECT_MODE){
		shaders::harris_threshold += MODIFY_EPS*yoffset;
		shaders::harris_threshold = max(shaders::harris_threshold, 0.0f);
		print_debug();
	}
	if(mode::mode == CORNER_CONNECT_MODE){
		point_geometry::corner_connect_distance+=(yoffset>0)?1:-1;
		point_geometry::corner_connect_distance=max(min(point_geometry::corner_connect_distance,MAX_CONNECT_DISTANCE*MAX_CONNECT_DISTANCE),0);
		point_geometry::connect_corner();
		print_debug();
	}
	
	if(mode::mode == CURVE_GEN_MODE){
		curve_generation::detail+=yoffset*-0.02;
		
		curve_generation::detail=std::min(
		curve_generation::detail,10.0f);
		
		curve_generation::detail=std::max(
		curve_generation::detail,0.1f);
		
		curve_generation::generate();
		print_debug();
	}
}

namespace input{
	float mousex, mousey;
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos){
	input::mousex=xpos/window_width*2-1;
	input::mousey=-ypos/window_height*2+1;
}
