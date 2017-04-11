#pragma once

#define EDGE_DETECT_MODE 0
#define CORNER_DETECT_MODE 1
#define ERASE_DRAW_CORNER_MODE 2
#define GENERATE_MODE 3
#define CORNER_MERGE_MODE 4
#define CORNER_CONNECT_MODE 5
#define EDGE_PREVIEW_MODE 6
#define EDGE_REMOVE_MODE 7

namespace mode{
	void advance();
	extern int mode;
}
