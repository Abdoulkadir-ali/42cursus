#include "graphics.h"
#include "core.h"

t_graphics	init_graphics(t_window *window, t_camera *camera)
{
	t_graphics	g;

	g.window = window;
	g.camera = camera;
	g.mouse.left_pressed = 0;
	g.mouse.right_pressed = 0;
	g.mouse.middle_pressed = 0;
	g.mouse.last_x = 0;
	g.mouse.last_y = 0;
	g.mouse.middle_start_x = 0;
	g.mouse.middle_start_y = 0;
	g.keys.up = 0;
	g.keys.down = 0;
	g.keys.left = 0;
	g.keys.right = 0;
	g.keys.ctrl_left = 0;
	g.keys.ctrl_right = 0;
	g.keys.shift_left = 0;
	g.keys.shift_right = 0;
	g.keys.l = 0;
	g.keys.z = 0;
	g.keys.f = 0;
	g.keys.h = 0;
	g.keys.d = 0;
	g.map = NULL;
	init_map_list(&g.map_manager);
	g.map_config.line_thickness = 1;
	g.map_config.point_thickness = 0;
	g.map_config.line_color = 0xFFFFFF;
	g.map_config.point_color = 0xFFFFFF;
	g.map_config.style = 0;
	g.render_config.render_mode = RENDER_LINES;
	g.render_config.use_depth_culling = 0;
	g.render_config.fill_triangles = 1;
	g.render_config.lod_level = DEFAULT_LOD_LEVEL;
	g.frame_data.last_frame_time = 0;
	g.frame_data.frame_in_progress = 0;
	return (g);
}