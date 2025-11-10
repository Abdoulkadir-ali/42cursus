#ifndef CONTROLS_H
# define CONTROLS_H

# include "vectors.h"

// Forward declare projection type (defined in projection.h)
typedef enum e_projection_type	t_projection_type;

/* ========== ROTATION STRUCTURE ========== */
// Stores rotation angles for 3D transformations
typedef struct s_rotation
{
	double	x;
	double	y;
	double	z;
}	t_rotation;

/* ========== COLOR SHIFT STRUCTURE ========== */
// Color modification values for RGB channels
typedef struct s_color_shift
{
	int	red;
	int	blue;
	int	green;
}	t_color_shift;

/* ========== CAMERA STRUCTURE ========== */
// Camera/view controls for 3D scene
typedef struct s_camera
{
	t_rotation			rotation;
	t_vec2d				offset;
	t_color_shift		color_shift;
	t_projection_type	projection;
	int					gui_style;
	double				scale;
	double				target_scale;
	double				move_speed;
	double				zoom_speed;
	double				dampening_threshold;
}	t_camera;

/* ========== MOUSE STATE ========== */
// Tracks mouse button press states and position
typedef struct s_mouse
{
	int	left_pressed;
	int	right_pressed;
	int	middle_pressed;
	int	last_x;
	int	last_y;
	int	middle_start_x;
	int	middle_start_y;
}	t_mouse;

/* ========== KEYBOARD STATE ========== */
// Tracks arrow key press states
typedef struct s_keys
{
	int	up;
	int	down;
	int	left;
	int	right;
	int	ctrl_left;
	int	ctrl_right;
}	t_keys;

/* ========== BUTTON CODE DEFINITIONS ========== */
// Keyboard button codes
typedef struct s_keyboard
{
	int	up_arrow;
	int	down_arrow;
	int	left_arrow;
	int	right_arrow;
	int	ctrl_left;
	int	ctrl_right;
	int	p;
	int	n;
	int	s;
	int	esc;
	int	r;
}	t_keyboard;

// Mouse button codes
typedef struct s_mouse_buttons
{
	int	left;
	int	right;
	int	middle;
	int	scroll_up;
	int	scroll_down;
}	t_mouse_buttons;

// Combined button codes
typedef struct s_buttons
{
	t_keyboard		keyboard;
	t_mouse_buttons	mouse;
}	t_buttons;

/* ========== CONTROL FUNCTIONS ========== */
// Forward declaration for zoom functions
typedef struct s_data	t_data;

// Initialize button/key code mappings
t_buttons	init_buttons(void);

// Zoom control functions
void		zoom_in(t_data *data);
void		zoom_out(t_data *data);
void		update_zoom(t_data *data);

// Camera adjustment functions
void		adjust_camera_to_map(t_data *data);

#endif
