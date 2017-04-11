#include "curve_generation.h"
#include "point_geometry.h"
#include <vector>
#include <iostream>

using namespace std;
using namespace glm;

namespace curve_generation{
	bspline bspline1;
	graphics::MyShader shader;
	
	
	vector<bspline> bsplines;

	int control_points=36;

	void init(){
		InitializeShaders(&shader, "point_vertex.glsl", "point_fragment.glsl");
	}
	
	void generate(){
		bsplines.resize(point_geometry::target_curves.size());
		for(int i=0;i<point_geometry::target_curves.size();i++){
			int tsize=point_geometry::target_curves[i].size()-1;
			vector<vec2> v;
			for(int j=0;j<control_points;j++){
				vec2 t=point_geometry::target_curves[i].at(tsize*j/(control_points-1));
				t.x/=window_width/2;
				t.y/=window_height/2;
				t.x-=1;
				t.y-=1;
				v.push_back(vec2(t.y,-t.x));
			}
			bsplines[i].point=v;
			initBSpine(&bsplines[i]);
		}
	}
	
	void render(){
		for(bspline spline:bsplines){

		glUseProgram(shader.program);
		glBindVertexArray(spline.geometry.vertexArray);

		glDrawArrays(GL_LINE_STRIP, 0, spline.geometry.elementCount);

		glBindVertexArray(0);
		glUseProgram(0);

		graphics::CheckGLErrors();
		}
	}
}
