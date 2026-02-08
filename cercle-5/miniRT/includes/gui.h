/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 00:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GUI_H
# define GUI_H

# include "libft.h"
# include "maths.h"
# include "mlx.h"
# include "raytracing.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <dirent.h>
# include <pthread.h>
# include <stdio.h>
#include <sys/time.h>

# define THREAD_COUNT 12
# define TILE_SIZE 16

# define ZOOM_SPEED 2.0
# define MOUSE_SENSITIVITY 0.005

typedef struct s_gui t_gui;

typedef struct s_render_ctx
{
	t_gui			*gui;
	// Synchronization
	pthread_mutex_t	mutex;
	int				next_tile_id;
	int				total_tiles;
	int				tiles_x;

	// Pre-calculated camera data (read-only for threads)
	t_vec3			cam_pos;
	t_vec3 forward, right, up;
	double half_width, half_height, aspect_ratio;
	int				step;
}					t_render_ctx;

typedef struct s_gui
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				width;
	int				height;
	t_scene			*scene;
	t_bvh			*bvh;
	t_camera *camera; // Updated from t_object *

	// Camera Control State
	t_rotator		rotation;
	t_rotator		target_rotation;
	t_vec3			target_position;
	double			target_fov;
	double			move_speed;
	double			lerp_factor;
	int render_scale; // 1 for full, 2/4 for low res
	bool dirty;       // Frame needs update

	// Input State
	int				move_forward_count;
	bool			moving_forward;
	int				move_backward_count;
	bool			moving_backward;
	int				move_left_count;
	bool			moving_left;
	int				move_right_count;
	bool			moving_right;
	int				move_up_count;
	bool			moving_up;
	int				move_down_count;
	bool			moving_down;

	int				zoom_in_count;
	bool			zooming_in;
	int				zoom_out_count;
	bool			zooming_out;

	bool			mouse_left_pressed;
	bool			mouse_middle_pressed;
	int				last_mouse_x;
	int				last_mouse_y;

	// Timing & FPS
	double			fps;
	long long		last_time;

	// Hovering
	int				mouse_x;
	int				mouse_y;

	// Map Switcher
	char			**maps;
	int				map_count;
	int				current_map_idx;

	void			*widgets;
}					t_gui;

typedef struct s_key_action
{
	int				key;
	void			(*press_action)(t_gui *gui);
	void			(*release_action)(t_gui *gui);
}					t_key_action;


t_gui				*gui_init(t_scene *scene, t_bvh *bvh);
void				gui_loop(t_gui *gui);
void				gui_render(t_gui *gui);
void				gui_destroy(t_gui *gui);
void				widget_list_draw(void *widgets, t_gui *gui);

// Map Switcher
void				gui_map_switcher_init(t_gui *gui);
void				gui_next_map(t_gui *gui);

// Input Callbacks
int					key_press(int keycode, t_gui *gui);
int					key_release(int keycode, t_gui *gui);
int					mouse_click(int button, int x, int y, t_gui *gui);
int					mouse_release(int button, int x, int y, t_gui *gui);
int					mouse_motion(int x, int y, t_gui *gui);

#endif
