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
    vec4 fc0 = vec4(texture(TextureImage, Textcoord).xyz, 1.0);
    
    float dt=1.5;
    
    if(fc0.x+fc0.y+fc0.z<dt)fc0.xyz=vec3(0);
    {
    	vec4 tc=texture(TextureImage, Textcoord+vec2(1/dv.x,0/dv.y));
    	if(fc0.x+fc0.y+fc0.z<tc.x+tc.y+tc.z)fc0.xyz=vec3(0);
    }

    {
    	vec4 tc=texture(TextureImage, Textcoord+vec2(-1/dv.x,0/dv.y));
    	if(fc0.x+fc0.y+fc0.z<tc.x+tc.y+tc.z)fc0.xyz=vec3(0);
    }

    
    vec4 fc1 = vec4(texture(TextureImage, Textcoord).xyz, 0.0);
    if(fc1.x+fc1.y+fc1.z<dt)fc1.xyz=vec3(0);
    {
    	vec4 tc=texture(TextureImage, Textcoord+vec2(0/dv.x,1/dv.y));
    	if(fc1.x+fc1.y+fc1.z<tc.x+tc.y+tc.z)fc1.xyz=vec3(0);
    }
    {
    	vec4 tc=texture(TextureImage, Textcoord+vec2(0/dv.x,-1/dv.y));
    	if(fc1.x+fc1.y+fc1.z<tc.x+tc.y+tc.z)fc1.xyz=vec3(0);
    }

    if((fc0+fc1).x>0&&(fc0+fc1).y>0&&(fc0+fc1).z>0)FragmentColour=vec4(1);
    else FragmentColour=vec4(0,0,0,1);
  //  FragmentColour=fc0+fc1;
}
