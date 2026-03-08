#include "raytracing.h"
#include "objects.h"

/*
** Intersect ray with a planar quad (v[0..3] in order).
** Uses Möller–Trumbore on the two triangles v[0,1,2] and v[0,2,3].
** Picks the closer positive hit and sets u/v as bilinear coords.
*/
bool	intersect_rect(const t_ray *ray, t_rect *rc, t_hit *hit)
{
	t_vec3	v012[3];
	t_vec3	v023[3];
	double	t0;
	double	t1;
	t_vec2	uv0;
	t_vec2	uv1;
	bool	h0;
	bool	h1;

	v012[0] = rc->v[0];
	v012[1] = rc->v[1];
	v012[2] = rc->v[2];
	v023[0] = rc->v[0];
	v023[1] = rc->v[2];
	v023[2] = rc->v[3];
	h0 = intersect_triangle_fast(ray, v012, &t0, &uv0);
	h1 = intersect_triangle_fast(ray, v023, &t1, &uv1);
	if (!h0 && !h1)
		return (false);
	if (h0 && (!h1 || t0 <= t1))
	{
		hit->t = t0;
		hit->u = uv0.x;
		hit->v = uv0.y;
	}
	else
	{
		hit->t = t1;
		hit->u = uv1.x;
		hit->v = uv1.y;
	}
	hit->point = vec3_add(ray->origin, vec3_scale(ray->direction, hit->t));
	hit->normal = rc->normal;
	if (vec3_dot(ray->direction, hit->normal) > 0)
		hit->normal = vec3_scale(hit->normal, -1.0);
	vec3_orthonormal_basis(hit->normal, &hit->tangent, &hit->bitangent);
	return (true);
}
