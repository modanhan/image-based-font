#include "mode.h"
#include "shaders.h"
#include "input.h"
#include "point_geometry.h"

namespace mode{
	int mode=0;
	void advance(){
		mode++;
		if(mode==ERASE_DRAW_CORNER_MODE){
			shaders::corner_extend=0;
		}
		if(mode==GENERATE_MODE){
        	point_geometry::readTexture(graphics::extraFramebuffer.texture);
        	point_geometry::generate();
        }
		if(mode==CORNER_MERGE_MODE){
			
		}
		print_mode_debug();
	}
}
