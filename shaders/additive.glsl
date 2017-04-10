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

uniform int extend=10;

void main(void)
{
	vec2 size=textureSize(TextureImage, 0).xy;
	
    FragmentColour = vec4(texture(TextureImage, Textcoord).xyz, 1.0);
    FragmentColour.xy=vec2(0);
    for(int i=-extend;i<=extend;i++) FragmentColour += vec4(texture(TextureImage1, Textcoord+vec2(i/size.x,0)).xyz, 1.0);
    for(int i=-extend;i<=extend;i++) FragmentColour += vec4(texture(TextureImage1, Textcoord+vec2(0,i/size.y)).xyz, 1.0);
    FragmentColour.w=0;
}
