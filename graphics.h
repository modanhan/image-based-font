#pragma once

#include <string>

// specify that we want the OpenGL core profile before including GLFW headers
#define GLFW_INCLUDE_GLCOREARB
#define GL_GLEXT_PROTOTYPES
#include <GLFW/glfw3.h>
#include <Magick++.h>
#include <glm/glm.hpp>

#define VERTEX_LOCATION 0
#define COLOUR_LOCATION 1
#define TEXTCOORD_LOCATION 2

namespace graphics{
// --------------------------------------------------------------------------
// OpenGL utility and support function prototypes

void QueryGLVersion();
bool CheckGLErrors();

std::string LoadSource(const std::string &filename);
GLuint CompileShader(GLenum shaderType, const std::string &source);
GLuint LinkProgram(GLuint vertexShader, GLuint fragmentShader);

// --------------------------------------------------------------------------
// Functions to set up OpenGL shader programs for rendering

struct MyShader
{
    // OpenGL names for vertex and fragment shaders, shader program
    GLuint  vertex;
    GLuint  fragment;
    GLuint  program;

    // initialize shader and program names to zero (OpenGL reserved value)
    MyShader() : vertex(0), fragment(0), program(0)
    {}
};

// --------------------------------------------------------------------------
// Functions to set up OpenGL buffers for storing geometry data

struct MyGeometry
{
    // OpenGL names for array buffer objects, vertex array object
    GLuint  vertexBuffer;
    GLuint  colourBuffer;
    GLuint  textcoordBuffer;
    GLuint  vertexArray;
    GLsizei elementCount;

    // initialize object names to zero (OpenGL reserved value)
    MyGeometry() : vertexBuffer(0), colourBuffer(0), vertexArray(0), elementCount(0)
    {}
};

struct MyTexture
	{
		GLuint textureID;
		GLuint target;
		int width;
		int height;

		// initialize object names to zero (OpenGL reserved value)
		MyTexture() : textureID(0), target(0), width(0), height(0)
		{}
	};
	
struct MyFrameBuffer {
	GLuint fbo;
	GLuint texture;
	GLuint rbo;

	MyFrameBuffer() :fbo(0), texture(0), rbo(0) {}
};

bool InitializeShaders(MyShader *shader, const char* fragment);
void DestroyShaders(MyShader *shader);
bool InitializeGeometry(MyGeometry *geometry);
void DestroyGeometry(MyGeometry *geometry);

bool InitializeFrameBuffer(MyFrameBuffer* frameBuffer, glm::vec2 dimension, bool HDR);

bool InitializeTexture(MyTexture *texture, const std::string &imageFileName);
void DestroyTexture(MyTexture *texture);

void Render(MyGeometry *geometry, MyShader *shader, GLuint, MyFrameBuffer*);

void ErrorCallback(int error, const char* description);
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void BufferGeometry(MyGeometry *geometry);
}
