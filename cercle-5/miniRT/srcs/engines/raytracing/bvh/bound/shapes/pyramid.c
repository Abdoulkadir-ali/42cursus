#include "raytracing.h"
#include <math.h>

/*
** Pyramid AABB: walk all 5 vertices (4 base corners + apex).
** Base corners are derived from center, up, base_size (as in the intersector).
*/
t_aabb	pyramid_aabb(t_pyramid *py)
{
	t_aabb	bb;
	t_vec3	ref;
	t_vec3	right;
	t_vec3	fwd;
	t_vec3	apex;
	t_vec3	c[4];
	double	h;
	int		i;

	h = py->base_size * 0.5;
	if (fabs(py->up.y) < 0.9)
		ref = vec3(0, 1, 0);
	else
		ref = vec3(1, 0, 0);
	right = vec3_norm(vec3_cross(py->up, ref));
	fwd = vec3_cross(right, py->up);
	c[0] = vec3_add(vec3_add(py->transform.pos, vec3_scale(right, h)),
			vec3_scale(fwd, h));
	c[1] = vec3_add(vec3_add(py->transform.pos, vec3_scale(right, -h)),
			vec3_scale(fwd, h));
	c[2] = vec3_add(vec3_add(py->transform.pos, vec3_scale(right, -h)),
			vec3_scale(fwd, -h));
	c[3] = vec3_add(vec3_add(py->transform.pos, vec3_scale(right, h)),
			vec3_scale(fwd, -h));
	apex = vec3_add(py->transform.pos, vec3_scale(py->up, py->height));
	bb.min = c[0];
	bb.max = c[0];
	i = 1;
	while (i < 4)
	{
		if (c[i].x < bb.min.x) bb.min.x = c[i].x;
		if (c[i].y < bb.min.y) bb.min.y = c[i].y;
		if (c[i].z < bb.min.z) bb.min.z = c[i].z;
		if (c[i].x > bb.max.x) bb.max.x = c[i].x;
		if (c[i].y > bb.max.y) bb.max.y = c[i].y;
		if (c[i].z > bb.max.z) bb.max.z = c[i].z;
		i++;
	}
	if (apex.x < bb.min.x) bb.min.x = apex.x;
	if (apex.y < bb.min.y) bb.min.y = apex.y;
	if (apex.z < bb.min.z) bb.min.z = apex.z;
	if (apex.x > bb.max.x) bb.max.x = apex.x;
	if (apex.y > bb.max.y) bb.max.y = apex.y;
	if (apex.z > bb.max.z) bb.max.z = apex.z;
	bb.min.x -= 1e-4;
	bb.min.y -= 1e-4;
	bb.min.z -= 1e-4;
	bb.max.x += 1e-4;
	bb.max.y += 1e-4;
	bb.max.z += 1e-4;
	return (bb);
}
