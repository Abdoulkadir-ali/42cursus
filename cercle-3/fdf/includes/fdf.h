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
}	t_data;

#endif
