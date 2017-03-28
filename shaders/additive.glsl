// ==========================================================================
// Vertex program for barebones GLFW boilerplate
//
// Author:  Sonny Chan, University of Calgary
// Date:    December 2015
// ==========================================================================
#version 410

// interpolated colour received from vertex stage
in vec3 Colour;
in vec2 Textcoord;

// first output is mapped to the framebuffer's colour index by default
out vec4 FragmentColour;

uniform sampler2D TextureImage;
uniform sampler2D TextureImage1;

void main(void)
{
    // write colour output without modification
    FragmentColour = vec4(texture(TextureImage, Textcoord).xyz, 1.0);
    FragmentColour.x=0;
    FragmentColour += vec4(texture(TextureImage1, Textcoord).xyz, 1.0);
    FragmentColour.w=0;
}
