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
	vec2 dv=textureSize(TextureImage, 0).xy;
	vec4 h=vec4(0), v=vec4(0);

    h -= texture(TextureImage, Textcoord+vec2(-1/dv.x,1/dv.y));
    h -= texture(TextureImage, Textcoord+vec2(-1/dv.x,0/dv.y));
    h -= texture(TextureImage, Textcoord+vec2(-1/dv.x,-1/dv.y));
    h += texture(TextureImage, Textcoord+vec2(1/dv.x,1/dv.y));
    h += texture(TextureImage, Textcoord+vec2(1/dv.x,0/dv.y));
    h += texture(TextureImage, Textcoord+vec2(1/dv.x,-1/dv.y));
    
    v -= texture(TextureImage, Textcoord+vec2(1/dv.x,1/dv.y));
    v -= texture(TextureImage, Textcoord+vec2(0/dv.x,1/dv.y));
    v -= texture(TextureImage, Textcoord+vec2(-1/dv.x,1/dv.y));
    v += texture(TextureImage, Textcoord+vec2(1/dv.x,-1/dv.y));
    v += texture(TextureImage, Textcoord+vec2(0/dv.x,-1/dv.y));
    v += texture(TextureImage, Textcoord+vec2(-1/dv.x,-1/dv.y));
    
    FragmentColour=vec4(0);
    FragmentColour+=(max(h, vec4(0))+max(-h, vec4(0)));
    FragmentColour+=(max(v, vec4(0))+max(-v, vec4(0)));
    FragmentColour.w=1;
}
