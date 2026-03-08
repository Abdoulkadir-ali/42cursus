/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 20:29:45 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/06 20:29:45 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GUI_H
# define GUI_H

# define BUTTON_LEFT 1
# define BUTTON_MIDDLE 2
# define BUTTON_RIGHT 3
# define BUTTON_SCROLL_UP 4
# define BUTTON_SCROLL_DOWN 5

# define RENDER_W 2560
# define RENDER_H 1440
#
/* Auto-refresh configuration:
 * - Set `GUI_AUTOREFRESH_PHYSICS` to 1 to force a render every frame while
 *   physics simulation is enabled. Set to 0 to keep the legacy "dirty only"
 *   behavior.
 * - `GUI_AUTOREFRESH_SCALE` controls the downscale factor used during
 *   auto-refresh to keep rendering fast while simulating physics.
 */
# ifndef GUI_AUTOREFRESH_PHYSICS
#  define GUI_AUTOREFRESH_PHYSICS 1
# endif

# ifndef GUI_AUTOREFRESH_SCALE
#  define GUI_AUTOREFRESH_SCALE 5
# endif
# define PANEL_RADIUS 6
# define COL_BG 0x0A0A12
# define COL_ACCENT 0xE0A820
# define COL_FPS 0x20E060
# define COL_TEXT 0xD0D0D8
# define COL_HOVER 0x20C8D0
# define COL_BORDER 0x333340

/* 1. EXTERNAL DEPENDENCIES */
# include "core.h"
# include "debug.h"
# include "maths.h"

typedef enum e_widget_type
{
	WIDGET_LABEL,
	WIDGET_BUTTON,
	WIDGET_CHECKBOX,
	WIDGET_SLIDER,
	WIDGET_COLOR_PICKER,
	WIDGET_PANEL
} t_widget_type;

typedef struct s_widget t_widget;

typedef void (*t_widget_callback)(t_widget *widget, struct s_gui *gui);

struct s_widget
{
	t_widget_type type;
	t_vec2i pos;
	t_vec2i size;
	char *label;
	int value;
	int color;
	double dvalue;
	double dmin;
	double dmax;
	void *target;
	t_widget_callback on_click;
	t_widget_callback on_change;
	void *userdata;
	t_widget *next;
};

typedef struct s_hover_cache
{
	int x;
	int y;
	bool active;
	bool hit;
	long last_frame;
}	t_hover_cache;

extern t_hover_cache	g_hover;

t_widget	*widget_create(t_widget_type type, t_vec2i pos, t_vec2i size,
		const char *label);
void	widget_add(struct s_gui *gui, t_widget *widget);
void	widget_draw_all(struct s_gui *gui);
void	widget_handle_mouse(struct s_gui *gui, int button, t_vec2i mouse);
void	widget_handle_key(struct s_gui *gui, int keycode);
void	widget_init_default(t_gui *gui);

void	widget_draw_checkbox(struct s_gui *gui, t_widget *w);
void	widget_draw_slider(struct s_gui *gui, t_widget *w);

/* Editor state types (depends on t_widget being defined above) */
# include "editor.h"

/* 3. MODULE TYPES */
struct s_camera_controller
{
	t_camera *camera;
	t_transform transform;
	t_vec3 target_pos;
	t_rotator target_rot;
	double target_fov;
	double move_speed;
	double lerp_factor;
	bool moving_forward;
	bool moving_backward;
	bool moving_left;
	bool moving_right;
	bool moving_up;
	bool moving_down;
	bool zooming_in;
	bool zooming_out;
	bool mouse_left_pressed;
	bool mouse_middle_pressed;
	t_vec2i last_mouse;
};

struct s_render_ctx
{
	t_gui *gui;
	int next_tile_id;
	int total_tiles;
	int tiles_x;
	t_transform transform;
	double half_width;
	double half_height;
	double aspect_ratio;
	int step;
};

/* Sub-structs for t_gui */
typedef struct s_window
{
	void *mlx;
	void *win;
	void *img;
	char *addr;
	int bpp;
	int line_len;
	int endian;
	int width;
	int height;
	void *disp_img;
	char *disp_addr;
	int disp_bpp;
	int disp_line_len;
	int disp_endian;
	int disp_w;
	int disp_h;
} t_window;

typedef struct s_render_state
{
	int scale;
	bool dirty;
	bool force_fullres;
	double fps;
	long long last_time;
	bool last_dirty;
} t_render_state;

typedef struct s_input_ctxs
{
	int mouse_x;
	int mouse_y;
} t_input_ctx;

typedef struct s_map_entry
{
	char				*path;
	t_scene				*scene;
	t_scene_snap		 snap;
	struct s_map_entry	*next;
}	t_map_entry;

struct s_map
{
	t_map_entry	*head;
	t_map_entry	*current;
	int			 count;
};

typedef struct s_map_job
{
	pthread_t		tid;
	t_map_entry		*entry;
	bool			done;
	bool			active;
}	t_map_job;

typedef enum e_popup_step
{
	POPUP_NONE = 0,
	POPUP_SHAPE,
	POPUP_MESH_FMT,
	POPUP_MESH_PATH,
}	t_popup_step;

typedef enum e_mesh_fmt
{
	MESH_FMT_OBJ,
	MESH_FMT_GLB,
}	t_mesh_fmt;

typedef struct s_crud_ui
{
	t_popup_step	popup;
	t_mesh_fmt		mesh_fmt;
	char			path_buf[512];
	int				path_len;
	bool			path_error;
}	t_crud_ui;

