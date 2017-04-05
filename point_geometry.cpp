#include "point_geometry.h"

namespace point_geometry{

	graphics::MyGeometry point_geometry;
	graphics::MyShader shader;
	
	void generaet(){
	
	}
	
	void render(){
    glUseProgram(shader.program);
    glBindVertexArray(point_geometry.vertexArray);
    
    glDrawArrays(GL_POINTS, 0, point_geometry.elementCount);

    glBindVertexArray(0);
    glUseProgram(0);
    
    graphics::CheckGLErrors();
	}
}
