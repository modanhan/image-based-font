#include "point_geometry.h"
#include <vector>
#include <iostream>
#include <queue>
#include <utility>
using namespace std;
using namespace glm;

typedef pair<int,int> ii;

namespace point_geometry{

	int width,height;

	graphics::MyGeometry geometry;
	graphics::MyShader shader;
	
	vector<vector<int>> g;
	
	void init(){
		InitializeShaders(&shader, "point_vertex.glsl", "point_fragment.glsl");
		InitializeGeometry(&geometry);
	}
	
	// fills in g
	void readTexture(GLuint texture){
		glBindTexture(GL_TEXTURE_2D, texture);
		glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width);
		glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &height);

		unsigned int pixels[width*height];
		glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
		glBindTexture(GL_TEXTURE_2D, 0);
		
		g.assign(width, vector<int>(height, -1));
		for(int i=0;i<width;i++){
			for(int j=0;j<height;j++){
				if(pixels[i*width+j]==0){
					g[i][j]=0;
				}else if(pixels[i*width+j]>16776960){
					g[i][j]=1;
				}else{
					g[i][j]=2;
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
					colors.push_back(vec3(1,1,1));
				}else if(g[i][j]==2){
					colors.push_back(vec3(0,0,1));
				}else continue;
				vec2 a((float)j/height,(float)i/width);
				a*=vec2(2);
				a-=vec2(1);
				a.y*=-1;
				vertices.push_back(a);
			}
		}
		geometry.elementCount = vertices.size();

		glBindBuffer(GL_ARRAY_BUFFER, geometry.vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(vec2), &vertices[0], GL_STATIC_DRAW);
		
		glBindBuffer(GL_ARRAY_BUFFER, geometry.colourBuffer);
		glBufferData(GL_ARRAY_BUFFER, colors.size()*sizeof(vec3), &colors[0], GL_STATIC_DRAW);
		
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	
	void render(){
 	   glUseProgram(shader.program);
 	   glBindVertexArray(geometry.vertexArray);
    
 	   glDrawArrays(GL_POINTS, 0, geometry.elementCount);

 	   glBindVertexArray(0);
 	   glUseProgram(0);
    
 	   graphics::CheckGLErrors();
	}
	
	// =========================================================================
	// bfs functions
	
	int DX[] = {1,1,0,-1,-1,-1,0,1};
	int DY[] = {0,1,1,1,0,-1,-1,-1};
	
	void merge_corner(){
		vector<vector<int>> v(width, vector<int>(height,0));
		
		for(int i=0;i<width;i++){
			for(int j=0;j<height;j++){
				if(v[i][j])continue;
				v[i][j]=1;
				if(g[i][j]!=1)continue;
				// run bfs
				queue<ii> q;
				q.push(ii(i,j));
				while(!q.empty()){
					ii t=q.front();q.pop();
					g[t.first][t.second]=0;
					v[t.first][t.second]=1;
					for(int k=0;k<8;k++){
						ii d(i+DX[k], j+DY[k]);
						if(d.first<0||d.first>=width||d.second<0||d.second>=height)continue;
						if(v[d.first][d.second])continue;
						if(g[d.first][d.second]!=1)continue;
						q.push(d);
					}
				}
				g[i][j]=1;
			}
		}
		generate();
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
}
