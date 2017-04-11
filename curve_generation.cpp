#include "curve_generation.h"

using namespace glm;

namespace curve_generation{
	bspline bspline1;
	graphics::MyShader shader;

	int control_points=9;

	void init(){
		InitializeShaders(&shader, "point_vertex.glsl", "point_fragment.glsl");
	}
	
	void generate(){
		bspline1.point.push_back(vec2(0.5));
		bspline1.point.push_back(vec2(0.5,-0.5));
		bspline1.point.push_back(vec2(-0.5));
		bspline1.point.push_back(vec2(-0.5,0));
		bspline1.point.push_back(vec2(0,0.75));
		initBSpine(&bspline1);
	}
	
	void render(){
 	   glUseProgram(shader.program);
 	   glBindVertexArray(bspline1.geometry.vertexArray);
    
 	   glDrawArrays(GL_LINE_STRIP, 0, bspline1.geometry.elementCount);

 	   glBindVertexArray(0);
 	   glUseProgram(0);
    
 	   graphics::CheckGLErrors();
	}
}
