/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   poc_gui.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 16:00:57 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 16:02:04 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GUI_H
# define GUI_H

/* EXTERNAL DEPENDENCIES */
# include "mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <pthread.h>
# include <semaphore.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>

/* NEUTRAL DEPENDENCIES */
# include "debug.h"
# include "defines.h"
# include "maths.h"

/* SYSTEM DEPENDENCIES (Decoupled Architecture) */
# include "physics.h"
# include "scene.h"

/* ------------------------------------------------------------------------- */
/* 1. CONSTANTS & CONFIGURATION                                              */
/* ------------------------------------------------------------------------- */

# define TILE_SIZE 32
# define ZOOM_SPEED 2.0
# define MOUSE_SENSITIVITY 0.005

# define BUTTON_LEFT 1
# define BUTTON_MIDDLE 2
# define BUTTON_RIGHT 3
# define BUTTON_SCROLL_UP 4
# define BUTTON_SCROLL_DOWN 5

# define RENDER_W 2560
# define RENDER_H 1440

/* Auto-refresh configuration */
# ifndef GUI_AUTOREFRESH_PHYSICS
#  define GUI_AUTOREFRESH_PHYSICS 1
# endif

# ifndef GUI_AUTOREFRESH_SCALE
#  define GUI_AUTOREFRESH_SCALE 2
# endif

# define PANEL_RADIUS 6
# define COL_BG 0x0A0A12
# define COL_ACCENT 0xE0A820
# define COL_FPS 0x20E060

# ifndef COL_TEXT
#  define COL_TEXT 0xD0D0D8
# endif
# ifndef COL_HOVER
#  define COL_HOVER 0x20C8D0
# endif
# ifndef COL_BORDER
#  define COL_BORDER 0x333340
# endif

# define MAX_INSPECT_TABS 4

/* ------------------------------------------------------------------------- */
/* 2. ENUMS                                                                  */
/* ------------------------------------------------------------------------- */

typedef enum e_widget_type
{
	WIDGET_LABEL,
	WIDGET_BUTTON,
	WIDGET_CHECKBOX,
	WIDGET_SLIDER,
	WIDGET_COLOR_PICKER,
	WIDGET_PANEL
}								t_widget_type;

typedef enum e_popup_step
{
	POPUP_NONE = 0,
	POPUP_SHAPE,
	POPUP_MESH_FMT,
	POPUP_MESH_PATH,
}								t_popup_step;

typedef enum e_mesh_fmt
{
	MESH_FMT_OBJ,
	MESH_FMT_GLB,
}								t_mesh_fmt;

/* ------------------------------------------------------------------------- */
/* 3. SUB-STRUCTURES                                                         */
/* ------------------------------------------------------------------------- */

typedef struct s_widget			t_widget;
typedef void					(*t_widget_callback)(t_widget *widget,
						struct s_gui *gui);

struct							s_widget
{
	t_widget_type				type;
	t_vec2i						pos;
	t_vec2i						size;
	char						*label;
	int							value;
	int							color;
	double						dvalue;
	double						dmin;
	double						dmax;
	void						*target;
	t_widget_callback			on_click;
	t_widget_callback			on_change;
	void						*userdata;
	t_widget					*next;
};

struct							s_window
{
	void						*mlx;
	void						*win;
	void						*img;
	char						*addr;
	int							bpp;
	int							line_len;
	int							endian;
	int							width;
	int							height;
	void						*disp_img;
	char						*disp_addr;
	int							disp_bpp;
	int							disp_line_len;
	int							disp_endian;
	int							disp_w;
	int							disp_h;
	void						*gui_bg_img;
	char						*gui_bg_addr;
	int							gui_bg_line_len;
	int							gui_bg_bpp;
	int							gui_bg_endian;
};

struct							s_render_state
{
	int							scale;
	bool						dirty;
	bool						force_fullres;
	double						fps;
	long long					last_time;
	bool						last_dirty;
	int							num_cores;
	pthread_t					*threads;
};

