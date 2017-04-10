#include "point_geometry.h"
#include <vector>
#include <iostream>
using namespace std;
using namespace glm;

namespace point_geometry{

	int width,height;

	graphics::MyGeometry point_geometry;
	graphics::MyShader shader;
	
	vector<vector<int>> g;
	
	void init(){
	
	}
	
	// fills in g
	void readTexture(GLuint texture){
		glBindTexture(GL_TEXTURE_2D, texture);
		glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width);
		glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &height);

		GLubyte pixels[width*height*4];
		glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
		glBindTexture(GL_TEXTURE_2D, 0);
		
		g.assign(width, vector<int>(height, -1));
		for(int i=0;i<width;i++){
			for(int j=0;j<height;j++){
				if(pixels[i*width+j]==0){
					g[i][j]=0;
				}else if(pixels[i*width+j]>1<<7){
					g[i][j]=2;
				}else{
					g[i][j]=1;
				}
			}
		}
	}
	
	void generate(){
		vector<vec2> vertices;
		vector<vec3> colors;
		for(int i=0;i<width;i++){
			for(int j=0;j<height;j++){
				if(g[i][j]==1){
					vertices.push_back(vec2((float)i/width,(float)j/height));
					colors.push_back(vec3(0,0,1));
				}else if(g[i][j]==2){
					vertices.push_back(vec2((float)i/width,(float)j/height));
					colors.push_back(vec3(1,1,1));
				}
			}
		}
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
