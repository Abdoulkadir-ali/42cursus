/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 16:11:35 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/26 19:56:07 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

/* ========== REQUIREMENTS ========== */
# include <math.h>

/* ========== MODULE IMPORTS ========== */
# include "define.h"
# include "geometry.h"
# include "math.h"
# include "primitives.h"
# include "window.h"

/* Forward declaration for circular dependency with Graphics */
typedef struct s_graphics	t_graphics;

typedef enum e_gui_style
{
	GUI_STYLE_TRON_BLUE,
	GUI_STYLE_TRON_ORANGE,
	GUI_STYLE_MATRIX,
	GUI_STYLE_CYBERPUNK,
	GUI_STYLE_NEON_GRID,
	GUI_STYLE_COUNT
}							t_gui_style;

typedef enum e_projection_type
{
	PROJ_PARALLEL,
	PROJ_CONIC,
	PROJ_COUNT
}							t_projection_type;

/* ========== CAMERA structs ========== */

typedef struct s_camera
{
	t_vec3d					rotation;
	t_vec2d					offset;
	t_vec3d					grid_center;
	t_vec3					color_shift;
	t_projection_type		projection;
	t_vec3d					rotation_matrix[3];
	int						gui_style;
	double					scale;
	double					target_scale;
	double					move_speed;
	double					zoom_speed;
	unsigned int			dampening_threshold;
	t_vec2d					pending_rot;
	double					z_scale;
	unsigned int			frustum_margin;
	int						use_z_divisor;
	int						invert_movement;
	double					alpha;
	float					view_dist;
	double					rotation_speed;
	t_vec3d					target_rotation;
	t_matrix4				transform_matrix;
}							t_camera;

typedef struct s_rot_ctx
{
	t_vec3d					rot;
	t_vec3d					cos;
	t_vec3d					sin;
}							t_rot_ctx;

typedef struct s_transform_ctx
{
	t_matrix4				rot;
	t_matrix4				view;
	t_matrix4				proj;
	t_matrix4				mvp;
	float					scale_factor;
	t_matrix4				screen_scale;
}							t_transform_ctx;

typedef struct s_update_ctx
{
	t_vec2					*min;
	t_vec2					*max;
}							t_update_ctx;

typedef struct s_matrix_result
{
	float					x;
	float					y;
	float					w;
}							t_matrix_result;

typedef struct s_camera_manager
{
	t_camera				*camera;
	t_map					*map;
	t_window				*window;
}							t_camera_manager;

typedef struct s_camera_args
{
	t_map					*map;
	t_window				*window;
	t_maps					*manager;
	char					*map_file;
}							t_camera_args;

/* ========== CAMERA PROTOTYPES ========== */

t_camera					*init_camera_default(t_camera *cam);
t_camera_manager			*init_camera(t_camera_args args);
t_camera_manager			*allocate_camera_manager(t_camera_args args);
int							setup_map_source(t_maps *mgr, t_camera_args args);

void						update_rotation_matrix(t_camera *cam);
void						compose_rotation_matrix(t_camera *cam,
								t_rot_ctx *ctx);
void						build_rotation_matrices(t_vec3d rx[3],
								t_vec3d ry[3], t_vec3d rz[3], t_rot_ctx *ctx);
t_vec3d						apply_rotation_with_matrix(t_vec3d v,
								t_camera *cam);

void						adjust_camera_to_map(t_camera_manager *ctx);
void						center_camera_on_map(t_camera_manager *ctx);
void						reset_style(t_camera *camera);
void						zoom_in(t_camera_manager *ctx);
void						zoom_out(t_camera_manager *ctx);
void						update_zoom(t_camera_manager *ctx);
void						recenter_camera_on_resize(t_camera *cam,
								t_vec2 old_size, t_vec2 new_size);

/* Orchestrates the full rendering pipeline */
void						render_scene(t_graphics *g);

/* Unified Data-Driven Projection */
t_matrix4					get_projection_matrix(t_camera *cam, float aspect);

void						calculate_transform_matrix(t_camera *cam);
t_point						apply_transform(t_point p, t_camera *cam);
void						transform_scanline(t_graphics *g, t_point *out,
								size_t row_idx, size_t width);

/* Culling Stages */

int							is_on_screen(t_vec2 pos, t_graphics *g);
t_point						project_helper(t_vec3d p3d, int color,
								t_graphics *g);
int							is_map_visible(t_graphics *g);
void						get_visible_map_bounds(t_graphics *g, t_vec2 *min,
								t_vec2 *max);
// Smart Culling
int							should_draw_line(t_point p1, t_point p2,
								t_graphics *g);
int							is_backface(t_point p1, t_point p2, t_point p3);

void						geometry_processing(t_graphics *g);
void						rasterization(t_graphics *g);

int							calculate_adaptive_level(t_graphics *g);
void						apply_tesselation(t_graphics *g, int level);
void						apply_lod(t_graphics *g, int level);

#endif
