/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 20:29:45 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 10:38:09 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GUI_H
# define GUI_H

/* External dependencies */
# include "mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>

/* 2. CONSTANTS */
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

/* Auto-refresh configuration:
 * - Set `GUI_AUTOREFRESH_PHYSICS` to 1 to force a render every frame while
 *   physics simulation is enabled. Set to 0 to use standard "dirty only"
 *   behavior.
 * - `GUI_AUTOREFRESH_SCALE` controls the downscale factor used during
 *   auto-refresh to keep rendering fast while simulating physics.
 */
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

/* --- Editor Color Constants --- */
# define COL_SELECTED 0x20D870U
# define COL_PANEL_HDR 0x1A1A28U
# define COL_ROW_HOVER 0x1E2030U
# define COL_ROW_SEL 0x2A3040U
# define COL_SLIDER_BG 0x1A1A20U
# define COL_SLIDER_FG 0xE0A820U
/* --- Editor Layout Constants --- */
# define INSPECTOR_W 280
# define SCENE_PANEL_W 220
# define ROW_H 24
# define CRUD_PANEL_H 36
# define SLIDER_H 8
# define SLIDER_KNOB_W 3
# define SLIDER_KNOB_H 12
# define SLIDER_PAD 24
# define SLIDER_Y_OFF 13
# define SLIDER_VAL_X 46

# define CRUD_BTN_H 24
# define CRUD_BTN_W 52
# define CRUD_ADD_W 90
# define POPUP_W 360
# define POPUP_ITEM_H 36
# define POPUP_PAD 16
# define POPUP_TITLE_H 36
# define POPUP_FMT_H 36
# define POPUP_INPUT_H 36
# define POPUP_ERR_H 16
# define POPUP_BTN_H 36

# define COL_POPUP_DIM 0x0D0D14U
# define COL_POPUP_BG 0x1A1A28U
# define COL_POPUP_BTN 0x22222EU
# define COL_POPUP_BTN_OK 0x1A2A1AU
# define COL_POPUP_BTN_CANCEL 0x2A1A1AU
# define COL_POPUP_ERR 0xFF4444U
# define COL_POPUP_ERR_TEXT 0xFF6666U
# define SCENE_PANEL_PAD_X 12
# define SCENE_PANEL_PAD_Y 8
# define SCENE_PANEL_HDR_X 8
# define SCENE_PANEL_EMPTY_COL 0x505060

# define INSPECTOR_HDR_Y 50
# define INSPECTOR_TAB_Y 70
# define INSPECTOR_TAB_H 24
# define INSPECTOR_PAD 8
# define INSPECTOR_TAB_MIN_Y 60
# define INSPECTOR_TAB_MAX_Y 84

# define TR_PANEL_START_Y 104
# define TR_PANEL_STEP_Y 30

/* --- Slider Range Constants --- */
/* Transform */
# define SL_POS_MIN -500.0
# define SL_POS_MAX 500.0
# define SL_ROT_MIN -180.0
# define SL_ROT_MAX 180.0
# define SL_SCALE_MIN 0.0
# define SL_SCALE_MAX 100.0
/* Material */
# define SL_ROUGH_MIN 0.0
# define SL_ROUGH_MAX 1.0
# define SL_METAL_MIN 0.0
# define SL_METAL_MAX 1.0
# define SL_OPAC_MIN 0.0
# define SL_OPAC_MAX 1.0
# define SL_REFL_MIN 0.0
# define SL_REFL_MAX 1.0
# define SL_IOR_MIN 0.0
# define SL_IOR_MAX 180.0
# define SL_COL_MIN 0.0
# define SL_COL_MAX 255.0
# define SL_EMIT_MIN 0.0
# define SL_EMIT_MAX 255.0
/* Light */
# define SL_INTENSITY_MIN 0.0
# define SL_INTENSITY_MAX 5.0
# define SL_CUTOFF_MIN 0.0
# define SL_CUTOFF_MAX 90.0
/* Ambient */
# define SL_AMB_MIN 0.0
# define SL_AMB_MAX 2.0
/* Physics */
# define SL_MASS_MIN 0.01
# define SL_MASS_MAX 1000.0
# define SL_ELAST_MIN 0.0
# define SL_ELAST_MAX 1.0
# define SL_FRIC_MIN 0.0
# define SL_FRIC_MAX 1.0
# define MAX_INSPECT_TABS 4
/* 2. MODULE TYPES */

