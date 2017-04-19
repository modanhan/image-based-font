#pragma once

#include "bspline.h"

namespace curve_generation{
	extern bspline bspline1;
	
	extern int control_points;
	extern float detail;

	void init();
	void generate();
	void render();
	
	void remove_cp(glm::vec2);
}
