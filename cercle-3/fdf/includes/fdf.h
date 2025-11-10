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

/* ========== WINDOW CONSTANTS ========== */
# define WINDOW_WIDTH_RATIO 0.4
# define WINDOW_HEIGHT_RATIO 0.4
# define MIN_WINDOW_WIDTH 800
# define MIN_WINDOW_HEIGHT 600

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
	int			win_width;
	int			win_height;
	t_map		*map;
	t_camera	camera;
	t_mouse		mouse;
	t_keys		keys;
	t_buttons	buttons;
}	t_data;

#endif
