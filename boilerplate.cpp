// ==========================================================================
// Barebones OpenGL Core Profile Boilerplate
//    using the GLFW windowing system (http://www.glfw.org)
//
// Loosely based on
//  - Chris Wellons' example (https://github.com/skeeto/opengl-demo) and
//  - Camilla Berglund's example (http://www.glfw.org/docs/latest/quick.html)
//
// Author:  Sonny Chan, University of Calgary
// Date:    December 2015
// ==========================================================================

#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include <algorithm>

#include "graphics.h"
#include "input.h"

using namespace std;
using namespace glm;
using namespace graphics;


// ==========================================================================
// PROGRAM ENTRY POINT

int main(int argc, char *argv[])
{   
	Magick::InitializeMagick(0);

    // initialize the GLFW windowing system
    if (!glfwInit()) {
        cout << "ERROR: GLFW failed to initilize, TERMINATING" << endl;
        return -1;
    }
    glfwSetErrorCallback(ErrorCallback);

    // attempt to create a window with an OpenGL 4.1 core profile context
    GLFWwindow *window = 0;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(1024, 1024, "Image Based Font Generator", 0, 0);
    if (!window) {
        cout << "Program failed to create GLFW window, TERMINATING" << endl;
        glfwTerminate();
        return -1;
    }

    // set keyboard callback function and make our context current (active)
    glfwSetKeyCallback(window, KeyCallback);
    glfwMakeContextCurrent(window);

    // query and print out information about our OpenGL environment
    QueryGLVersion();

    // call function to load and compile shader programs
    MyShader shader;
    if (!InitializeShaders(&shader, "fragment.glsl")) {
        cout << "Program could not initialize shaders, TERMINATING" << endl;
        return -1;
    }
    
    MyShader blurShader;
    if (!InitializeShaders(&blurShader, "shaders/blur.glsl")) {
        cout << "Program could not initialize shaders, TERMINATING" << endl;
        return -1;
    }
    
    MyShader cannyShader;
    if (!InitializeShaders(&cannyShader, "shaders/canny.glsl")) {
        cout << "Program could not initialize shaders, TERMINATING" << endl;
        return -1;
    }
    
    MyShader sobelShader;
    if (!InitializeShaders(&sobelShader, "shaders/sobel.glsl")) {
        cout << "Program could not initialize shaders, TERMINATING" << endl;
        return -1;
    }
    
    MyShader harrisShader;
    if (!InitializeShaders(&harrisShader, "shaders/harris.glsl")) {
        cout << "Program could not initialize shaders, TERMINATING" << endl;
        return -1;
    }
    
    MyShader additiveShader;
    if (!InitializeShaders(&additiveShader, "shaders/additive.glsl")) {
        cout << "Program could not initialize shaders, TERMINATING" << endl;
        return -1;
    }
    
    // call function to create and fill buffers with geometry data
    MyGeometry geometry;
    if (!InitializeGeometry(&geometry))
        cout << "Program failed to intialize geometry!" << endl;

	MyTexture texture;
	if (!InitializeTexture(&texture, "images/Block_-_M_79016763-075a-4d8f-a212-a1b57073b4eb_1024x1024.jpg"))
		cout << "Program failed to intialize texture!" << endl;
		
	MyFrameBuffer blurFramebuffer;
	if (!InitializeFrameBuffer(&blurFramebuffer, vec2(1024), 1))
		cout << "Program failed to intialize frame buffer!" << endl;
		
	MyFrameBuffer cannyFramebuffer;
	if (!InitializeFrameBuffer(&cannyFramebuffer, vec2(1024), 1))
		cout << "Program failed to intialize frame buffer!" << endl;
		
	MyFrameBuffer cannyStorageFramebuffer;
	if (!InitializeFrameBuffer(&cannyStorageFramebuffer, vec2(1024), 1))
		cout << "Program failed to intialize frame buffer!" << endl;
		
	MyFrameBuffer harrisStorageFramebuffer;
	if (!InitializeFrameBuffer(&harrisStorageFramebuffer, vec2(1024), 1))
		cout << "Program failed to intialize frame buffer!" << endl;
		
	MyFrameBuffer extraFramebuffer;
	if (!InitializeFrameBuffer(&extraFramebuffer, vec2(1024), 1))
		cout << "Program failed to intialize frame buffer!" << endl;
	
	MyFrameBuffer nullFramebuffer;

    // run an event-triggered main loop
    while (!glfwWindowShouldClose(window))
    {
        // call function to draw our scene
        Render(&geometry, &blurShader, texture.textureID, &blurFramebuffer);
        Render(&geometry, &sobelShader, blurFramebuffer.texture, &cannyFramebuffer);
        Render(&geometry, &cannyShader, cannyFramebuffer.texture, &cannyStorageFramebuffer);
        
        Render(&geometry, &harrisShader, texture.textureID, &harrisStorageFramebuffer);
        
        Render(&geometry, &additiveShader, cannyStorageFramebuffer.texture, harrisStorageFramebuffer.texture, &nullFramebuffer);
        
      //  Render(&geometry, &shader, extraFramebuffer.texture, &nullFramebuffer);

        // scene is rendered to the back buffer, so swap to front for display
        glfwSwapBuffers(window);

        // sleep until next event before drawing again
        glfwWaitEvents();
    }

    // clean up allocated resources before exit
    DestroyGeometry(&geometry);
    DestroyShaders(&shader);
    glfwDestroyWindow(window);
    glfwTerminate();

    cout << "Goodbye!" << endl;
    return 0;
}

// ==========================================================================
