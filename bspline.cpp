#include "bspline.h"

float mix0(bspline* spline, int i, int n, float x){
	if((spline->knot[i+n]-spline->knot[i])==0)return 0;
	else return (x-spline->knot[i])/(spline->knot[i+n]-spline->knot[i]);
}

float mix1(bspline* spline, int i, int n, float x){
	if((spline->knot[i+n+1]-spline->knot[i+1])==0)return 0;
	else return (spline->knot[i+n+1]-x)/(spline->knot[i+n+1]-spline->knot[i+1]);
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
