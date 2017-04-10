#include "graphics.h"

#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include <algorithm>
using namespace std;

#include <Magick++.h>
#include "shaders.h"

using namespace glm;

int window_width = 1024, window_height = 1024;

namespace graphics{




// --------------------------------------------------------------------------
// Rendering function that draws our scene to the frame buffer

void Render(MyGeometry *geometry, MyShader *shader, GLuint texture, MyFrameBuffer* framebuffer)
{
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer->fbo);
	glBindTexture(GL_TEXTURE_2D, framebuffer->texture);
	

    // bind our shader program and the vertex array object containing our
    // scene geometry, then tell OpenGL to draw our geometry
    glUseProgram(shader->program);
    glBindVertexArray(geometry->vertexArray);
    
    glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(glGetUniformLocation(shader->program, "TextureImage"), 0);
    
    auto u=glGetUniformLocation(shader->program, "canny_threshold");
    if(u!=-1){
    	glUniform1f(u, shaders::canny_threshold);
    }
    
    u=glGetUniformLocation(shader->program, "harris_threshold");
    if(u!=-1){
    	glUniform1f(u, shaders::harris_threshold);
    }
    
    glDrawArrays(GL_TRIANGLES, 0, geometry->elementCount);

    // reset state to default (no shader or geometry bound)
    glBindVertexArray(0);
    glUseProgram(0);
    
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // check for an report any OpenGL errors
    CheckGLErrors();
}

void Render(MyGeometry *geometry, MyShader *shader, GLuint texture, GLuint texture1, MyFrameBuffer* framebuffer)
{
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer->fbo);
	glBindTexture(GL_TEXTURE_2D, framebuffer->texture);
	

    // bind our shader program and the vertex array object containing our
    // scene geometry, then tell OpenGL to draw our geometry
    glUseProgram(shader->program);
    glBindVertexArray(geometry->vertexArray);
    
    glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(glGetUniformLocation(shader->program, "TextureImage"), 0);
    
    glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture1);
    glUniform1i(glGetUniformLocation(shader->program, "TextureImage1"), 1);
    
    auto u=glGetUniformLocation(shader->program, "extend");
    if(u!=-1){
    	glUniform1i(u, shaders::corner_extend);
    }
    
    glDrawArrays(GL_TRIANGLES, 0, geometry->elementCount);

    // reset state to default (no shader or geometry bound)
    glBindVertexArray(0);
    glUseProgram(0);
    
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // check for an report any OpenGL errors
    CheckGLErrors();
}



// ==========================================================================
// SUPPORT FUNCTION DEFINITIONS

// --------------------------------------------------------------------------
// OpenGL utility functions

void QueryGLVersion()
{
    // query opengl version and renderer information
    string version  = reinterpret_cast<const char *>(glGetString(GL_VERSION));
    string glslver  = reinterpret_cast<const char *>(glGetString(GL_SHADING_LANGUAGE_VERSION));
    string renderer = reinterpret_cast<const char *>(glGetString(GL_RENDERER));

    cout << "OpenGL [ " << version << " ] "
         << "with GLSL [ " << glslver << " ] "
         << "on renderer [ " << renderer << " ]" << endl;
}

bool CheckGLErrors()
{
    bool error = false;
    for (GLenum flag = glGetError(); flag != GL_NO_ERROR; flag = glGetError())
    {
        cout << "OpenGL ERROR:  ";
        switch (flag) {
        case GL_INVALID_ENUM:
            cout << "GL_INVALID_ENUM" << endl; break;
        case GL_INVALID_VALUE:
            cout << "GL_INVALID_VALUE" << endl; break;
        case GL_INVALID_OPERATION:
            cout << "GL_INVALID_OPERATION" << endl; break;
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            cout << "GL_INVALID_FRAMEBUFFER_OPERATION" << endl; break;
        case GL_OUT_OF_MEMORY:
            cout << "GL_OUT_OF_MEMORY" << endl; break;
        default:
            cout << "[unknown error code]" << endl;
        }
        error = true;
    }
    return error;
}


// --------------------------------------------------------------------------
// OpenGL shader support functions

// reads a text file with the given name into a string
string LoadSource(const string &filename)
{
    string source;

    ifstream input(filename.c_str());
    if (input) {
        copy(istreambuf_iterator<char>(input),
             istreambuf_iterator<char>(),
             back_inserter(source));
        input.close();
    }
    else {
        cout << "ERROR: Could not load shader source from file "
             << filename << endl;
    }

    return source;
}

