
#version 410

#extension GL_ARB_explicit_uniform_location : enable
layout(location = 0) in vec2 VertexPosition;
layout(location = 1) in vec3 VertexColour;


out vec3 Colour;
out vec2 Textcoord;

void main()
{
    gl_Position = vec4(VertexPosition, 0.0, 1.0);

    Colour = VertexColour;
}
