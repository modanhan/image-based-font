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

layout(location=3) uniform float harris_threshold=1.3;

uniform sampler2D TextureImage;

float g(float x){
	float t=3;
	return 1/sqrt(2*3.1415926*t*t)*exp(-x*x/2/t/t);
}

void main(void)
{
	FragmentColour.xyz=vec3(0);
	vec2 size=textureSize(TextureImage, 0).xy;
	
	vec3 c=texture(TextureImage, Textcoord).xyz;
	float ci=c.x+c.y+c.z;
	for(int u=-7;u<=7;u++){
		for(int v=-7;v<=7;v++){
			float w=g(u)*g(v);
			vec3 tc=texture(TextureImage, Textcoord+vec2(u/size.x,v/size.y)).xyz;
			float tci=tc.x+tc.y+tc.z;
			FragmentColour.xyz+=w*(tc-c)*(tc-c);
		}
	}
	FragmentColour.w=1;
	if(FragmentColour.x+FragmentColour.y+FragmentColour.z<harris_threshold){
		FragmentColour.xyz=vec3(0);
	}else{
		FragmentColour.xyz=vec3(1);
	}
}
