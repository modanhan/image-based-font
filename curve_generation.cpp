#include "curve_generation.h"
#include "point_geometry.h"
#include "bspline.h"
#include <vector>
#include <iostream>

using namespace std;
using namespace glm;

namespace curve_generation{
	bspline bspline1;
	graphics::MyShader shader;
	
	float detail=1;

	void generate_reverse_chaikin();
	
	vector<bspline> bsplines;

	int control_points=32;

	void init(){
		InitializeShaders(&shader, "point_vertex.glsl", "point_fragment.glsl");
	}
	
	void generate(){
		generate_reverse_chaikin();
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
		for(int i=2;i<v.size()-2;i+=2){
			ans.push_back((v[i]+v[i+1])/vec2(2));
		}
		ans.push_back(v.back());
		
		return ans;
	}
	
	void generate_reverse_chaikin(){
		bsplines.resize(point_geometry::target_curves.size());
		for(int i=0;i<point_geometry::target_curves.size();i++){
			vector<vec2> v=point_geometry::target_curves[i];
			int s=v.size();
			int subdivn=(int)(log(s*detail));
			for(int i=0;i<std::min(std::max(subdivn, 2), 9);i++)v=reverse_chaikin(v);
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
	
	// editing functions
	
	void remove_cp(glm::vec2 pos){
		int ansi=-1, ansj=-1;
		float d=1000;
		for(int i=0;i<bsplines.size();i++){
			// can't delete corners
			for(int j=1;j<bsplines[i].point.size()-1;j++){
				vec2 diff=bsplines[i].point[j]-pos;
				if(abs(diff.x)<CPSIZE&&abs(diff.y)<CPSIZE){
					if(abs(diff.x)+abs(diff.y)<d){
						d=abs(diff.x)+abs(diff.y);
						ansi=i;ansj=j;
					}
				}
			}
		}
		
		if(ansi!=-1&&ansj!=-1){
			vector<vec2> v;
			for(int j=0;j<bsplines[ansi].point.size();j++){
				if(j!=ansj){
					v.push_back(bsplines[ansi].point[j]);
				}
			}
			bsplines[ansi].point=v;
			initBSpine(&bsplines[ansi]);
		}
	}
}
