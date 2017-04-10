#pragma once

#include "graphics.h"


namespace point_geometry{

	extern graphics::MyGeometry point_geometry;
	
	extern int corner_connect_distance;
	
	void init();
	void render();
	void generate();
	void readTexture(GLuint texture);
	void merge_corner();
	void connect_corner();
	void edge_remove();
}