/* 1. EXTERNAL DEPENDENCIES */
# include "debug.h"
# include "defines.h"
# include "maths.h"
# include "objects.h"
# include "physics.h"
# include "scene.h"
# include "surface.h"

typedef enum e_widget_type
{
	WIDGET_LABEL,
	WIDGET_BUTTON,
	WIDGET_CHECKBOX,
	WIDGET_SLIDER,
	WIDGET_COLOR_PICKER,
	WIDGET_PANEL
}						t_widget_type;

typedef enum e_popup_step
{
	POPUP_NONE = 0,
	POPUP_SHAPE,
	POPUP_MESH_FMT,
	POPUP_MESH_PATH,
}						t_popup_step;

typedef enum e_mesh_fmt
{
	MESH_FMT_OBJ,
	MESH_FMT_GLB,
}						t_mesh_fmt;

typedef void			(*t_widget_callback)(t_widget *widget,
				struct s_gui *gui);

struct					s_selection
{
	t_type				type;
	int					index;
	bool				active;
	t_aabb				bbox;
};

typedef enum e_inspect_tab
{
	TAB_TRANSFORM,
	TAB_MATERIAL,
	TAB_OBJECT,
	TAB_LIGHT,
	TAB_PHYSICS,
	TAB_INFO
}						t_inspect_tab;

struct					s_inspector
{
	bool				visible;
	t_inspect_tab		tab;
	int					x;
	int					width;
};

struct					s_scene_panel
{
	bool				visible;
	int					width;
	int					scroll;
	int					hovered_row;
};

struct					s_btn_rect
{
	t_vec2i				pos;
	t_vec2i				size;
};

struct					s_islider
{
	const char			*label;
	double				min;
	double				max;
	double				*ptr;
};

struct					s_slider_arg
{
	t_vec2i				pos;
	t_islider			sl;
	void				(*on_change)(struct s_gui *gui);
};

struct					s_vec3_label_arg
{
	int					x;
	int					y;
	const char			*label;
	t_vec3				v;
};

struct					s_bool_label_arg
{
	int					x;
	int					y;
	const char			*label;
	bool				val;
};

struct					s_slider_state
{
	bool				dragging;
	int					drag_start_x;
	double				drag_start_val;
	double				*value_ptr;
	double				dmin;
	double				dmax;
	int					track_x;
	int					track_w;
	void				(*on_change)(struct s_gui *gui);
	struct s_widget		*target;
};

struct					s_mesh_snap
{
	t_transform			transform;
	int					mat_id;
	t_physics_body		phys;
};

struct					s_group_snap
{
	t_transform			transform;
	t_vec3				pivot;
	t_physics_body		phys;
};

struct					s_scene_snap
{
	t_sphere			*spheres;
	int					sphere_count;
	t_plane				*planes;
	int					plane_count;
	t_cylinder			*cylinders;
	int					cylinder_count;
	t_cone				*cones;
	int					cone_count;
	t_light				*lights;
	int					light_count;
	t_material			*materials;
	int					mat_count;
	t_mesh_snap			*meshes;
	int					mesh_count;
	int					mesh_group_count;
	t_group_snap		*groups;
	int					group_count;
	t_box				*boxes;
	int					box_count;
	t_capsule			*capsules;
	int					capsule_count;
	t_rect				*rects;
	int					rect_count;
	t_pyramid			*pyramids;
	int					pyramid_count;
	t_tri_shape			*tris;
	int					tri_count;
	t_ambient			ambient;
	t_camera			camera;
	int					ambient_color;
	double				ambient_intensity;
};

struct					s_widget
{
	t_widget_type		type;
	t_vec2i				pos;
	t_vec2i				size;
	char				*label;
	int					value;
	int					color;
	double				dvalue;
	double				dmin;
	double				dmax;
	void				*target;
	t_widget_callback	on_click;
	t_widget_callback	on_change;
	void				*userdata;
	t_widget			*next;
};

struct					s_crud_ui
{
	t_popup_step		popup;
	t_mesh_fmt			mesh_fmt;
	char				path_buf[512];
	int					path_len;
	bool				path_error;
	bool				shift_held;
	t_vec2i				pos;
	int					w;
	int					h;
};

struct					s_render_thread_arg
{
	int					idx;
	struct s_gui		*gui;
};

struct					s_render_pool
{
	pthread_t			threads[128];
	sem_t				start[128];
	sem_t				done[128];
	struct s_render_ctx	*ctx[128];
	t_render_thread_arg	args[128];
	int					n;
	bool				shutdown;
	bool				ready;
};

