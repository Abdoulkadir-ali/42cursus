#ifndef DATA_H
# define DATA_H

# include "vectors.h"

typedef struct s_data				t_data;
typedef struct s_map				t_map;
typedef struct s_mouse				t_mouse;
typedef struct s_keys				t_keys;
typedef struct s_point				t_point;
typedef struct s_map_render_config	t_map_render_config;

# include "controls.h"
# include "map.h"
# include "camera.h"
# include "graphics.h"

typedef struct s_data
{
	void							*mlx_ptr;
	void							*win_ptr;
	t_graphics						graphics;
	t_map							*map;
	t_camera						camera;
	t_map							**maps;
	char							**map_files;
	int								map_count;
	int								current_map_index;
	t_mouse							mouse;
	t_keys							keys;
	long							last_frame_time;
	int								frame_in_progress;
}									t_data;

#endif