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

uniform	float mask[7]=float[](
0.038735,	0.113085,	0.215007,	0.266346,	0.215007,	0.113085,	0.038735);

void main(void)
{
	FragmentColour.xyz=vec3(0);
	vec2 size=textureSize(TextureImage, 0).xy;
	
	vec3 c=texture(TextureImage, Textcoord).xyz;
	for(int u=-3;u<=3;u++){
		for(int v=-3;v<=3;v++){
			float w=mask[u+3]*mask[v+3];
			vec3 tc=texture(TextureImage, Textcoord+vec2(u/size.x,v/size.y)).xyz;
			FragmentColour.xyz+=w*(tc-c)*(tc-c);
		}
	}
	FragmentColour.w=1;
	if(FragmentColour.x+FragmentColour.y+FragmentColour.z<1.3){
		FragmentColour.xyz=vec3(0);
	}
	
}