struct					s_hover_cache
{
	int					x;
	int					y;
	bool				active;
	bool				hit;
	long				last_frame;
};

/* 3. MODULE TYPES */
struct					s_camera_controller
{
	t_camera			*camera;
	t_transform			transform;
	t_vec3				target_pos;
	t_rotator			target_rot;
	double				target_fov;
	double				move_speed;
	double				lerp_factor;
	bool				moving_forward;
	bool				moving_backward;
	bool				moving_left;
	bool				moving_right;
	bool				moving_up;
	bool				moving_down;
	bool				zooming_in;
	bool				zooming_out;
	bool				mouse_left_pressed;
	bool				mouse_middle_pressed;
	t_vec2i				last_mouse;
};

struct					s_render_ctx
{
	t_gui				*gui;
	int					next_tile_id;
	int					total_tiles;
	int					tiles_x;
	t_transform			transform;
	double				half_width;
	double				half_height;
	double				aspect_ratio;
	int					step;
};

/* Sub-structs for t_gui */
struct					s_window
{
	void				*mlx;
	void				*win;
	void				*img;
	char				*addr;
	int					bpp;
	int					line_len;
	int					endian;
	int					width;
	int					height;
	void				*disp_img;
	char				*disp_addr;
	int					disp_bpp;
	int					disp_line_len;
	int					disp_endian;
	int					disp_w;
	int					disp_h;
	void				*gui_bg_img;
	char				*gui_bg_addr;
	int					gui_bg_line_len;
	int					gui_bg_bpp;
	int					gui_bg_endian;
};

struct					s_render_state
{
	int					scale;
	bool				dirty;
	bool				force_fullres;
	double				fps;
	long long			last_time;
	bool				last_dirty;
	int					num_cores;
	pthread_t			*threads;
};

typedef struct s_input_ctxs
{
	int					mouse_x;
	int					mouse_y;
}						t_input_ctx;

struct					s_map_entry
{
	char				*path;
	t_scene				*scene;
	t_scene_snap		snap;
	struct s_map_entry	*next;
};

struct					s_map
{
	t_map_entry			*head;
	t_map_entry			*current;
	int					count;
};

struct					s_map_job
{
	pthread_t			tid;
	t_map_entry			*entry;
	bool				done;
	bool				active;
};

struct					s_gui
{
	t_window			win;
	t_scene				*scene;
	t_camera_controller	cam_ctrl;
	t_render_state		render;
	t_input_ctx			input;
	t_map				map_info;
	t_widget			*widgets;
	bool				physics_enabled;
	double				phys_accumulator;
	double				phys_fixed_dt;
	int					phys_max_steps;
	int					ambient_color;
	double				ambient_intensity;
	t_selection			selection;
	t_inspector			inspector;
	t_scene_panel		scene_panel;
	t_slider_state		slider_state;
	t_map_job			map_job;
	t_crud_ui			crud;
	t_hover_cache		hover;
	t_render_pool		pool;
};

struct					s_key_action
{
	int					key;
	void				(*press_action)(t_gui *gui);
	void				(*release_action)(t_gui *gui);
};

struct					s_panel
{
	t_vec2i				pos;
	t_vec2i				size;
	int					x;
	int					y;
	int					w;
	int					h;
	int					bg;
	int					brd;
};

typedef struct s_fill_params
{
	int					x;
	int					y;
	int					color;
	char				*pixel_addr;
}						t_fill_params;

struct					s_tile_vars
{
	int					id;
	int					tx;
	int					ty;
	t_vec2i				pos;
	int					x;
	int					y;
	int					bpp_step;
	int					row_step;
	char				*row_ptr;
	char				*pixel_ptr;
};

t_widget				*widget_create(t_widget_type type, t_vec2i pos,
							t_vec2i size, const char *label);
void					widget_add(struct s_gui *gui, t_widget *widget);
void					widget_draw_all(struct s_gui *gui);
void					widget_handle_mouse(struct s_gui *gui, int button,
							t_vec2i mouse);
void					widget_handle_key(struct s_gui *gui, int keycode);
void					widget_init_default(t_gui *gui);

void					widget_draw_checkbox(struct s_gui *gui, t_widget *w);
void					widget_draw_slider(struct s_gui *gui, t_widget *w);

/* 4. FUNCTION PROTOTYPES */

