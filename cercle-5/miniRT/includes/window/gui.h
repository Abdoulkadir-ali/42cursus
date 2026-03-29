/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 20:29:45 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/29 13:57:18 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GUI_H
# define GUI_H

/* --- CONSTANTS --- */
# define RENDER_W 1920
# define RENDER_H 1080
# define PANEL_RADIUS 4
# define GUI_AUTOREFRESH_PHYSICS 1
# define GUI_AUTOREFRESH_SCALE 2

/* Colors - Modern Dark Theme */
# define COL_ACCENT 0x3B82F6
# define COL_ACCENT_DIM 0x1E40AF
# define COL_BG 0x0F0F14
# define COL_BG_CARD 0x18181F
# define COL_BORDER 0x2A2A35
# define COL_FPS 0x22C55E
# define COL_HOVER 0x60A5FA
# define COL_PANEL_HDR 0x1F1F28
# define COL_POPUP_BG 0x1F1F28
# define COL_POPUP_BTN 0x2A2A38
# define COL_POPUP_BTN_CANCEL 0x7F1D1D
# define COL_POPUP_BTN_OK 0x14532D
# define COL_POPUP_DIM 0x0A0A10
# define COL_POPUP_ERR 0xEF4444
# define COL_POPUP_ERR_TEXT 0xFCA5A5
# define COL_ROW_HOVER 0x1E293B
# define COL_ROW_SEL 0x1E3A5F
# define COL_SELECTED 0x22C55E
# define COL_SLIDER_BG 0x1E1E28
# define COL_SLIDER_FG 0x3B82F6
# define COL_TEXT 0xE2E8F0
# define COL_TEXT_DIM 0x64748B
# define COL_HEADER 0x14141A
# define COL_SUCCESS 0x22C55E
# define COL_WARNING 0xF59E0B
# define COL_ERROR 0xEF4444

/* ── External dependencies ───────────────────────────────────────────────── */
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-function"
# pragma GCC diagnostic ignored "-Wunused-parameter"
# pragma GCC diagnostic ignored "-Wmissing-field-initializers"
# pragma GCC diagnostic ignored "-Wsign-compare"
# pragma GCC diagnostic ignored "-Wtype-limits"
# include "../packages/stb_image.h"
# pragma GCC diagnostic pop

# include "mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <zlib.h>

/* ── Engine dependencies ─────────────────────────────────────────────────── */
# include "engines.h"
# include "profiler.h"
#include "loader.h"

/* ── Forward declarations (editor types — full defs live in editor.h) ────── */
typedef struct s_selection		t_selection;
typedef struct s_inspector		t_inspector;
typedef struct s_scene_panel	t_scene_panel;
typedef struct s_slider_state	t_slider_state;
typedef struct s_crud_ui		t_crud_ui;
typedef struct s_hover_cache	t_hover_cache;
typedef struct s_scene_snap		t_scene_snap;

/* ── Forward declarations for self-referential structs ───────────────────── */
typedef struct s_widget			t_widget;
typedef struct s_gui			t_gui;
typedef struct s_map_entry		t_map_entry;

/* ── Enumerations ────────────────────────────────────────────────────────── */
typedef enum e_widget_type
{
	WIDGET_LABEL,
	WIDGET_BUTTON,
	WIDGET_CHECKBOX,
	WIDGET_SLIDER,
	WIDGET_COLOR_PICKER,
	WIDGET_PANEL,
}	t_widget_type;

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

/* ── GUI Geometry ────────────────────────────────────────────────────────── */
typedef struct s_gui_box
{
	t_vec2i			pos;
	t_vec2i			size;
}	t_gui_box;

/* ── Callback type (uses forward-declared t_widget / t_gui) ─────────────── */

/* ── Callback type (uses forward-declared t_widget / t_gui) ─────────────── */
typedef void	(*t_widget_callback)(t_widget *widget, t_gui *gui);

/* ── Widget ──────────────────────────────────────────────────────────────── */
typedef struct s_widget
{
	t_widget_type		type;
	t_gui_box			box;
	char			*label;
	int				value;
	int				color;
	double			dvalue;
	double			dmin;
	double			dmax;
	void			*target;
	t_widget_callback	on_click;
	t_widget_callback	on_change;
	void			*userdata;
	t_widget		*next;
}	t_widget;