struct							s_camera_controller
{
	t_camera					*camera;
	t_transform					transform;
	t_vec3						target_pos;
	t_rotator					target_rot;
	double						target_fov;
	double						move_speed;
	double						lerp_factor;
	bool						moving_forward;
	bool						moving_backward;
	bool						moving_left;
	bool						moving_right;
	bool						moving_up;
	bool						moving_down;
	bool						zooming_in;
	bool						zooming_out;
	bool						mouse_left_pressed;
	bool						mouse_middle_pressed;
	t_vec2i						last_mouse;
};

typedef struct s_render_ctx
{
	struct s_gui				*gui;
	int							next_tile_id;
	int							total_tiles;
	int							tiles_x;
	t_transform					transform;
	double						half_width;
	double						half_height;
	double						aspect_ratio;
	int							step;
}								t_render_ctx;

struct							s_render_thread_arg
{
	int							idx;
	struct s_gui				*gui;
};

struct							s_render_pool
{
	pthread_t					threads;
	sem_t						start;
	sem_t						done;
	struct s_render_ctx			*ctx;
	struct s_render_thread_arg	args;
	int							n;
	bool						shutdown;
	bool						ready;
};

typedef struct s_input_ctx
{
	int							mouse_x;
	int							mouse_y;
}								t_input_ctx;

struct							s_map_entry
{
	char						*path;
	t_scene						*scene;
	t_scene_snap				*snap;
	struct s_map_entry			*next;
};

struct							s_map
{
	struct s_map_entry			*head;
	struct s_map_entry			*current;
	int							count;
};

struct							s_map_job
{
	pthread_t					tid;
	struct s_map_entry			*entry;
	bool						done;
	bool						active;
};

/* ------------------------------------------------------------------------- */
/* 4. MAIN GUI STRUCTURE (THE ORCHESTRATOR)                                  */
/* ------------------------------------------------------------------------- */

typedef struct s_gui
{
	/* Window & Graphics */
	struct s_window				win;
	struct s_render_state		render;
	struct s_render_pool		pool;

	/* Data (The Scene) */
	t_scene						*scene;
	struct s_map				map_info;
	struct s_map_job			map_job;

	/* Logic (The Physics System) */
	t_physics					*physics;
	bool						physics_enabled;
	double						phys_accumulator;
	double						phys_fixed_dt;
	int							phys_max_steps;

	/* Interactive Systems */
	struct s_camera_controller	cam_ctrl;
	t_input_ctx					input;
	t_widget					*widgets;
	t_selection					*selection;
	t_inspector					*inspector;
	t_scene_panel				*scene_panel;
	t_slider_state				*slider_state;
	t_crud_ui					*crud;
	t_hover_cache				*hover;

	/* Editor Params */
	int							ambient_color;
	double						ambient_intensity;
}								t_gui;

/* ------------------------------------------------------------------------- */
/* 5. UI UTILITIES                                                           */
/* ------------------------------------------------------------------------- */

struct							s_panel
{
	t_vec2i						pos;
	t_vec2i						size;
	int							x;
	int							y;
	int							w;
	int							h;
	int							bg;
	int							brd;
};

typedef struct s_fill_args
{
	int							x;
	int							y;
	int							color;
	char						*pixel_addr;
}								t_fill_args;

struct							s_tile
{
	int							id;
	int							tx;
	int							ty;
	t_vec2i						pos;
	int							x;
	int							y;
	int							bpp_step;
	int							row_step;
	char						*row_ptr;
	char						*pixel_ptr;
};

/* ------------------------------------------------------------------------- */
/* 6. FUNCTION PROTOTYPES                                                    */
/* ------------------------------------------------------------------------- */

/* --- Core Lifecycle --- */
bool							gui_init(t_gui *gui, t_scene *scene, void *mlx);
void							gui_destroy(t_gui *gui);
void							gui_loop(t_gui *gui);
void							gui_render(t_gui *gui);

/* --- Rendering Pipeline --- */
void							render_tiles(t_render_ctx *ctx);
void							process_pixel(t_render_ctx *ctx, t_vec2i pos,
									char *pixel_addr);