t_gui					*gui_init(t_scene *scene, void *mlx);
void					gui_destroy(t_gui *gui);
void					gui_loop(t_gui *gui);
void					gui_render(t_gui *gui);
unsigned int			color_blend(unsigned int dst, int src, float alpha);
int						panel_color(t_panel panel, int i, int j);
void					render_tiles(t_render_ctx *ctx);
void					draw_panel(t_gui *gui, t_panel panel);
void					draw_ui_panels(t_gui *gui);
void					draw_ui_help(t_gui *gui, int *y);
void					draw_ui_status(t_gui *gui, int *y);
void					draw_ui_object(t_gui *gui);
void					draw_ui_text(t_gui *gui, t_camera_controller *ctrl);
bool					update_hover(t_gui *gui, t_render_ctx *ctx);
void					draw_hover_text(t_gui *gui);
void					process_pixel(t_render_ctx *ctx, t_vec2i pos,
							char *pixel_addr);
void					make_camera_ray(t_render_ctx *ctx, double x, double y,
							t_ray *ray);

/* srcs/gui/map/ */
void					gui_map_switcher_init(t_gui *gui);
void					gui_next_map(t_gui *gui);
void					gui_prev_map(t_gui *gui);
bool					map_load_entry(t_gui *gui, t_map_entry *entry);
void					map_load_async(t_gui *gui, t_map_entry *entry);
void					reset_camera_view(t_gui *gui);
void					map_manager_destroy(t_gui *gui);

/* srcs/gui/input/ */
int						key_press(int keycode, t_gui *gui);
int						key_release(int keycode, t_gui *gui);
int						mouse_click(int button, t_vec2i mouse, t_gui *gui);
int						mouse_release(int button, t_vec2i mouse, t_gui *gui);
int						mouse_motion(t_vec2i mouse, t_gui *gui);
int (*mouse_click_hook(void))(int, int, int, t_gui *);
int (*mouse_release_hook(void))(int, int, int, t_gui *);
int (*mouse_motion_hook(void))(int, int, t_gui *);
void					gui_update_input(t_gui *gui);
void					camera_move(t_camera *camera, t_vec3 direction,
							double speed);
void					camera_move_forward(t_camera *camera, double speed);
void					camera_move_backward(t_camera *camera, double speed);
void					camera_move_left(t_camera *camera, double speed);
void					camera_move_right(t_camera *camera, double speed);
void					camera_move_up(t_camera *camera, double speed);
void					camera_move_down(t_camera *camera, double speed);
void					camera_rotate_yaw(t_gui *gui, double delta_yaw);
void					camera_rotate_pitch(t_gui *gui, double delta_pitch);
void					get_forward(double pitch, double yaw, t_vec3 *out);
void					apply_movement(t_camera_controller *ctrl, t_vec3 fwd,
							t_vec3 right);
void					smooth_rotation(t_gui *gui, t_camera_controller *ctrl);
void					smooth_position(t_gui *gui, t_camera_controller *ctrl);
void					update_fov(t_gui *gui, t_camera_controller *ctrl);

void					move_forward_press(t_gui *gui);
void					move_forward_release(t_gui *gui);
void					move_backward_press(t_gui *gui);
void					move_backward_release(t_gui *gui);
void					move_left_press(t_gui *gui);
void					move_left_release(t_gui *gui);
void					move_right_press(t_gui *gui);
void					move_right_release(t_gui *gui);
void					move_up_press(t_gui *gui);
void					move_up_release(t_gui *gui);
void					move_down_press(t_gui *gui);
void					move_down_release(t_gui *gui);
void					zoom_in_press(t_gui *gui);
void					zoom_in_release(t_gui *gui);
void					zoom_out_press(t_gui *gui);
void					zoom_out_release(t_gui *gui);
void					speed_up_press(t_gui *gui);
void					speed_down_press(t_gui *gui);
void					map_next_press(t_gui *gui);
void					map_prev_press(t_gui *gui);
void					exit_press(t_gui *gui);
void					fullres_toggle(t_gui *gui);

void					fill_map_list(t_gui *gui);
void					set_current_entry(t_gui *gui);

/* Window Management */
int						gui_window_resize(int width, int height, t_gui *gui);
int						gui_window_close(t_gui *gui);
void					upscale_image(t_gui *gui);

void					clamp_fov(double *fov);

/* Software bitmap font — draws text directly into disp_img */
void					gui_draw_string(t_gui *gui, const char *str, int x,
							int y, unsigned int color);

