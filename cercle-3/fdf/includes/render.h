/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 16:11:35 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/17 21:05:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

/* ========== REQUIREMENTS ========== */
# include <math.h>

/* ========== MODULE IMPORTS ========== */
# include "geometry.h"
# include "window.h"

/* Forward declaration for circular dependency with Graphics */
typedef struct s_graphics	t_graphics;

/* ========== CAMERA CONSTANTS ========== */
# define DEFAULT_ZOOM_AVAILABLE_WIDTH 0.8
# define DEFAULT_ZOOM_AVAILABLE_HEIGHT 0.8
# define DEFAULT_ZOOM_PADDING 1.0
# define DEFAULT_ZOOM_MIN 0.1
# define DEFAULT_ZOOM_MAX 10.0
# define DEFAULT_Y_ADJUST_FACTOR 0.5
# define DEFAULT_CAMERA_ROTATION_X 0.0
# define DEFAULT_CAMERA_ROTATION_Y 0.0
# define DEFAULT_CAMERA_ROTATION_Z 0.0
# define DEFAULT_DAMPENING_THRESHOLD 0
# define DEFAULT_Z_SCALE 1.0
# define DEFAULT_FRUSTUM_MARGIN 50
# define DEFAULT_SPLINE_SEGMENTS 10

typedef enum e_gui_style
{
	GUI_STYLE_TRON_BLUE,
	GUI_STYLE_TRON_ORANGE,
	GUI_STYLE_MATRIX,
	GUI_STYLE_CYBERPUNK,
	GUI_STYLE_NEON_GRID,
	GUI_STYLE_COUNT
}						t_gui_style;

typedef enum e_projection_type
{
	PROJ_PARALLEL,
	PROJ_CONIC,
	PROJ_COUNT
}						t_projection_type;

/* ========== CAMERA structs ========== */

typedef struct s_camera
{
	t_vec3d				rotation;
	t_vec2d				offset;
	t_vec3d				grid_center;
	t_vec3				color_shift;
	t_projection_type	projection;
	t_vec3d				rotation_matrix[3];
	int					gui_style;
	double				scale;
	double				target_scale;
	double				move_speed;
	double				zoom_speed;
	unsigned int		dampening_threshold;
	t_vec2d				pending_rot;
	double				z_scale;
	unsigned int		frustum_margin;
	unsigned int		spline_segments;
	int					use_z_divisor;
	int					invert_movement;
	double				alpha;
	t_matrix4			transform_matrix;
}						t_camera;

typedef struct s_rot_ctx
{
	t_vec3d				rot;
	t_vec3d				cos;
	t_vec3d				sin;
}						t_rot_ctx;

typedef struct s_camera_manager
{
	t_camera			*camera;
	t_map				*map;
	t_window			*window;
}						t_camera_manager;

typedef struct s_camera_args
{
	t_map				*map;
	t_window			*window;
	t_maps				*manager;
	char				*map_file;
}						t_camera_args;

/* ========== CAMERA PROTOTYPES ========== */
t_camera				*init_camera_object(void);
t_camera_manager		*init_camera(t_camera_args args);

void					update_rotation_matrix(t_camera *cam);
void					compose_rotation_matrix(t_camera *cam, t_rot_ctx *ctx);
void					build_rotation_matrices(t_vec3d rx[3], t_vec3d ry[3],
							t_vec3d rz[3], t_rot_ctx *ctx);
t_vec3d					apply_rotation_with_matrix(t_vec3d v, t_camera *cam);
t_vec3d					apply_rotation_centered_with_matrix(t_vec3d v,
							t_camera *cam);

void					adjust_camera_to_map(t_camera_manager *ctx);
void					center_camera_on_map(t_camera_manager *ctx);
void					reset_style(t_camera *camera);
void					zoom_in(t_camera_manager *ctx);
void					zoom_out(t_camera_manager *ctx);
void					update_zoom(t_camera_manager *ctx);
void					recenter_camera_on_resize(t_camera *cam, int old_w,
							int old_h, int new_w, int new_h);

/* ========== PIPELINE PROTOTYPES ========== */
/* 
** The main entry point for transforming a 3D point to 2D screen coordinates.
** Applies: Model -> View -> Projection transformations.
*/
t_point		project_point(t_vec3d p3d, int color, t_camera *cam,
				double z_divisor);

/* Orchestrates the full rendering pipeline */
void		render_scene(t_graphics *g);

/* Unified Data-Driven Projection */
t_matrix4	get_projection_matrix(t_camera *cam, float aspect);
t_point		project_unified(t_point p3d, t_camera *cam);
void		calculate_transform_matrix(t_camera *cam);
t_point		apply_transform(t_point p, t_camera *cam);
void		transform_scanline(t_graphics *g, t_point *out, size_t row_idx, size_t width);

/* Culling Stages */
int			is_point_visible(t_vec3d p, t_graphics *g);
int			is_visible(int x, int y, t_graphics *g);
int			is_on_screen(int x, int y, t_graphics *g);
int			is_map_visible(t_graphics *g);
void		get_visible_map_bounds(t_graphics *g, t_vec2 *min, t_vec2 *max); // Smart Culling
int			should_draw_line(t_point p1, t_point p2, t_graphics *g);
int			is_backface(t_point p1, t_point p2, t_point p3);

#endif