// creates and returns a shader object compiled from the given source
GLuint CompileShader(GLenum shaderType, const string &source)
{
    // allocate shader object name
    GLuint shaderObject = glCreateShader(shaderType);

    // try compiling the source as a shader of the given type
    const GLchar *source_ptr = source.c_str();
    glShaderSource(shaderObject, 1, &source_ptr, 0);
    glCompileShader(shaderObject);

    // retrieve compile status
    GLint status;
    glGetShaderiv(shaderObject, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE)
    {
        GLint length;
        glGetShaderiv(shaderObject, GL_INFO_LOG_LENGTH, &length);
        string info(length, ' ');
        glGetShaderInfoLog(shaderObject, info.length(), &length, &info[0]);
        cout << "ERROR compiling shader:" << endl << endl;
        cout << source << endl;
        cout << info << endl;
    }

    return shaderObject;
}

// creates and returns a program object linked from vertex and fragment shaders
GLuint LinkProgram(GLuint vertexShader, GLuint fragmentShader)
{
    // allocate program object name
    GLuint programObject = glCreateProgram();

    // attach provided shader objects to this program
    if (vertexShader)   glAttachShader(programObject, vertexShader);
    if (fragmentShader) glAttachShader(programObject, fragmentShader);

    // try linking the program with given attachments
    glLinkProgram(programObject);

    // retrieve link status
    GLint status;
    glGetProgramiv(programObject, GL_LINK_STATUS, &status);
    if (status == GL_FALSE)
    {
        GLint length;
        glGetProgramiv(programObject, GL_INFO_LOG_LENGTH, &length);
        string info(length, ' ');
        glGetProgramInfoLog(programObject, info.length(), &length, &info[0]);
        cout << "ERROR linking shader program:" << endl;
        cout << info << endl;
    }

    return programObject;
}

bool InitializeShaders(MyShader *shader, const char* vertex, const char* fragment)
{
    // load shader source from files
    string vertexSource = LoadSource(vertex);
    string fragmentSource = LoadSource(fragment);
    if (vertexSource.empty() || fragmentSource.empty()) return false;

    // compile shader source into shader objects
    shader->vertex = CompileShader(GL_VERTEX_SHADER, vertexSource);
    shader->fragment = CompileShader(GL_FRAGMENT_SHADER, fragmentSource);

    // link shader program
    shader->program = LinkProgram(shader->vertex, shader->fragment);

    // check for OpenGL errors and return false if error occurred
    return !CheckGLErrors();
}

// load, compile, and link shaders, returning true if successful
bool InitializeShaders(MyShader *shader, const char* fragment)
{
	return InitializeShaders(shader, "vertex.glsl", fragment);
}

// deallocate shader-related objects
void DestroyShaders(MyShader *shader)
{
    // unbind any shader programs and destroy shader objects
    glUseProgram(0);
    glDeleteProgram(shader->program);
    glDeleteShader(shader->vertex);
    glDeleteShader(shader->fragment);
}

