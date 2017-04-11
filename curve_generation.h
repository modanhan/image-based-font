#pragma once

#include "bspline.h"

namespace curve_generation{
	extern bspline bspline1;
	
	extern int control_points;

	void init();
	void generate();
	void render();
}