/* ── Render thread types ─────────────────────────────────────────────────── */
typedef struct s_render_thread_arg
{
	int				idx;
	t_gui			*gui;
}	t_render_thread_arg;

typedef struct s_render
{
	t_gui			*gui;
	int				next_tile_id;
	int				total_tiles;
	int				tiles_x;
	t_transform		transform;
	double			half_width;
	double			half_height;
	double			aspect_ratio;
	int				step;
	double			px_step_x;
	double			px_step_y;
	double			px_off_x;
	double			px_off_y;
}	t_render;

typedef struct s_render_pool
{
	pthread_t		threads[128];
	sem_t			start[128];
	sem_t			done[128];
	t_render		*ctx[128];
	t_render_thread_arg	args[128];
	int				n;
	bool			shutdown;
	bool			ready;
}	t_render_pool;

/* ── Camera controller ───────────────────────────────────────────────────── */
typedef struct s_camera_controller
{
	t_camera		*camera;
	t_transform		transform;
	t_vec3			target_pos;
	t_rotator		target_rot;
	double			target_fov;
	double			current_fov;
	double			move_speed;
	double			lerp_factor;
	bool			moving_forward;
	bool			moving_backward;
	bool			moving_left;
	bool			moving_right;
	bool			moving_up;
	bool			moving_down;
	bool			zooming_in;
	bool			zooming_out;
	bool			mouse_left_pressed;
	bool			mouse_middle_pressed;
	t_vec2i			last_mouse;	bool				basis_dirty;}	t_camera_controller;

/* ── Window ──────────────────────────────────────────────────────────────── */
typedef struct s_window
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*addr;
	int				bpp;
	int				line_len;
	int				endian;
	t_vec2i			size;
	void			*disp_img;
	char			*disp_addr;
	int				disp_bpp;
	int				disp_line_len;
	int				disp_endian;
	t_vec2i			disp_size;
	void			*gui_bg_img;
	char			*gui_bg_addr;
	int				gui_bg_line_len;
	int				gui_bg_bpp;
	int				gui_bg_endian;
}	t_window;

/* ── Render state ────────────────────────────────────────────────────────── */
typedef struct s_render_state
{
	int				scale;
	bool			dirty;
	bool			force_fullres;
	double			fps;
	long long		last_time;
	bool			last_dirty;
	int				num_cores;
	pthread_t		*threads;
	bool			proj_dirty;
	double			cached_half_w;
	double			cached_half_h;
	double			cached_aspect;
}	t_render_state;

/* ── Input state ─────────────────────────────────────────────────────────── */
typedef struct s_input
{
	t_vec2i			mouse;
}	t_input;

/* ── Map management ──────────────────────────────────────────────────────── */
typedef struct s_map_entry
{
	char			*path;
	t_scene			*scene;
	t_scene_snap	*snap;
	t_map_entry		*next;
}	t_map_entry;

typedef struct s_map
{
	t_map_entry		*head;
	t_map_entry		*current;
	int				count;
}	t_map;

typedef struct s_map_job
{
	pthread_t		tid;
	t_map_entry		*entry;
	bool			done;
	bool			active;
}	t_map_job;

/* ── Main GUI aggregate ──────────────────────────────────────────────────── */
typedef struct s_gui
{
	t_window			win;
	t_scene				*scene;
	t_camera_controller	cam_ctrl;
	t_render_state		render;
	t_input				input;
	t_map				map_info;
	t_widget			*widgets;
	bool				physics_enabled;
	double				phys_accumulator;
	double				phys_fixed_dt;
	int					phys_max_steps;
	int					ambient_color;
	double				ambient_intensity;
	int					last_ambient_color;
	double				last_ambient_intensity;
	t_selection			*selection;
	t_inspector			*inspector;
	t_scene_panel		*scene_panel;
	t_slider_state		*slider_state;
	t_map_job			map_job;
	t_crud_ui			*crud;
	t_hover_cache		*hover;
	t_render_pool		pool;
	t_rt_engine			rt;
	t_physics			*phys;
	t_transform			scratch_tr;
	int					scratch_idx;
	t_type				scratch_type;
	t_physics_body		scratch_phys;
	pthread_rwlock_t	scene_lock;
}	t_gui;

/* ── Misc UI helpers ─────────────────────────────────────────────────────── */
typedef struct s_key_action
{
	int				key;
	void			(*press_action)(t_gui *gui);
	void			(*release_action)(t_gui *gui);
}	t_key_action;

