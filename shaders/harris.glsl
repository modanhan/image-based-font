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
    
    vec3 ix=h*h;
    vec3 iy=v*v;
    vec3 ixy=h*v;
    
    FragmentColour.xyz=abs(ix*iy-ixy*ixy-0.6*(ix+iy)*(ix+iy));
    FragmentColour.w=1;
}
