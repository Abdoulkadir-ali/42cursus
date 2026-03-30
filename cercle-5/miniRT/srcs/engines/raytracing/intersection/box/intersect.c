#include "raytracing.h"
#include "objects.h"
#include <math.h>

static void	get_box_axes_i(t_box *bx, t_vec3 ax[3])
{
	if (vec3_mag_sq(bx->transform.forward) < 1e-6)
		ax[0] = vec3(1, 0, 0);
	else
		ax[0] = vec3_norm(bx->transform.forward);
	vec3_orthonormal_basis(ax[0], &ax[1], &ax[2]);
}

bool	intersect_box(const t_ray *ray, t_box *bx, t_hit *hit)
{
	t_vec3	ax[3];
	t_vec3	oc;
	double	p[3];
	double	d_ax[3];
	double	h[3];
	double	t_min;
	double	t_max;
	double	ta;
	double	tb;
	double	tmp;
	int		face;
	int		i;
	double	entry;
	t_vec3	normal;

	get_box_axes_i(bx, ax);
	oc = vec3_sub(ray->origin, bx->transform.pos);
	h[0] = bx->half_extents.x;
	h[1] = bx->half_extents.y;
	h[2] = bx->half_extents.z;
	p[0] = vec3_dot(oc, ax[0]);
	p[1] = vec3_dot(oc, ax[1]);
	p[2] = vec3_dot(oc, ax[2]);
	d_ax[0] = vec3_dot(ray->direction, ax[0]);
	d_ax[1] = vec3_dot(ray->direction, ax[1]);
	d_ax[2] = vec3_dot(ray->direction, ax[2]);
	t_min = -1e30;
	t_max = 1e30;
	face = 0;
	i = 0;
	while (i < 3)
	{
		if (fabs(d_ax[i]) < 1e-8)
		{
			if (p[i] < -h[i] || p[i] > h[i])
				return (false);
		}
		else
		{
			ta = (-h[i] - p[i]) / d_ax[i];
			tb = (h[i] - p[i]) / d_ax[i];
			if (ta > tb)
			{
				tmp = ta;
				ta = tb;
				tb = tmp;
			}
			if (ta > t_min)
			{
				t_min = ta;
				face = i;
			}
			if (tb < t_max)
				t_max = tb;
			if (t_min > t_max)
				return (false);
		}
		i++;
	}
	if (t_min < 1e-6)
		return (false);
	entry = p[face] + t_min * d_ax[face];
	if (entry < 0.0)
		normal = vec3_scale(ax[face], -1.0);
	else
		normal = ax[face];
	if (vec3_dot(ray->direction, normal) > 0.0)
		normal = vec3_scale(normal, -1.0);
	hit->t = t_min;
	hit->point = vec3_add(ray->origin, vec3_scale(ray->direction, t_min));
	hit->normal = normal;
	hit->u = 0.5;
	hit->v = 0.5;
	vec3_orthonormal_basis(hit->normal, &hit->tangent, &hit->bitangent);
	return (true);
}
