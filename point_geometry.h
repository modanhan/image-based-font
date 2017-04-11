#pragma once

#include "graphics.h"
#include <vector>

namespace point_geometry{

	extern graphics::MyGeometry point_geometry;
	extern std::vector<std::vector<glm::vec2>> target_curves;
	
	extern int corner_connect_distance;
	
	void init();
	void render();
	void generate();
	void readTexture(GLuint texture);
	void merge_corner();
	void connect_corner();
	void edge_remove();
	void edge_preview();
	void target_point_gen();
}