// create buffers and fill with geometry data, returning true if successful
bool InitializeGeometry(MyGeometry *geometry)
{
    // create an array buffer object for storing our vertices
    glGenBuffers(1, &geometry->vertexBuffer);

    // create another one for storing our colours
    glGenBuffers(1, &geometry->colourBuffer);
    
    glGenBuffers(1, &geometry->textcoordBuffer);

    // create a vertex array object encapsulating all our vertex attributes
    glGenVertexArrays(1, &geometry->vertexArray);
    glBindVertexArray(geometry->vertexArray);

    // associate the position array with the vertex array object
    glBindBuffer(GL_ARRAY_BUFFER, geometry->vertexBuffer);
    glVertexAttribPointer(VERTEX_LOCATION, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(VERTEX_LOCATION);

    // assocaite the colour array with the vertex array object
    glBindBuffer(GL_ARRAY_BUFFER, geometry->colourBuffer);
    glVertexAttribPointer(COLOUR_LOCATION, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(COLOUR_LOCATION);
    
    // assocaite the textcoord array with the vertex array object
    glBindBuffer(GL_ARRAY_BUFFER, geometry->textcoordBuffer);
    glVertexAttribPointer(TEXTCOORD_LOCATION, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(TEXTCOORD_LOCATION);

    // unbind our buffers, resetting to default state
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

	BufferGeometry(geometry);

    // check for OpenGL errors and return false if error occurred
    return !CheckGLErrors();
}

void BufferGeometry(MyGeometry *geometry){
	    // three vertex positions and assocated colours of a triangle
    const GLfloat vertices[][2] = {
        { -1., 1. },
        {  1., -1. },
        {  -1., -1. },
        { -1., 1. },
        {  1., 1. },
        {  1., -1. }
    };
    const GLfloat colours[][3] = {
        { 1.0, 1.0, 1.0 },
        { 1.0, 1.0, 1.0 },
        { 1.0, 1.0, 1.0 },
        { 1.0, 1.0, 1.0 },
        { 1.0, 1.0, 1.0 },
        { 1.0, 1.0, 1.0 }
    };
	const GLfloat textcoords[][2] = {
        { 0., 0. },
        {  1., 1. },
        {  0., 1. },
        { 0., 0. },
        {  1., 0. },
        {  1., 1. }
    };
    geometry->elementCount = 6;
    
    glBindBuffer(GL_ARRAY_BUFFER, geometry->vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ARRAY_BUFFER, geometry->colourBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colours), colours, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ARRAY_BUFFER, geometry->textcoordBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(textcoords), textcoords, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// deallocate geometry-related objects
void DestroyGeometry(MyGeometry *geometry)
{
    // unbind and destroy our vertex array object and associated buffers
    glBindVertexArray(0);
    glDeleteVertexArrays(1, &geometry->vertexArray);
    glDeleteBuffers(1, &geometry->vertexBuffer);
    glDeleteBuffers(1, &geometry->colourBuffer);
}

bool InitializeTexture(MyTexture *texture, const string &imageFileName)
{
    Magick::Image myImage;

    // try to read the provided image file
    try {
        myImage.read(imageFileName);
    }
    catch (Magick::Error &error) {
        cout << "Magick++ failed to read image " << imageFileName << endl;
        cout << "ERROR: " << error.what() << endl;
        return false;
    }

    // store the image width and height into the texture structure
    texture->width = myImage.columns();
    texture->height = myImage.rows();

    // create a Magick++ pixel cache from the image for direct access to data
    Magick::Pixels pixelCache(myImage);
    Magick::PixelPacket *pixels;
    pixels = pixelCache.get(0, 0, texture->width, texture->height);

    // determine the number of stored bytes per pixel channel in the cache
    GLenum channelDataType;
    switch (sizeof(Magick::Quantum)) {
        case 4:     channelDataType = GL_UNSIGNED_INT;      break;
        case 2:     channelDataType = GL_UNSIGNED_SHORT;    break;
        default:    channelDataType = GL_UNSIGNED_BYTE;
    }

    // create a texture name to associate our image data with
    if (!texture->textureID)
        glGenTextures(1, &texture->textureID);

    // bind the texture as a "rectangle" to access using image pixel coordinates
    glBindTexture(GL_TEXTURE_2D, texture->textureID);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // send image pixel data to OpenGL texture memory
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture->width, texture->height,
                 0, GL_BGRA, channelDataType, pixels);

    // unbind this texture
    glBindTexture(GL_TEXTURE_2D, 0);

    return !CheckGLErrors();
}
	
void DestroyTexture(MyTexture *texture)
{
	glBindTexture(texture->target, 0);
	glDeleteTextures(1, &texture->textureID);
}

bool InitializeFrameBuffer(MyFrameBuffer* frameBuffer, vec2 dimension, bool HDR) {
		glGenFramebuffers(1, &frameBuffer->fbo);
		glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer->fbo);

		glGenTextures(1, &frameBuffer->texture);
		glBindTexture(GL_TEXTURE_2D, frameBuffer->texture);

		glTexImage2D(GL_TEXTURE_2D, 0, (HDR) ? GL_RGBA16F : GL_RGBA, dimension.x, dimension.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, frameBuffer->texture, 0);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
			return false;
		}

		return true;
	}

// --------------------------------------------------------------------------
// GLFW callback functions

// reports GLFW errors
void ErrorCallback(int error, const char* description)
{
    cout << "GLFW ERROR " << error << ":" << endl;
    cout << description << endl;
}

}
