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
