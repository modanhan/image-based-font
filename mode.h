#pragma once

#define EDGE_DETECT_MODE 0
#define CORNER_DETECT_MODE 1
#define MERGE_CORNER_MODE 2

namespace mode{
	void advance();
	extern int mode;
}
