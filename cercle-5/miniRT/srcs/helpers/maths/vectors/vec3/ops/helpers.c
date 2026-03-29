#define _GNU_SOURCE
#include <math.h>
#include "maths.h"

void	vec3_orthonormal_basis(t_vec3 normal, t_vec3 *tangent,
		t_vec3 *bitangent)
{
	t_vec3	up;

	if (fabs(normal.y) > 0.9)
		up = vec3(1, 0, 0);
	else
		up = vec3(0, 1, 0);
	*bitangent = vec3_norm(vec3_cross(normal, up));
	*tangent = vec3_norm(vec3_cross(*bitangent, normal));
}

t_vec3	vec3_reflect(t_vec3 I, t_vec3 N)
{
	return (vec3_sub(I, vec3_scale(N, 2 * vec3_dot(I, N))));
}

t_vec3	vec3_refract(t_vec3 I, t_vec3 N, double ior)
{
	double	cosi;
	double	etai;
	double	etat;
	t_vec3	n;
	double	tmp;
	double	eta;
	double	k;

	cosi = -fmax(-1.0, fmin(1.0, vec3_dot(I, N)));
	etai = 1.0;
	etat = ior;
	n = N;
	if (cosi < 0)
	{
		cosi = -cosi;
		n = vec3_scale(N, -1.0);
		tmp = etai;
		etai = etat;
		etat = tmp;
	}
	eta = etai / etat;
	k = 1.0 - eta * eta * (1.0 - cosi * cosi);
	if (k < 0)
		return ((t_vec3){0, 0, 0, 0});
	return (vec3_add(vec3_scale(I, eta), vec3_scale(n, eta * cosi - sqrt(k))));
}

t_vec3	rotate_vector(t_vec3 v, double pitch, double yaw)
{
	double	cp;
	double	sp;
	double	cy;
	double	sy;
	double	y1;
	double	z1;
	double	x2;
	double	y2;

	sp = sin(pitch);
	cp = cos(pitch);
	sy = sin(yaw);
	cy = cos(yaw);
	y1 = v.y * cp - v.z * sp;
	z1 = v.y * sp + v.z * cp;
	x2 = v.x * cy - y1 * sy;
	y2 = v.x * sy + y1 * cy;
	return (vec3(x2, y2, z1));
}

t_vec3	get_camera_forward(double pitch, double yaw)
{
	double	cp;
	double	sp;
	double	cy;
	double	sy;

	sp = sin(pitch);
	cp = cos(pitch);
	sy = sin(yaw);
	cy = cos(yaw);
	return (vec3(cp * sy, sp, cp * cy));
}
