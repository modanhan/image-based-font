#include "curve_io.h"
#include <fstream>
#include <iostream>

#include "curve_generation.h"

using namespace std;

string curve_file_name;

void curve_io_init(char* c){
	curve_file_name="curves/";
	int i=0;
	while(1){
		if(c[i]=='.')break;
		curve_file_name+=c[i];
		i++;
	}
	curve_file_name+=".txt";
}

void read_curve(string name){
	ifstream file(name);
	int n;file>>n;
	curve_generation::bsplines.assign(n,bspline());
	for(int i=0;i<n;i++){
		int m;file>>m;
		while(m--){
			float x,y;file>>x>>y;
			curve_generation::bsplines[i].point.push_back(glm::vec2(x,y));
		}
		initBSpine(&curve_generation::bsplines[i]);
	}
	file.close();
	/*
	curve_generation::bsplines.assign(1,bspline());
	curve_generation::bsplines[0].point.push_back(glm::vec2(0,0));
	curve_generation::bsplines[0].point.push_back(glm::vec2(0,1));
	curve_generation::bsplines[0].point.push_back(glm::vec2(1,1));
	curve_generation::bsplines[0].point.push_back(glm::vec2(1,0));
	initBSpine(&curve_generation::bsplines[0]);*/
}

void write_curve(string name){
	ofstream file(name);
	file<<curve_generation::bsplines.size()<<endl;
	for(auto a:curve_generation::bsplines){
		file<<a.point.size();
		for(auto b:a.point){
			file<<" "<<b.x<<" "<<b.y;
		}
		file<<endl;
	}
	file.close();
	cout<<"File saved!"<<endl;
}
