/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 16:11:35 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/21 22:34:10 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

/* ========== REQUIREMENTS ========== */
# include <math.h>

/* ========== PROJECT IMPORTS ========== */
# include "map.h"
# include "vectors.h"
# include "window.h"

/* ========== GUI STYLE ========== */
typedef enum e_gui_style
{
	GUI_STYLE_TRON_BLUE,
	GUI_STYLE_TRON_ORANGE,
	GUI_STYLE_MATRIX,
	GUI_STYLE_CYBERPUNK,
	GUI_STYLE_NEON_GRID,
	GUI_STYLE_COUNT
}						t_gui_style;

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

typedef enum e_projection_type
{
	PROJ_ISOMETRIC,
	PROJ_ORTHOGRAPHIC,
	PROJ_PERSPECTIVE,
	PROJ_OBLIQUE,
	PROJ_CAMERA_MATRIX,
	PROJ_NONLINEAR,
	PROJ_COUNT
}						t_projection_type;

/* ========== CAMERA CONTEXT ========== */
typedef struct s_camera
{
	t_vec3d				rotation;
	t_vec2d				offset;
	t_vec3d				grid_center;
	t_vec3				color_shift;
	t_projection_type	projection;
	int					gui_style;
	double				scale;
	double				target_scale;
	double				move_speed;
	double				zoom_speed;
	int					dampening_threshold;
	t_vec2d				pending_rot;
	double				z_scale;
	int					frustum_margin;
	int					spline_segments;
	int					use_z_divisor;
	int					invert_movement;
}						t_camera;

/* ========== CAMERA MANAGER ========== */
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

t_point					project_point(t_vec3d p3d, int color, t_camera *cam,
							double z_divisor);
t_point					project_isometric(t_point p3d, t_camera *cam);
t_point					project_orthographic(t_point p3d, t_camera *cam);
t_point					project_perspective(t_point p3d, t_camera *cam);
t_point					project_oblique(t_point p3d, t_camera *cam);
t_point					project_camera_matrix(t_point p3d, t_camera *cam);
t_point					project_nonlinear(t_point p3d, t_camera *cam);

t_vec3d					apply_rotation(t_vec3d v, t_vec3d rot);
t_vec3d					apply_rotation_centered(t_vec3d v, t_vec3d rot,
							t_vec3d center);
t_vec3d					rotate_x(t_vec3d v, double angle);
t_vec3d					rotate_y(t_vec3d v, double angle);
t_vec3d					rotate_z(t_vec3d v, double angle);

void					adjust_camera_to_map(t_camera_manager *ctx);
void					reset_style(t_camera *camera);
void					zoom_in(t_camera_manager *ctx);
void					zoom_out(t_camera_manager *ctx);
void					update_zoom(t_camera_manager *ctx);

t_camera				*init_camera_object(void);
t_camera_manager		*init_camera(t_camera_args args);

#endif
