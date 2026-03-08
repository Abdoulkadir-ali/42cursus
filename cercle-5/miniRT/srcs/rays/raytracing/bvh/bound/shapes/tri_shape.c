#include "raytracing.h"

t_aabb	tri_shape_aabb(t_tri_shape *tr)
{
	t_aabb	bbox;

	bbox.min = vec3(
			fmin(tr->v[0].x, fmin(tr->v[1].x, tr->v[2].x)) - 1e-4,
			fmin(tr->v[0].y, fmin(tr->v[1].y, tr->v[2].y)) - 1e-4,
			fmin(tr->v[0].z, fmin(tr->v[1].z, tr->v[2].z)) - 1e-4);
	bbox.max = vec3(
			fmax(tr->v[0].x, fmax(tr->v[1].x, tr->v[2].x)) + 1e-4,
			fmax(tr->v[0].y, fmax(tr->v[1].y, tr->v[2].y)) + 1e-4,
			fmax(tr->v[0].z, fmax(tr->v[1].z, tr->v[2].z)) + 1e-4);
	return (bbox);
}
