#include "bspline.h"

using namespace std;
using namespace glm;

float mix0(bspline* spline, int i, int n, float x){
	if((spline->knot[i+n]-spline->knot[i])==0)return 0;
	else return (x-spline->knot[i])/(spline->knot[i+n]-spline->knot[i]);
}

float mix1(bspline* spline, int i, int n, float x){
	if((spline->knot[i+n+1]-spline->knot[i+1])==0)return 0;
	else return (spline->knot[i+n+1]-x)/(spline->knot[i+n+1]-spline->knot[i+1]);
}

// basis function fast
float Bfast(bspline* spline, int k, int n, float x){
	vector<float> v(n+1, 0);
	
	// v[i]=B(k+i,n,x)
	for(int i=0;i<=n;i++){
		if(spline->knot[i+k]<=x&&x<spline->knot[i+1+k])v[i]=1;
	}
	
	for(int j=1;j<=n;j++){
		vector<float> w(n+1,0);
		for(int i=0;i<n;i++){
			w[i]=mix0(spline, i+k,j,x)*v[i]+mix1(spline, i+k,j,x)*v[i+1];
		}
		v=w;
	}
	return v[0];
}

void initBSplineGeometry(bspline* spline){
    vector<vec2> vertices;
    vector<vec3> colors;
    int delta=0;
    for(float x=0;x<=1+spline->stepsize/2;x+=spline->stepsize){
    	vec2 p(0,0);
    	while(spline->knot[delta]<=x)delta++;
    	for(int i=delta-spline->degree-1;i<delta;i++){
    		p.x+=spline->point[i].x*Bfast(spline,i,spline->degree,x);
    		p.y+=spline->point[i].y*Bfast(spline,i,spline->degree,x);
    	}
    	vertices.push_back(p);
    }
    
    colors.assign(vertices.size(), vec3(1));
    
	spline->geometry.elementCount = vertices.size();

	glBindBuffer(GL_ARRAY_BUFFER, spline->geometry.vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(vec2), &vertices[0], GL_STATIC_DRAW);
		
	glBindBuffer(GL_ARRAY_BUFFER, spline->geometry.colourBuffer);
	glBufferData(GL_ARRAY_BUFFER, colors.size()*sizeof(vec3), &colors[0], GL_STATIC_DRAW);
		
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void initBSpine(bspline* spline){
	if(spline->point.size()<spline->degree+1){
		return;
	}
	
	spline->knot.resize(spline->degree+spline->point.size()+1);
	
	for(int i=0;i<spline->degree;i++){
		spline->knot[i]=0;
		spline->knot[spline->knot.size()-i-1]=1;
	}
	for(unsigned int i=spline->degree;i<=spline->point.size();i++){
		spline->knot[i]=(i-spline->degree)/(float)(spline->point.size()-spline->degree);
	}
}
