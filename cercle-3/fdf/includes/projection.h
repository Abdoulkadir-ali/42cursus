#ifndef PROJECTION_H
# define PROJECTION_H

# include "vectors.h"
# include "map.h"

/* ========== PROJECTION TYPES ========== */
typedef enum e_projection_type
{
	PROJ_ISOMETRIC = 0,
	PROJ_ORTHOGRAPHIC,
	PROJ_PERSPECTIVE,
	PROJ_OBLIQUE,
	PROJ_CAMERA_MATRIX,
	PROJ_NONLINEAR,
	PROJ_COUNT
}	t_projection_type;

// Forward declarations
typedef struct s_camera	t_camera;

/* ========== PROJECTION NAMES ========== */
extern const char	*g_projection_names[PROJ_COUNT];

/* ========== PROJECTION FUNCTIONS ========== */
// Apply selected projection to a 3D point
t_point	project_point(t_point p3d, t_camera cam, t_projection_type type);

// Individual projection algorithms
t_point	project_isometric(t_point p3d, t_camera cam);
t_point	project_orthographic(t_point p3d, t_camera cam);
t_point	project_perspective(t_point p3d, t_camera cam);
t_point	project_oblique(t_point p3d, t_camera cam);
t_point	project_camera_matrix(t_point p3d, t_camera cam);
t_point	project_nonlinear(t_point p3d, t_camera cam);

#endif