typedef struct s_panel
{
	t_gui_box		box;
	int				bg;
	int				brd;
}	t_panel;

typedef struct s_fill_args
{
	int				x;
	int				y;
	int				color;
	char			*pixel_addr;
}	t_fill_args;

typedef struct s_tile
{
	int				id;
	t_vec2i			tile_idx;
	t_vec2i			pos;
	int				bpp_step;
	int				row_step;
	char			*row_ptr;
	char			*pixel_ptr;
}	t_tile;

/* ── Widget system prototypes ────────────────────────────────────────────── */
t_widget	*widget_create(t_widget_type type, t_vec2i pos,
				t_vec2i size, const char *label);
void	widget_add(t_gui *gui, t_widget *widget);
void	widget_draw_all(t_gui *gui);
void	widget_handle_mouse(t_gui *gui, int button, t_vec2i mouse);
void	widget_handle_key(t_gui *gui, int keycode);
void	widget_init_default(t_gui *gui);
void	widget_draw_checkbox(t_gui *gui, t_widget *w);
void	widget_draw_slider(t_gui *gui, t_widget *w);

/* ── GUI core ────────────────────────────────────────────────────────────── */
bool				gui_init(t_gui *gui, t_scene *scene, void *mlx);
void				gui_destroy(t_gui *gui);
void				gui_loop(t_gui *gui);
void				gui_render(t_gui *gui);
unsigned int	color_blend(unsigned int dst, int src, float alpha);
int				panel_color(t_panel panel, int i, int j);
void				render_tiles(t_render *ctx);
void				draw_panel(t_gui *gui, t_panel panel);
void				draw_ui_panels(t_gui *gui);
void				draw_ui_help(t_gui *gui, int *y);
void				draw_ui_status(t_gui *gui, int *y);
void				draw_ui_object(t_gui *gui);
void				draw_ui_text(t_gui *gui, t_camera_controller *ctrl);
bool				update_hover(t_gui *gui, t_render *ctx);
void				draw_hover_text(t_gui *gui);
void				process_pixel(t_render *ctx, t_vec2i pos, char *pixel_addr);
void				make_camera_ray(t_render *ctx, double x, double y, t_ray *ray);

/* ── Map ─────────────────────────────────────────────────────────────────── */
void	gui_map_switcher_init(t_gui *gui);
void	gui_next_map(t_gui *gui);
void	gui_prev_map(t_gui *gui);
bool	map_load_entry(t_gui *gui, t_map_entry *entry);
void	map_load_async(t_gui *gui, t_map_entry *entry);
void	reset_camera_view(t_gui *gui);
void	map_manager_destroy(t_gui *gui);

/* ── Input ───────────────────────────────────────────────────────────────── */
int	key_press(int keycode, t_gui *gui);
int	key_release(int keycode, t_gui *gui);
int	mouse_click(int button, int x, int y, t_gui *gui);
int	mouse_release(int button, int x, int y, t_gui *gui);
int	mouse_motion(int x, int y, t_gui *gui);
void	shoot_force(t_gui *gui, t_vec2i mouse);
void	handle_scroll(int button, t_gui *gui);
void	gui_update_input(t_gui *gui);

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

/* ── Window management ───────────────────────────────────────────────────── */
int		gui_window_resize(int width, int height, t_gui *gui);
int		gui_window_close(t_gui *gui);
void	upscale_image(t_gui *gui);
void	clamp_fov(double *fov);

/* ── Text / drawing helpers ──────────────────────────────────────────────── */
void			gui_draw_string(t_gui *gui, const char *str, int x, int y,
				unsigned int color);
void			fill_rect(t_gui *gui, int x, int y, int w, int h,
				unsigned int col);

/* ── Slider system ───────────────────────────────────────────────────────── */
void	slider_begin_drag(t_gui *gui, t_widget *w, int mouse_x);
void	slider_update_drag(t_gui *gui, int mouse_x);
void	slider_end_drag(t_gui *gui);

/* ── Scene panel helpers ─────────────────────────────────────────────────── */
int		count_scene_rows(t_scene *sc);
void	row_to_object(t_gui *gui, int r, t_type *ty, int *idx);
const char	*row_type_prefix(t_type type);
void	draw_one_row(t_gui *gui, int y_px, t_type ty, int idx);

int	start_app(void *mlx, const char *path);

#endif