void							make_camera_ray(t_render_ctx *ctx, double x,
									double y, t_ray *ray);
void							upscale_image(t_gui *gui);
unsigned int					color_blend(unsigned int dst, int src,
									float alpha);

/* --- Input Logic --- */
int								key_press(int keycode, t_gui *gui);
int								key_release(int keycode, t_gui *gui);
int								mouse_click(int button, int x, int y,
									t_gui *gui);
int								mouse_release(int button, int x, int y,
									t_gui *gui);
int								mouse_motion(int x, int y, t_gui *gui);
void							gui_update_input(t_gui *gui);
void							handle_scroll(int button, t_gui *gui);

/* --- Camera Controller --- */
void							camera_move(t_camera *camera, t_vec3 direction,
									double speed);
void							camera_move_forward(t_camera *camera,
									double speed);
void							camera_move_backward(t_camera *camera,
									double speed);
void							camera_move_left(t_camera *camera,
									double speed);
void							camera_move_right(t_camera *camera,
									double speed);
void							camera_move_up(t_camera *camera, double speed);
void							camera_move_down(t_camera *camera,
									double speed);
void							camera_rotate_yaw(t_gui *gui, double delta_yaw);
void							camera_rotate_pitch(t_gui *gui,
									double delta_pitch);
void							apply_movement(struct s_camera_controller *ctrl,
									t_vec3 fwd, t_vec3 right);
void							smooth_rotation(t_gui *gui,
									struct s_camera_controller *ctrl);
void							smooth_position(t_gui *gui,
									struct s_camera_controller *ctrl);
void							update_fov(t_gui *gui,
									struct s_camera_controller *ctrl);

/* --- Input Press/Release Actions --- */
void							move_forward_press(t_gui *gui);
void							move_forward_release(t_gui *gui);
void							move_backward_press(t_gui *gui);
void							move_backward_release(t_gui *gui);
void							move_left_press(t_gui *gui);
void							move_left_release(t_gui *gui);
void							move_right_press(t_gui *gui);
void							move_right_release(t_gui *gui);
void							zoom_in_press(t_gui *gui);
void							zoom_in_release(t_gui *gui);
void							exit_press(t_gui *gui);
void							fullres_toggle(t_gui *gui);

/* --- Widget System --- */
t_widget						*widget_create(t_widget_type type, t_vec2i pos,
									t_vec2i size, const char *label);
void							widget_add(t_gui *gui, t_widget *widget);
void							widget_draw_all(t_gui *gui);
void							widget_handle_mouse(t_gui *gui, int button,
									t_vec2i mouse);
void							widget_handle_key(t_gui *gui, int keycode);
void							widget_init_default(t_gui *gui);
void							widget_draw_checkbox(t_gui *gui, t_widget *w);
void							widget_draw_slider(t_gui *gui, t_widget *w);

/* --- UI Drawing --- */
void							draw_panel(t_gui *gui, struct s_panel panel);
void							draw_ui_panels(t_gui *gui);
void							draw_ui_text(t_gui *gui,
									struct s_camera_controller *ctrl);
void							gui_draw_string(t_gui *gui, const char *str,
									int x, int y, unsigned int color);
void							fill_rect(t_gui *gui, int x, int y, int w,
									int h, unsigned int col);
bool							update_hover(t_gui *gui, t_render_ctx *ctx);
void							draw_hover_text(t_gui *gui);

/* --- Map & Window Management --- */
void							gui_map_switcher_init(t_gui *gui);
void							gui_next_map(t_gui *gui);
void							gui_prev_map(t_gui *gui);
bool							map_load_entry(t_gui *gui,
									struct s_map_entry *entry);
void							map_load_async(t_gui *gui,
									struct s_map_entry *entry);
void							reset_camera_view(t_gui *gui);
int								gui_window_resize(int width, int height,
									t_gui *gui);
int								gui_window_close(t_gui *gui);

/* --- Physics Bridge --- */
void							shoot_force(t_gui *gui, t_vec2i mouse);

#endif