// ==========================================================================
// Vertex program for barebones GLFW boilerplate
//
// Author:  Sonny Chan, University of Calgary
// Date:    December 2015
// ==========================================================================
#version 410
#extension GL_ARB_explicit_uniform_location : enable

// interpolated colour received from vertex stage
in vec3 Colour;
in vec2 Textcoord;

// first output is mapped to the framebuffer's colour index by default
out vec4 FragmentColour;

layout(location=3) uniform float place_holder;

uniform sampler2D TextureImage;

void main(void)
{
	vec2 size=textureSize(TextureImage, 0).xy;
    
    vec3 h = texture(TextureImage, Textcoord+vec2(1/size.x,1/size.y)).xyz
    +texture(TextureImage, Textcoord+vec2(1/size.x,0)).xyz
    +texture(TextureImage, Textcoord+vec2(1/size.x,-1/size.y)).xyz
    -texture(TextureImage, Textcoord+vec2(-1/size.x,1/size.y)).xyz
    -texture(TextureImage, Textcoord+vec2(-1/size.x,0)).xyz
    -texture(TextureImage, Textcoord+vec2(-1/size.x,-1/size.y)).xyz;
    
    vec3 v = texture(TextureImage, Textcoord+vec2(1/size.x,1/size.y)).xyz
    +texture(TextureImage, Textcoord+vec2(0/size.x,1)).xyz
    +texture(TextureImage, Textcoord+vec2(1/size.x,-1/size.y)).xyz
    -texture(TextureImage, Textcoord+vec2(1/size.x,-1/size.y)).xyz
    -texture(TextureImage, Textcoord+vec2(0/size.x,-1)).xyz
    -texture(TextureImage, Textcoord+vec2(1/size.x,-1/size.y)).xyz;
    
    FragmentColour.xyz=abs(h)+abs(v);
    FragmentColour.w=1;
}
