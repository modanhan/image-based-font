#include "mode.h"
#include "shaders.h"
#include "input.h"
#include "point_geometry.h"
#include "curve_generation.h"
#include "curve_io.h"

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
			point_geometry::merge_corner();
		}
		if(mode==CORNER_CONNECT_MODE){
			point_geometry::connect_corner();
		}
		if(mode==EDGE_PREVIEW_MODE){
			point_geometry::edge_preview();
		}
		if(mode==EDGE_REMOVE_MODE){
			// 2 pass for guaranteed excess edge removal
			point_geometry::edge_remove();
			point_geometry::edge_remove();
		}
		if(mode==TARGET_GEN_MODE){
			point_geometry::target_point_gen();
		}
		if(mode==CURVE_GEN_MODE){
			curve_generation::generate();
		}
		if(mode==EDIT_MODE){
		
		}
		if(mode>EDIT_MODE){
			write_curve(curve_file_name);
			mode=EDIT_MODE;
		}
		print_mode_debug();
	}
}