/* 3. FUNCTION PROTOTYPES */

/* srcs/gui/editor/selection.c */
void					select_object(struct s_gui *gui, t_type type,
							int index);
void					clear_selection(struct s_gui *gui);
t_material				*get_selected_material(struct s_gui *gui);
void					pick_at_mouse(struct s_gui *gui, t_vec2i mouse);
void					rebuild_bvh(struct s_gui *gui);

/* srcs/gui/editor/scene_panel.c */
void					editor_init(struct s_gui *gui);
void					draw_scene_panel_bg(struct s_gui *gui);
void					draw_scene_panel_text(struct s_gui *gui);
bool					scene_panel_handle_click(struct s_gui *gui,
							t_vec2i mouse);
bool					scene_panel_handle_scroll(struct s_gui *gui,
							int button);

/* srcs/gui/editor/inspector.c */
const char				*type_name_str(t_type type);
void					draw_inspector_bg(struct s_gui *gui);
void					draw_inspector_text(struct s_gui *gui);
bool					inspector_handle_click(struct s_gui *gui,
							t_vec2i mouse);

/* srcs/gui/editor/transform_panel.c */
t_transform				*get_selected_transform(struct s_gui *gui);
void					draw_transform_panel(struct s_gui *gui, int x);

/* srcs/gui/editor/material_panel.c */
void					draw_material_panel_text(struct s_gui *gui, int x);
bool					material_panel_handle_click(struct s_gui *gui,
							t_vec2i mouse);

/* material panel helpers */
void					build_mat_sliders(t_material *mat, t_islider *sl,
							int *count);

/* srcs/gui/editor/transform_panel.c */
bool					transform_panel_handle_click(struct s_gui *gui,
							t_vec2i mouse);

/* transform panel helpers and callbacks */
void					mesh_transform_sync(struct s_gui *gui);
void					sphere_scale_sync(struct s_gui *gui);
void					box_scale_sync(struct s_gui *gui);
void					capsule_dims_sync(struct s_gui *gui);
void					build_tr_sliders(t_transform *tr, t_type type,
							t_islider *sl, int *count);

/* srcs/gui/editor/slider_inline.c */
void					draw_slider_row(struct s_gui *gui, t_slider_arg arg);
bool					try_islider_click(struct s_gui *gui, t_vec2i mouse,
							t_slider_arg arg);
void					update_inline_drag(struct s_gui *gui, int mouse_x);
void					end_inline_drag(struct s_gui *gui);

/* srcs/gui/editor/crud.c */
void					editor_add_sphere(struct s_gui *gui);
void					editor_add_plane(struct s_gui *gui);
void					editor_add_cylinder(struct s_gui *gui);
void					editor_add_cone(struct s_gui *gui);
void					editor_add_light(struct s_gui *gui);
void					editor_add_tri(struct s_gui *gui);
void					editor_add_rect(struct s_gui *gui);
void					editor_add_pyramid(struct s_gui *gui);
void					editor_add_box(struct s_gui *gui);
void					editor_add_capsule(struct s_gui *gui);
void					editor_add_obj(struct s_gui *gui, const char *path);
void					editor_add_glb(struct s_gui *gui, const char *path);
void					editor_delete_selected(struct s_gui *gui);

/* delete helpers (crud/delete/) */
bool					handle_delete_light(t_scene *sc, t_selection *sel,
							int i);
void					delete_sel_prims(t_scene *sc, t_selection *sel);
void					delete_sel_solids(t_scene *sc, t_selection *sel);
void					delete_sel_extras(t_scene *sc, t_selection *sel);

/* crud helpers */
t_transform				make_obj_transform(t_vec3 pos, t_vec3 fwd, t_vec3 scl);
t_vec3					cam_fwd_pos(struct s_gui *gui, double dist);

/* srcs/gui/editor/crud_ui.c */
void					draw_crud_buttons(struct s_gui *gui);
bool					crud_handle_click(struct s_gui *gui, t_vec2i mouse);

/* srcs/gui/editor/popup.c */
void					draw_popup(struct s_gui *gui);
bool					popup_handle_click(struct s_gui *gui, t_vec2i mouse);
bool					popup_handle_key(struct s_gui *gui, int keycode);
void					update_popup_rect(struct s_gui *gui);
void					popup_load_mesh(struct s_gui *gui);

