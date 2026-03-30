#include "raytracing.h"
#include "objects.h"
#include <math.h>

static void	get_box_axes(t_box *bx, t_vec3 ax[3])
{
	if (vec3_mag_sq(bx->transform.forward) < 1e-6)
		ax[0] = vec3(1, 0, 0);
	else
		ax[0] = vec3_norm(bx->transform.forward);
	vec3_orthonormal_basis(ax[0], &ax[1], &ax[2]);
}

t_aabb	box_aabb(t_box *bx)
{
	t_aabb	aabb;
	t_vec3	ax[3];
	t_vec3	corner;
	double	sx;
	double	sy;
	double	sz;
	int		i;

	get_box_axes(bx, ax);
	aabb = aabb_create_empty();
	i = 0;
	while (i < 8)
	{
		sx = (double)((i & 1) * 2 - 1);
		sy = (double)((((i >> 1) & 1)) * 2 - 1);
		sz = (double)((((i >> 2) & 1)) * 2 - 1);
		corner = vec3_add(bx->transform.pos,
				vec3_add(vec3_scale(ax[0], sx * bx->half_extents.x),
					vec3_add(vec3_scale(ax[1], sy * bx->half_extents.y),
						vec3_scale(ax[2], sz * bx->half_extents.z))));
		aabb_expand_point(&aabb, corner);
		i++;
	}
	return (aabb);
}