struct s_gui
{
	t_window win;
	t_scene *scene;
	t_camera_controller cam_ctrl;
	t_render_state render;
	t_input_ctx input;
	t_map map_info;
	t_widget *widgets;
	bool physics_enabled;
	double phys_accumulator;
	double phys_fixed_dt;
	int phys_max_steps;
	int ambient_color;
	double ambient_intensity;
	t_selection		selection;
	t_inspector		inspector;
	t_scene_panel	scene_panel;
	t_slider_state	slider_state;
	t_map_job		map_job;
	t_crud_ui		crud;
};

typedef struct s_key_action
{
	int key;
	void (*press_action)(t_gui *gui);
	void (*release_action)(t_gui *gui);
} t_key_action;

typedef struct s_panel
{
	t_vec2i pos;
	t_vec2i size;
	int x;
	int y;
	int w;
	int h;
	int bg;
	int brd;
} t_panel;

typedef struct s_fill_params
{
	int x;
	int y;
	int color;
	char *pixel_addr;
} t_fill_params;

typedef struct s_tile_vars
{
	int id;
	int tx;
	int ty;
	t_vec2i pos;
	int x;
	int y;
	int bpp_step;
	int row_step;
	char *row_ptr;
	char *pixel_ptr;
} t_tile_vars;

/* 4. FUNCTION PROTOTYPES */

/* srcs/gui/init.c */
t_gui	*gui_init(t_scene *scene, void *mlx);
void	gui_destroy(t_gui *gui);

/* srcs/gui/loop.c */
void	gui_loop(t_gui *gui);

/* srcs/gui/render.c */
void	gui_render(t_gui *gui);
unsigned int	color_blend(unsigned int dst, int src, float alpha);
int	panel_color(t_panel panel, int i, int j);
void	render_tiles(t_render_ctx *ctx);
void	draw_panel(t_gui *gui, t_panel panel);
void	draw_ui_panels(t_gui *gui);
void	draw_ui_help(t_gui *gui, int *y);
void	draw_ui_status(t_gui *gui, int *y);
void	draw_ui_object(t_gui *gui);
void	draw_ui_text(t_gui *gui, t_camera_controller *ctrl);
bool	update_hover(t_gui *gui, t_render_ctx *ctx);
void	draw_hover_text(t_gui *gui);
void	process_pixel(t_render_ctx *ctx, t_vec2i pos, char *pixel_addr);
void	make_camera_ray(t_render_ctx *ctx, double x, double y, t_ray *ray);

/* srcs/gui/map/ */
void	gui_map_switcher_init(t_gui *gui);
void	gui_next_map(t_gui *gui);
void	gui_prev_map(t_gui *gui);
bool	map_load_entry(t_gui *gui, t_map_entry *entry);
void	map_load_async(t_gui *gui, t_map_entry *entry);
void	reset_camera_view(t_gui *gui);
void	map_manager_destroy(t_gui *gui);

/* srcs/gui/input/ */
int	key_press(int keycode, t_gui *gui);
int	key_release(int keycode, t_gui *gui);
int	mouse_click(int button, t_vec2i mouse, t_gui *gui);
int	mouse_release(int button, t_vec2i mouse, t_gui *gui);
int	mouse_motion(t_vec2i mouse, t_gui *gui);
int (*mouse_click_hook(void))(int, int, int, t_gui *);
int (*mouse_release_hook(void))(int, int, int, t_gui *);
int (*mouse_motion_hook(void))(int, int, t_gui *);
void	gui_update_input(t_gui *gui);

/* srcs/gui/camera/ */
void	camera_move(t_camera *camera, t_vec3 direction, double speed);
void	camera_move_forward(t_camera *camera, double speed);
void	camera_move_backward(t_camera *camera, double speed);
void	camera_move_left(t_camera *camera, double speed);
void	camera_move_right(t_camera *camera, double speed);
void	camera_move_up(t_camera *camera, double speed);
void	camera_move_down(t_camera *camera, double speed);
void	camera_rotate_yaw(t_gui *gui, double delta_yaw);
void	camera_rotate_pitch(t_gui *gui, double delta_pitch);
void	get_forward(double pitch, double yaw, t_vec3 *out);
void	apply_movement(t_camera_controller *ctrl, t_vec3 fwd, t_vec3 right);
void	smooth_rotation(t_gui *gui, t_camera_controller *ctrl);
void	smooth_position(t_gui *gui, t_camera_controller *ctrl);
void	update_fov(t_gui *gui, t_camera_controller *ctrl);

void	move_forward_press(t_gui *gui);
void	move_forward_release(t_gui *gui);
void	move_backward_press(t_gui *gui);
void	move_backward_release(t_gui *gui);
void	move_left_press(t_gui *gui);
void	move_left_release(t_gui *gui);
void	move_right_press(t_gui *gui);
void	move_right_release(t_gui *gui);
void	move_up_press(t_gui *gui);
void	move_up_release(t_gui *gui);
void	move_down_press(t_gui *gui);
void	move_down_release(t_gui *gui);
void	zoom_in_press(t_gui *gui);
void	zoom_in_release(t_gui *gui);
void	zoom_out_press(t_gui *gui);
void	zoom_out_release(t_gui *gui);
void	speed_up_press(t_gui *gui);
void	speed_down_press(t_gui *gui);
void	map_next_press(t_gui *gui);
void	map_prev_press(t_gui *gui);
void	exit_press(t_gui *gui);
void	fullres_toggle(t_gui *gui);

void	fill_map_list(t_gui *gui);
void	set_current_entry(t_gui *gui);

/* 5. IMPLEMENTATION IMPORTS */
# include "raytracing.h"
# include "scene.h"

/* Window Management */
int	gui_window_resize(int width, int height, t_gui *gui);
int	gui_window_close(t_gui *gui);
void	upscale_image(t_gui *gui);

void	clamp_fov(double *fov);

#endif
