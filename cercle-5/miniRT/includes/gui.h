/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 11:45:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/11 11:45:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GUI_H
# define GUI_H

/* 1. EXTERNAL DEPENDENCIES */
# include "core.h"
# include "debug.h"
# include "maths.h"

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
	int					last_mouse_x;
	int					last_mouse_y;
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
typedef struct s_window
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
}						t_window;

typedef struct s_render_state
{
	int					scale;
	bool				dirty;
	double				fps;
	long long			last_time;
	bool				last_dirty;
}						t_render_state;

typedef struct s_input_ctxs
{
	int					mouse_x;
	int					mouse_y;
}						t_input_ctx;

struct					s_map
{
	char				**files;
	int					count;
	int					current_idx;
};

struct					s_gui
{
	t_window			win;
	t_scene				*scene;
	t_bvh				*bvh;
	t_camera_controller	cam_ctrl;
	t_render_state		render;
	t_input_ctx			input;
	t_map				map_info;
	void				*widgets;
};

typedef struct s_key_action
{
	int					key;
	void				(*press_action)(t_gui *gui);
	void				(*release_action)(t_gui *gui);
}						t_key_action;

typedef struct s_panel
{
	int					x;
	int					y;
	int					w;
	int					h;
	int					bg;
	int					brd;
}						t_panel;

typedef struct s_fill_params
{
	int					x;
	int					y;
	int					color;
	char				*pixel_addr;
}						t_fill_params;

typedef struct s_tile_vars
{
	int					id;
	int					tx;
	int					ty;
	int					x;
	int					y;
	int					bpp_step;
	int					row_step;
	char				*row_ptr;
	char				*pixel_ptr;
}						t_tile_vars;

/* 4. FUNCTION PROTOTYPES */

/* srcs/gui/init.c */
t_gui					*gui_init(t_scene *scene, t_bvh *bvh, void *mlx);
void					gui_destroy(t_gui *gui);

/* srcs/gui/loop.c */
void					gui_loop(t_gui *gui);

/* srcs/gui/render.c */
void					gui_render(t_gui *gui);
unsigned int			color_blend(unsigned int dst, int src, float alpha);
int						panel_color(t_panel panel, int i, int j);
void					render_tiles(t_render_ctx *ctx);
void					draw_panel(t_gui *gui, t_panel panel);
void					draw_ui_panels(t_gui *gui);
void					draw_ui_text(t_gui *gui, t_camera_controller *ctrl);
bool					update_hover(t_gui *gui, t_render_ctx *ctx);
void					draw_hover_text(t_gui *gui);
void					process_pixel(t_render_ctx *ctx, int x, int y,
							char *pixel_addr);
void					make_camera_ray(t_render_ctx *ctx, double x, double y,
							t_ray *ray);

/* srcs/gui/map_switcher.c */
void					gui_map_switcher_init(t_gui *gui);
void					gui_next_map(t_gui *gui);

/* srcs/gui/input/ */
int						key_press(int keycode, t_gui *gui);
int						key_release(int keycode, t_gui *gui);
int						mouse_click(int button, int x, int y, t_gui *gui);
int						mouse_release(int button, int x, int y, t_gui *gui);
int						mouse_motion(int x, int y, t_gui *gui);
void					gui_update_input(t_gui *gui);

/* srcs/gui/camera/ */
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
void					exit_press(t_gui *gui);

/* 5. IMPLEMENTATION IMPORTS */
# include "raytracing.h"
# include "scene.h"

/* Window Management */
int						gui_window_resize(int width, int height, t_gui *gui);
int						gui_window_close(t_gui *gui);

void					clamp_fov(double *fov);

#endif
