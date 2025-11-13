/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 16:20:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/13 18:20:25 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_H
# define CORE_H

# include "events.h"
# include "graphics.h"
# include "gui.h"
# include <X11/keysym.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_data
{
	void				*mlx_ptr;
	void				*win_ptr;
	t_window			*window;
	t_graphics			*graphics;
	t_maps				map_manager;
	t_gui				*gui;
	t_camera			*camera;
	t_camera_context	*camera_ctx;
}						t_data;

/* ========== WINDOW CONSTANTS ========== */
# define WINDOW_WIDTH_RATIO 0.85
# define WINDOW_HEIGHT_RATIO 0.85
# define MIN_WINDOW_WIDTH 1024
# define MIN_WINDOW_HEIGHT 768
# define MAX_WINDOW_WIDTH 1920
# define MAX_WINDOW_HEIGHT 1080

/* ========== OPTIMIZATION DEFAULTS ========== */
# define DEFAULT_LOD_LEVEL 2
# define DEFAULT_Z_SCALE 1.0
# define DEFAULT_FRUSTUM_MARGIN 50
# define DEFAULT_DAMPENING_THRESHOLD 0
# define DEFAULT_SPLINE_SEGMENTS 10
# define MIN_LOD_LEVEL 1
# define MAX_LOD_LEVEL 10
# define MIN_Z_SCALE 0.1
# define MIN_FRUSTUM_MARGIN 0
# define MAX_FRUSTUM_MARGIN 500
# define MIN_DAMPENING_THRESHOLD -100
# define MAX_DAMPENING_THRESHOLD 100
# define MIN_SPLINE_SEGMENTS 2
# define MAX_SPLINE_SEGMENTS 50

void					init_window_size(t_data *data);
void					init_mouse(t_mouse *mouse);
void					init_keys(t_keys *keys);
void					init_map_config(t_data *data);
int						init_and_render(t_data *data);
t_events				*init_events(t_data *data);
int						cleanup_and_exit(t_events *events);

#endif