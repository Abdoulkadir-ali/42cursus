/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 19:41:31 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/10 22:21:39 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

/* ========== SYSTEM INCLUDES ========== */
# include <mlx.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>

/* ========== PROJECT HEADERS ========== */
# include "vectors.h"
# include "color.h"
# include "map.h"
# include "projection.h"
# include "controls.h"
# include "render.h"
# include "events.h"
# include "map_style.h"
# include "gui_style.h"

/* ========== WINDOW CONSTANTS ========== */
# define WINDOW_WIDTH_RATIO 0.85
# define WINDOW_HEIGHT_RATIO 0.85
# define MIN_WINDOW_WIDTH 1024
# define MIN_WINDOW_HEIGHT 768
# define MAX_WINDOW_WIDTH 2560
# define MAX_WINDOW_HEIGHT 1440

/* ========== CAMERA DEFAULT SETTINGS ========== */
# define DEFAULT_CAMERA_ROTATION_X -0.5
# define DEFAULT_CAMERA_ROTATION_Y 0.5
# define DEFAULT_CAMERA_ROTATION_Z 0.0
# define DEFAULT_ZOOM_AVAILABLE_WIDTH 0.7
# define DEFAULT_ZOOM_AVAILABLE_HEIGHT 0.7
# define DEFAULT_ZOOM_PADDING 1.2
# define DEFAULT_ZOOM_MIN 3.0
# define DEFAULT_ZOOM_MAX 60.0
# define DEFAULT_Y_ADJUST_FACTOR 0.5

/* ========== FRAME RATE SETTINGS ========== */
# define MAX_ROTATION_SPEED 0.005
# define MAX_PENDING_ROTATION 0.1
# define MIN_FRAME_TIME 16
# define TARGET_FRAME_TIME 16

/* ========== RENDER MODE ========== */
typedef enum e_render_mode
{
	RENDER_LINES,
	RENDER_SPLINES,
	RENDER_TRIANGLES,
	RENDER_MODE_COUNT
}	t_render_mode;

/* ========== OPTIMIZATION DEFAULTS ========== */
# define DEFAULT_LOD_LEVEL 1
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

/* ========== MAIN DATA STRUCTURE ========== */
// Central structure containing all program state
typedef struct s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img;
	char		*img_addr;
	int			img_bpp;
	int			img_line_len;
	int			img_endian;
	void		*gui_img;
	char		*gui_addr;
	int			gui_bpp;
	int			gui_line_len;
	int			gui_endian;
	int					win_width;
	int					win_height;
	t_map				*map;
	t_map				**maps;
	char				**map_files;
	int					map_count;
	int					current_map_index;
	t_camera			camera;
	t_mouse				mouse;
	t_keys				keys;
	t_buttons			buttons;
	t_map_render_config	map_config;
	long				last_frame_time;
	int					frame_in_progress;
	int					lod_level;
	t_render_mode		render_mode;
	float				*z_buffer;
	int					use_depth_culling;
}	t_data;

/* ========== INITIALIZATION FUNCTIONS ========== */
void	init_window_size(t_data *data);
void	init_mouse(t_data *data);
void	init_keys(t_data *data);
void	init_map_config(t_data *data);
void	init_camera(t_data *data);
void	adjust_camera_to_map(t_data *data);

#endif
