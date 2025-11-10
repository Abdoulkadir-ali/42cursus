#include "fdf.h"

// Rotate vector around X axis
t_vec3d	rotate_x(t_vec3d v, double angle)
{
	t_vec3d	rotated;

	rotated.x = v.x;
	rotated.y = v.y * cos(angle) - v.z * sin(angle);
	rotated.z = v.y * sin(angle) + v.z * cos(angle);
	return (rotated);
}

// Rotate vector around Y axis
t_vec3d	rotate_y(t_vec3d v, double angle)
{
	t_vec3d	rotated;

	rotated.x = v.x * cos(angle) + v.z * sin(angle);
	rotated.y = v.y;
	rotated.z = -v.x * sin(angle) + v.z * cos(angle);
	return (rotated);
}

// Rotate vector around Z axis
t_vec3d	rotate_z(t_vec3d v, double angle)
{
	t_vec3d	rotated;

	rotated.x = v.x * cos(angle) - v.y * sin(angle);
	rotated.y = v.x * sin(angle) + v.y * cos(angle);
	rotated.z = v.z;
	return (rotated);
}

// Apply all rotations to a vector
t_vec3d	apply_rotation(t_vec3d v, t_rotation rot)
{
	t_vec3d	rotated;

	rotated = rotate_x(v, rot.x);
	rotated = rotate_y(rotated, rot.y);
	rotated = rotate_z(rotated, rot.z);
	return (rotated);
}