/* Internal Popup Helpers */
bool					phit(t_vec2i m, t_vec2i pos, t_vec2i size);
void					draw_modal_bg(struct s_gui *gui);
void					draw_popup_btn(struct s_gui *gui, t_vec2i pos,
							t_vec2i size, const char *lbl, int bg);
void					draw_popup_shape(struct s_gui *gui);
bool					click_popup_shape(struct s_gui *gui, t_vec2i mouse);
void					draw_popup_mesh_fmt(struct s_gui *gui);
bool					click_popup_mesh_fmt(struct s_gui *gui, t_vec2i mouse);
void					draw_popup_mesh_path(struct s_gui *gui);
bool					click_popup_mesh_path(struct s_gui *gui, t_vec2i mouse);
char					popup_shift_char(int keycode);
void					draw_physics_panel(struct s_gui *gui,
							t_physics_body *phys, int x);
bool					physics_panel_handle_click(struct s_gui *gui,
							t_vec2i mouse, t_physics_body *phys);

/* physics panel helpers */
void					build_phys_sliders(t_physics_body *phys,
							t_islider out[3]);

/* srcs/gui/editor/light_panel.c */
void					draw_light_panel(struct s_gui *gui, int x);
bool					light_panel_handle_click(struct s_gui *gui,
							t_vec2i mouse);
void					draw_ambient_panel(struct s_gui *gui, int x);
bool					ambient_panel_handle_click(struct s_gui *gui,
							t_vec2i mouse);

/* shared helpers for light panel */
void					build_light_sliders(t_light *lt, t_islider *sl,
							int *count);

/* srcs/gui/editor/mesh_info_panel.c */
void					draw_mesh_info_panel(struct s_gui *gui, int x);
t_physics_body			*get_selected_physics(t_gui *gui);
int						get_tabs(t_type type, t_inspect_tab tabs[4],
							const char *labels[4]);

void					scene_snapshot(t_scene_snap *snap, struct s_gui *gui);
void					scene_snap_free(t_scene_snap *snap);
void					scene_reset(struct s_gui *gui);

/* Global UI Helpers */
void					fill_rect(struct s_gui *gui, int x, int y, int w, int h,
							unsigned int col);

/* Internal Snapshot Helpers */
void					snap_array(void **dst, void *src, int count, size_t sz);
void					snap_sphere(t_scene_snap *s, t_scene *sc);
void					snap_plane(t_scene_snap *s, t_scene *sc);
void					snap_cylinder(t_scene_snap *s, t_scene *sc);
void					snap_cone(t_scene_snap *s, t_scene *sc);
void					snap_light(t_scene_snap *s, t_scene *sc);
void					snap_box(t_scene_snap *s, t_scene *sc);
void					snap_capsule(t_scene_snap *s, t_scene *sc);
void					snap_rect(t_scene_snap *s, t_scene *sc);
void					snap_pyramid(t_scene_snap *s, t_scene *sc);
void					snap_tri(t_scene_snap *s, t_scene *sc);
void					snap_mesh(t_scene_snap *s, t_scene *sc);
void					snap_material(t_scene_snap *s, t_scene *sc);

/* Internal Reset Helpers */
void					reset_sphere(t_scene *sc, t_scene_snap *s);
void					reset_plane(t_scene *sc, t_scene_snap *s);
void					reset_cylinder(t_scene *sc, t_scene_snap *s);
void					reset_cone(t_scene *sc, t_scene_snap *s);
void					reset_light(t_scene *sc, t_scene_snap *s);
void					reset_box(t_scene *sc, t_scene_snap *s);
void					reset_capsule(t_scene *sc, t_scene_snap *s);
void					reset_rect(t_scene *sc, t_scene_snap *s);
void					reset_pyramid(t_scene *sc, t_scene_snap *s);
void					reset_tri(t_scene *sc, t_scene_snap *s);
void					reset_mesh(t_scene *sc, t_scene_snap *s);
void					reset_material(t_scene *sc, t_scene_snap *s);
int						start_app(t_gui *gui, t_scene *scene, void *mlx);

/* Internal Inspector Helpers */
t_physics_body			*get_selected_physics(struct s_gui *gui);
int						get_tabs(t_type type, t_inspect_tab tabs[4],
							const char *labels[4]);

/* Internal Scene Panel Helpers */
int						count_scene_rows(t_scene *sc);
void					row_to_object(struct s_gui *gui, int r, t_type *ty,
							int *idx);
const char				*row_type_prefix(t_type type);
void					draw_one_row(struct s_gui *gui, int y_px, t_type ty,
							int idx);

#endif