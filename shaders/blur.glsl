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
	float mask[5]=float[](0.113318,	0.236003,	0.30136,	0.236003,	0.113318);
	vec2 tsize=textureSize(TextureImage, 0);
	vec3 c=vec3(0,0,0);
	for(int i=0;i<5;i++)
		for(int j=0;j<5;j++)
			c+=texture(TextureImage, Textcoord+vec2((i-2)/tsize.x,(j-2)/tsize.y)).xyz*mask[i]*mask[j];
    // write colour output without modification
    FragmentColour = vec4(c, 1.0);
}
