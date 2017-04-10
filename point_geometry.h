#pragma once

#include "graphics.h"


namespace point_geometry{

	extern graphics::MyGeometry point_geometry;
	
	void init();
	void render();
	void generate();
	void readTexture(GLuint texture);
	void merge_corner();
}
