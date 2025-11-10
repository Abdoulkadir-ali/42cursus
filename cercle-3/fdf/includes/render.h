#ifndef RENDER_H
# define RENDER_H

# include "map.h"
# include "controls.h"

// Forward declaration
typedef struct s_data	t_data;

/* ========== ROTATION FUNCTIONS ========== */
// 3D rotation transformations
inline t_vec3d	rotate_x(t_vec3d v, double angle);
inline t_vec3d	rotate_y(t_vec3d v, double angle);
inline t_vec3d	rotate_z(t_vec3d v, double angle);
t_vec3d			apply_rotation(t_vec3d v, t_rotation rot);

/* ========== PROJECTION FUNCTIONS ========== */
// Convert 3D points to 2D screen coordinates
t_point	project_isometric(t_point p3d, t_camera cam);

/* ========== DRAWING FUNCTIONS ========== */
// Line drawing with color interpolation
void	draw_line(t_data *data, t_point start, t_point end);

// Draw entire grid
void	draw_grid(t_data *data);

// Redraw entire scene
void	redraw(t_data *data);

/* ========== VISUAL STYLE FUNCTIONS ========== */
extern const char	*g_style_names[];
int		get_styled_color(int base_z, int min_z, int max_z, int style);
int		get_background_color(int style);
void	cycle_visual_style(t_data *data);
void	apply_style_to_map(t_data *data);

#endif
