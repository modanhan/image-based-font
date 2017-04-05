#include "mode.h"
#include "shaders.h"

namespace mode{
	int mode=0;
	void advance(){
		mode++;
		if(mode==ERASE_DRAW_CORNER_MODE){
			shaders::corner_extend=0;
		}
	}
}
