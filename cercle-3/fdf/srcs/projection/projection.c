#include "fdf.h"
#include "projection.h"

// Projection type names for menu
const char	*g_projection_names[PROJ_COUNT] = {
	"Isometric",
	"Orthographic",
	"Perspective",
	"Oblique",
	"Camera Matrix",
	"Nonlinear"
};

// Main projection dispatcher
t_point	project_point(t_point p3d, t_camera cam, t_projection_type type)
{
	if (type == PROJ_ISOMETRIC)
		return (project_isometric(p3d, cam));
	else if (type == PROJ_ORTHOGRAPHIC)
		return (project_orthographic(p3d, cam));
	else if (type == PROJ_PERSPECTIVE)
		return (project_perspective(p3d, cam));
	else if (type == PROJ_OBLIQUE)
		return (project_oblique(p3d, cam));
	else if (type == PROJ_CAMERA_MATRIX)
		return (project_camera_matrix(p3d, cam));
	else if (type == PROJ_NONLINEAR)
		return (project_nonlinear(p3d, cam));
	return (project_isometric(p3d, cam));
}
