#include "raytracing.h"
#include "objects.h"
#include <math.h>

/*
** Precompute and cache the 5 pyramid vertices into py->c[] and py->apex.
** Called once at BVH build time (before any render threads start), so the
** per-ray hot path can just read the cached values.
*/
void	pyramid_cache_verts(t_pyramid *py)
{
	t_vec3	ref;
	t_vec3	right;
	t_vec3	fwd;
	double	h;

	h = py->base_size * 0.5;
	if (fabs(py->up.y) < 0.9)
		ref = vec3(0, 1, 0);
	else
		ref = vec3(1, 0, 0);
	right = vec3_norm(vec3_cross(py->up, ref));
	fwd = vec3_cross(right, py->up);
	py->c[0] = vec3_add(vec3_add(py->transform.pos, vec3_scale(right, h)),
			vec3_scale(fwd, h));
	py->c[1] = vec3_add(vec3_add(py->transform.pos, vec3_scale(right, -h)),
			vec3_scale(fwd, h));
	py->c[2] = vec3_add(vec3_add(py->transform.pos, vec3_scale(right, -h)),
			vec3_scale(fwd, -h));
	py->c[3] = vec3_add(vec3_add(py->transform.pos, vec3_scale(right, h)),
			vec3_scale(fwd, -h));
	py->apex = vec3_add(py->transform.pos, vec3_scale(py->up, py->height));
}

/*
** Try a single triangle face; if hit and closer than *best_t, update hit.
*/
static bool	try_face(const t_ray *ray, t_vec3 a, t_vec3 b, t_vec3 c,
		double *best_t, t_hit *hit)
{
	t_vec3	tri[3];
	double	t;
	t_vec2	uv;
	t_vec3	n;

	tri[0] = a;
	tri[1] = b;
	tri[2] = c;
	if (!intersect_triangle_fast(ray, tri, &t, &uv))
		return (false);
	if (t >= *best_t)
		return (false);
	*best_t = t;
	hit->t = t;
	hit->point = vec3_add(ray->origin, vec3_scale(ray->direction, t));
	n = vec3_norm(vec3_cross(vec3_sub(b, a), vec3_sub(c, a)));
	if (vec3_dot(ray->direction, n) > 0)
		n = vec3_scale(n, -1.0);
	hit->normal = n;
	hit->u = uv.x;
	hit->v = uv.y;
	vec3_orthonormal_basis(hit->normal, &hit->tangent, &hit->bitangent);
	return (true);
}

bool	intersect_pyramid(const t_ray *ray, t_pyramid *py, t_hit *hit)
{
	double	best;
	bool	any;

	best = 1e30;
	any = false;
	if (try_face(ray, py->c[0], py->c[1], py->c[2], &best, hit)) any = true;
	if (try_face(ray, py->c[0], py->c[2], py->c[3], &best, hit)) any = true;
	if (try_face(ray, py->c[0], py->c[1], py->apex, &best, hit)) any = true;
	if (try_face(ray, py->c[1], py->c[2], py->apex, &best, hit)) any = true;
	if (try_face(ray, py->c[2], py->c[3], py->apex, &best, hit)) any = true;
	if (try_face(ray, py->c[3], py->c[0], py->apex, &best, hit)) any = true;
	return (any);
}
