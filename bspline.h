#pragma once

#include "graphics.h"
#include <vector>

#define CPSIZE 0.01

#define PI 3.1415926

struct bspline{
	int degree=2;
	float stepsize=0.002;
	std::vector<glm::vec2> point;
	std::vector<float> knot;
	
	graphics::MyGeometry geometry;
};

// init bspline with standard knot
void initBSpine(bspline*);
