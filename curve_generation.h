#pragma once

#include "bspline.h"
#include <vector>

namespace curve_generation{
	extern std::vector<bspline> bsplines;
	extern int control_points;
	extern float detail;

	void init();
	void generate();
	void render();
	
	void remove_cp(glm::vec2);
	void select_cp(glm::vec2);
	void move_cp(glm::vec2);
	void deselect();
}
