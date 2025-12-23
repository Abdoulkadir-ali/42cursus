/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 19:41:27 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/23 22:14:31 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTS_H
# define EVENTS_H

# include <X11/Xlib.h>
# include <X11/keysym.h>
# include <math.h>
# include <sys/time.h>

/* ========== PACKAGES ========== */
# include "define.h"
# include "geometry.h"
# include "graphics.h"
# include "gui.h"
# include "libft.h"
# include "render.h"
# include "window.h"

/* ========== CONTROLS ========== */
# ifndef CONTROLS_H
#  define CONTROLS_H

#  define MOUSE_LEFT 1
#  define MOUSE_MIDDLE 2
#  define MOUSE_RIGHT 3
#  define MOUSE_SCROLL_UP 4
#  define MOUSE_SCROLL_DOWN 5

#  define KEY_UP_ARROW XK_Up
#  define KEY_DOWN_ARROW XK_Down
#  define KEY_LEFT_ARROW XK_Left
#  define KEY_RIGHT_ARROW XK_Right
#  define KEY_CTRL_LEFT XK_Control_L
#  define KEY_CTRL_RIGHT XK_Control_R
#  define KEY_SHIFT_LEFT XK_Shift_L
#  define KEY_SHIFT_RIGHT XK_Shift_R
#  define KEY_L XK_l
#  define KEY_Z XK_z
#  define KEY_F XK_f
#  define KEY_H XK_h
#  define KEY_D XK_d
#  define KEY_T XK_t
#  define KEY_S XK_s
#  define KEY_A XK_a
#  define KEY_X XK_x
#  define KEY_I XK_i
#  define KEY_V XK_v
#  define KEY_G XK_g
#  define KEY_PLUS XK_plus
#  define KEY_MINUS XK_minus
#  define KEY_ZERO XK_0
#  define KEY_ESC XK_Escape
#  define KEY_R XK_r
#  define KEY_P XK_p
#  define KEY_N XK_n
#  define KEY_BRACKET_LEFT XK_bracketleft
#  define KEY_BRACKET_RIGHT XK_bracketright
#  define KEY_B XK_b
#  define KEY_Y XK_y
#  define KEY_W XK_w
#  define KEY_1 XK_1
#  define KEY_2 XK_2
#  define KEY_3 XK_3
#  define KEY_7 XK_7
#  define KEY_8 XK_8
#  define KEY_9 XK_9
#  define KEY_Q XK_q
#  define KEY_E XK_e
#  define KEY_U XK_u

# endif

typedef struct s_mouse
{
	int					left_pressed;
	int					right_pressed;
	int					middle_pressed;
	int					last_x;
	int					last_y;
	int					middle_start_x;
	int					middle_start_y;
}						t_mouse;

typedef struct s_keys
{
	int					up;
	int					down;
	int					left;
	int					right;
	int					ctrl_left;
	int					ctrl_right;
	int					shift_left;
	int					shift_right;
	int					l;
	int					z;
	int					f;
	int					h;
	int					d;
	int					t;
	int					s;
	int					a;
	int					x;
	int					i;
	int					v;
	int					g;
	int					b;
	int					w;
	int					y;
}						t_keys;

typedef struct s_movement_ctx
{
	t_vec2d				v;
	int					m;
	double				speed;
}						t_movement_ctx;

typedef struct s_combo_ctx
{
	float				old_lod;
	float				old_z;
	unsigned int		old_frust;
	unsigned int		old_damp;
	double				old_alpha;
	double				old_rot_speed;
}						t_combo_ctx;

typedef struct s_resize_ctx
{
	t_window			*win;
	XWindowAttributes	attrs;
	t_mlx_ptr			*mlx;
	t_mlx_win_list		*win_list;
	t_vec2				old_size;
	t_vec2				new_size;
}						t_resize_ctx;

typedef int				(*t_key_action)(int keycode, t_events *events);

typedef struct s_key_maps
{
	t_key_action		key_actions[KEY_MAP_SIZE];
	t_key_action		key_releases[KEY_MAP_SIZE];
}						t_key_maps;

typedef struct s_events_args
{
	t_window			*window;
	t_graphics			*graphics;
	t_gui				*gui;
	t_camera_manager	*camera_manager;
	t_maps				*maps;
	t_map				*map;
}						t_events_args;

