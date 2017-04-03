// ==========================================================================
// Vertex program for barebones GLFW boilerplate
//
// Author:  Sonny Chan, University of Calgary
// Date:    December 2015
// ==========================================================================
#version 410

#extension GL_ARB_explicit_uniform_location : enable
// location indices for these attributes correspond to those specified in the
// InitializeGeometry() function of the main program
layout(location = 0) in vec2 VertexPosition;
layout(location = 1) in vec3 VertexColour;
layout(location = 2) in vec2 VertexTextcoord;


// output to be interpolated between vertices and passed to the fragment stage
out vec3 Colour;
out vec2 Textcoord;

void main()
{
    // assign vertex position without modification
    gl_Position = vec4(VertexPosition, 0.0, 1.0);

    // assign output colour to be interpolated
    Colour = VertexColour;
    Textcoord = VertexTextcoord;
}
