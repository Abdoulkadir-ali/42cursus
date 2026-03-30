#include "raytracing.h"

t_aabb	rect_aabb(t_rect *rc)
{
	t_aabb	bbox;
	int		i;

	bbox.min = rc->v[0];
	bbox.max = rc->v[0];
	i = 1;
	while (i < 4)
	{
		if (rc->v[i].x < bbox.min.x) bbox.min.x = rc->v[i].x;
		if (rc->v[i].y < bbox.min.y) bbox.min.y = rc->v[i].y;
		if (rc->v[i].z < bbox.min.z) bbox.min.z = rc->v[i].z;
		if (rc->v[i].x > bbox.max.x) bbox.max.x = rc->v[i].x;
		if (rc->v[i].y > bbox.max.y) bbox.max.y = rc->v[i].y;
		if (rc->v[i].z > bbox.max.z) bbox.max.z = rc->v[i].z;
		i++;
	}
	bbox.min.x -= 1e-4;
	bbox.min.y -= 1e-4;
	bbox.min.z -= 1e-4;
	bbox.max.x += 1e-4;
	bbox.max.y += 1e-4;
	bbox.max.z += 1e-4;
	return (bbox);
}
