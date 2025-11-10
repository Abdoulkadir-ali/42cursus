#include "fdf.h"
#include "projection.h"

// Oblique projection (cabinet projection, 45 degree angle)
t_point	project_oblique(t_point p3d, t_camera cam)
{
	t_vec3d	v;
	t_vec3d	rotated;
	t_point	p2d;
	double	oblique_angle;
	double	oblique_factor;

	v.x = (double)p3d.pos.x;
	v.y = (double)p3d.pos.y;
	v.z = (double)p3d.pos.z;
	rotated = apply_rotation(v, cam.rotation);
	oblique_angle = 0.785398;
	oblique_factor = 0.5;
	p2d.pos.x = (rotated.x + rotated.y * cos(oblique_angle) * oblique_factor)
		* cam.scale;
	p2d.pos.y = (-rotated.z + rotated.y * sin(oblique_angle) * oblique_factor)
		* cam.scale;
	p2d.pos.x += cam.offset.x;
	p2d.pos.y += cam.offset.y;
	p2d.pos.z = rotated.z;
	p2d.color = p3d.color;
	return (p2d);
}

// Camera matrix projection (full 3D camera transformation)
t_point	project_camera_matrix(t_point p3d, t_camera cam)
{
	t_vec3d	v;
	t_vec3d	rotated;
	t_point	p2d;
	double	fov;
	double	aspect;
	double	f;

	v.x = (double)p3d.pos.x;
	v.y = (double)p3d.pos.y;
	v.z = (double)p3d.pos.z;
	rotated = apply_rotation(v, cam.rotation);
	fov = 1.047;
	aspect = 1.333;
	f = 1.0 / tan(fov / 2.0);
	p2d.pos.x = (rotated.x * f / aspect) * cam.scale * 10;
	p2d.pos.y = (rotated.z * f) * cam.scale * 10;
	p2d.pos.x += cam.offset.x;
	p2d.pos.y += cam.offset.y;
	p2d.pos.z = rotated.z;
	p2d.color = p3d.color;
	return (p2d);
}

// Nonlinear projection (artistic/warped projection)
t_point	project_nonlinear(t_point p3d, t_camera cam)
{
	t_vec3d	v;
	t_vec3d	rotated;
	t_point	p2d;
	double	warp_x;
	double	warp_y;

	v.x = (double)p3d.pos.x;
	v.y = (double)p3d.pos.y;
	v.z = (double)p3d.pos.z;
	rotated = apply_rotation(v, cam.rotation);
	warp_x = sin(rotated.y * 0.05) * 5;
	warp_y = cos(rotated.x * 0.05) * 5;
	p2d.pos.x = (rotated.x + warp_x - rotated.y) * cos(0.523599) * cam.scale;
	p2d.pos.y = ((rotated.x + rotated.y) * sin(0.523599)
			- rotated.z + warp_y) * cam.scale;
	p2d.pos.x += cam.offset.x;
	p2d.pos.y += cam.offset.y;
	p2d.pos.z = rotated.z;
	p2d.color = p3d.color;
	return (p2d);
}
