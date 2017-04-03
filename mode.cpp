#include "mode.h"
#include "shaders.h"

namespace mode{
	int mode=0;
	void advance(){
		mode++;
		if(mode==MERGE_CORNER_MODE){
			shaders::corner_extend=0;
		}
	}
}
