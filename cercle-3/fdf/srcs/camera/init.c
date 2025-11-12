#include "camera.h"

t_camera	init_camera(void)
{
	t_camera	cam;

	cam.rotation.x = DEFAULT_CAMERA_ROTATION_X;
	cam.rotation.y = DEFAULT_CAMERA_ROTATION_Y;
	cam.rotation.z = DEFAULT_CAMERA_ROTATION_Z;
	cam.offset = create_vec2d(0.0, 0.0);
	cam.grid_center.x = 0.0;
	cam.grid_center.y = 0.0;
	cam.grid_center.z = 0.0;
	cam.color_shift.x = 0;
	cam.color_shift.y = 0;
	cam.color_shift.z = 0;
	cam.projection = PROJ_ISOMETRIC;
	cam.gui_style = GUI_STYLE_TRON_BLUE;
	cam.scale = 1.0;
	cam.target_scale = 1.0;
	cam.move_speed = 1.0;
	cam.zoom_speed = 1.0;
	cam.dampening_threshold = DEFAULT_DAMPENING_THRESHOLD;
	cam.pending_rot_x = 0.0;
	cam.pending_rot_y = 0.0;
	cam.z_scale = DEFAULT_Z_SCALE;
	cam.frustum_margin = DEFAULT_FRUSTUM_MARGIN;
	cam.spline_segments = DEFAULT_SPLINE_SEGMENTS;
	cam.use_z_divisor = 1;
	cam.invert_movement = 1;
	return (cam);
}