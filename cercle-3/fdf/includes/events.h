/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 19:41:27 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/13 02:46:40 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTS_H
# define EVENTS_H

# include "camera.h"
# include "graphics.h"
# include "gui.h"
# include "libft.h"
# include "map.h"
# include "window.h"
# include <X11/keysym.h>

/* ========== OPTIMIZATION DEFAULTS ========== */
# define DEFAULT_LOD_LEVEL 1
# define DEFAULT_Z_SCALE 1.0
# define DEFAULT_FRUSTUM_MARGIN 50
# define DEFAULT_DAMPENING_THRESHOLD 0
# define DEFAULT_SPLINE_SEGMENTS 10
# define MIN_LOD_LEVEL 1
# define MAX_LOD_LEVEL 10
# define MIN_Z_SCALE 0.1
# define MAX_Z_SCALE 5.0
# define MIN_FRUSTUM_MARGIN 0
# define MAX_FRUSTUM_MARGIN 500
# define MIN_DAMPENING_THRESHOLD -100
# define MAX_DAMPENING_THRESHOLD 100
# define MIN_SPLINE_SEGMENTS 2
# define MAX_SPLINE_SEGMENTS 50
# define KEY_MAP_SIZE 0x10000



typedef int			(*key_action_t)(int keycode, t_events *events);

typedef struct s_key_maps
{
	key_action_t	key_actions[KEY_MAP_SIZE];
	key_action_t	key_releases[KEY_MAP_SIZE];
}					t_key_maps;

typedef struct s_events
{
	t_camera		*camera;
	t_window		*window;
	t_map			*map;
	t_graphics		*graphics;
	t_gui			*gui;
	int				render_mode;
	int				lod_level;
	int				use_depth_culling;
	int				fill_triangles;
	t_key_maps		key_maps;
}					t_events;

int					mouse_press(int button, int x, int y, t_events *events);
int					mouse_release(int button, int x, int y, t_events *events);
int					mouse_move(int x, int y, t_events *events);

int					key_press(int keycode, t_events *events);
int					key_release(int keycode, t_events *events);

int					loop_hook(t_events *events);

int					process_movement(t_events *events);

void				cycle_projection(t_events *events);
void				reset_view(t_events *events);
void				adjust_move_speed(t_events *events, int increase);
int					cleanup_and_exit(t_events *events);
void				setup_hooks(t_events *events);

/* Key action functions */
int					handle_escape(int keycode, t_events *events);
int					handle_r(int keycode, t_events *events);
int					handle_p(int keycode, t_events *events);
int					handle_n(int keycode, t_events *events);
int					handle_s(int keycode, t_events *events);
int					handle_a(int keycode, t_events *events);
int					handle_x(int keycode, t_events *events);
int					handle_i(int keycode, t_events *events);
int					handle_v(int keycode, t_events *events);
int					handle_g(int keycode, t_events *events);
int					handle_plus(int keycode, t_events *events);
int					handle_minus(int keycode, t_events *events);
int					handle_0(int keycode, t_events *events);
int					handle_up(int keycode, t_events *events);
int					handle_down(int keycode, t_events *events);
int					handle_left(int keycode, t_events *events);
int					handle_right(int keycode, t_events *events);
int					handle_press_flag(int keycode, t_events *events);
int					handle_release_flag(int keycode, t_events *events);

void				init_key_actions(t_key_maps *key_maps);

#endif
