#include "curve_generation.h"
#include "point_geometry.h"
#include <vector>
#include <iostream>

using namespace std;
using namespace glm;

namespace curve_generation{
	bspline bspline1;
	graphics::MyShader shader;

	void generate_reverse_chaikin();
	
	vector<bspline> bsplines;

	int control_points=32;

	void init(){
		InitializeShaders(&shader, "point_vertex.glsl", "point_fragment.glsl");
	}
	
	void generate(){
		generate_reverse_chaikin();
		return;
	
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
	
	vector<vec2> reverse_chaikin(vector<vec2>& ov){
		if(ov.size()<6)return ov;
		vector<vec2> v=ov;
	
		// preprocess
		if(v.size()%2==0){
			v[v.size()-2]=v.back();
			v.pop_back();
		}
		
		v[1]=v[0]+(v[1]-v[0])*vec2(4.0/3.0);
		
		for(int i=2;i<v.size()-1;i+=2){
			vec2 vi=v[i];
			vec2 vi1=v[i+1];
			v[i]=vi+(vi-vi1)/vec2(2);
			v[i+1]=vi1+(vi1-vi)/vec2(2);
		}
		
		vector<vec2> ans;
		ans.push_back(v[0]);
		for(int i=1;i<v.size()-2;i+=2){
			ans.push_back((v[i]+v[i+1])/vec2(2));
		}
		ans.push_back(v.back());
		
		return ans;
	}
	
	void generate_reverse_chaikin(){
		bsplines.resize(point_geometry::target_curves.size());
		for(int i=0;i<point_geometry::target_curves.size();i++){
			vector<vec2> v=point_geometry::target_curves[i];
			for(int i=0;i<5;i++)v=reverse_chaikin(v);
			for(int i=0;i<v.size();i++){
				auto t=v[i];
				t.x/=window_width/2;
				t.y/=window_height/2;
				t.x-=1;
				t.y-=1;
				v[i].x=t.y;
				v[i].y=-t.x;
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