typedef struct s_events
{
	t_camera			*camera;
	t_window			*window;
	t_map				*map;
	t_maps				*maps;
	t_graphics			*graphics;
	t_gui				gui;
	t_camera_manager	*camera_manager;
	int					render_mode;
	float				lod_value;
	int					use_depth_culling;
	int					filled;
	t_mouse				mouse;
	t_keys				keys;
	t_key_maps			key_maps;
}						t_events;

/* Initialize events from a compact args struct */
t_events				*init_events(t_events_args *args);
void					init_mouse(t_mouse *mouse);
void					init_keys(t_keys *keys);
void					handle_mouse_release(int button, t_mouse *mouse);
int						handle_mouse_scroll(int button, t_events *events);
void					handle_mouse_click(int button, int x, int y,
							t_mouse *mouse);
int						mouse_press(int button, int x, int y, t_events *events);
int						mouse_release(int button, int x, int y,
							t_events *events);
int						mouse_move(int x, int y, t_events *events);
int						key_press(int keycode, t_events *events);
int						key_release(int keycode, t_events *events);
int						loop_hook(t_events *events);
int						process_movement(t_events *events);
int						process_rotation(t_events *events);
void					cycle_projection(t_events *events);
void					reset_view(t_events *events);
void					adjust_move_speed(t_events *events, int increase);
int						cleanup_and_exit(t_events *events);
void					setup_hooks(t_events *events);
int						handle_resize(t_events *events);

/* Key action functions */
int						handle_escape(int keycode, t_events *events);
int						handle_r(int keycode, t_events *events);
int						handle_p(int keycode, t_events *events);
int						handle_n(int keycode, t_events *events);
int						handle_s(int keycode, t_events *events);
int						handle_m(int keycode, t_events *events);
int						handle_i(int keycode, t_events *events);
int						handle_v(int keycode, t_events *events);
int						handle_g(int keycode, t_events *events);

int						handle_1(int keycode, t_events *events);
int						handle_2(int keycode, t_events *events);
int						handle_3(int keycode, t_events *events);
int						handle_plus(int keycode, t_events *events);
int						handle_minus(int keycode, t_events *events);
int						handle_0(int keycode, t_events *events);
int						handle_up(int keycode, t_events *events);
int						handle_down(int keycode, t_events *events);
int						handle_left(int keycode, t_events *events);
int						handle_right(int keycode, t_events *events);
int						handle_horizontal(int keycode, t_events *events,
							int left);
int						handle_press_flag(int keycode, t_events *events);
int						handle_release_flag(int keycode, t_events *events);
void					handle_button(int keycode, t_events *events, int value);

void					set_key_actions_1(t_key_maps *key_maps);
void					set_key_actions_2(t_key_maps *key_maps);
void					set_key_actions_3(t_key_maps *key_maps);
void					set_key_actions_4(t_key_maps *key_maps);
void					set_key_actions_5(t_key_maps *key_maps);

/* Toggle Helpers */ // Cleanup
int						handle_t(int keycode, t_events *events);
int						handle_j(int keycode, t_events *events);
int						handle_tesselation_up(int keycode, t_events *events);
int						handle_tesselation_down(int keycode, t_events *events);
int						handle_lod_up(int keycode, t_events *events);
int						handle_lod_down(int keycode, t_events *events);
int						handle_bracket(int keycode, t_events *events);
int						handle_manual_mode(int keycode, t_events *events);
void					handle_tesselation_points(int keycode, t_graphics *g);

void					set_key_actions(t_key_maps *key_maps);
void					set_key_releases(t_key_maps *key_maps);
void					calculate_fps(t_events *events);

void					clamp_values(t_events *events);
void					apply_plus_changes(t_events *events);
void					apply_minus_changes(t_events *events);
void					apply_zero_changes(t_events *events);
int						check_if_changed(t_events *events, t_combo_ctx *ctx);

void					init_movement_ctx(t_movement_ctx *ctx,
							t_events *events);
void					calculate_movement_vector(t_movement_ctx *ctx,
							t_events *events);
void					apply_movement(t_movement_ctx *ctx, t_events *events);
void					clamp_offset(t_events *events);

#endif
