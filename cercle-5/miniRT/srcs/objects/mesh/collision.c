#include "maths.h"
#include "objects.h"
#include "physics.h"


static inline double	clamp(double min, double max, double v)
{
	if (v < min)
		return (min);
	if (v > max)
		return (max);
	return (v);
}

static bool	aabb_overlap(const t_aabb *a, const t_aabb *b)
{
	if (a->max.x < b->min.x || a->min.x > b->max.x)
		return (false);
	if (a->max.y < b->min.y || a->min.y > b->max.y)
		return (false);
	if (a->max.z < b->min.z || a->min.z > b->max.z)
		return (false);
	return (true);
}

/*
 * Returns the closest point on triangle (v0, v1, v2) to point p.
 * Uses a robust method checking edge regions and face region.
 */
static t_vec3	closest_point_on_triangle(t_vec3 p, t_vec3 v0, t_vec3 v1,
		t_vec3 v2)
{
	t_vec3 edge0 = vec3_sub(v1, v0);
	t_vec3 edge1 = vec3_sub(v2, v0);
	t_vec3 v0_p = vec3_sub(p, v0);

	double a = vec3_dot(edge0, edge0);
	double b = vec3_dot(edge0, edge1);
	double c = vec3_dot(edge1, edge1);
	double d = vec3_dot(edge0, v0_p);
	double e = vec3_dot(edge1, v0_p);

	double det = a * c - b * b;
	double s = b * e - c * d;
	double t = b * d - a * e;

	if (s + t < det)
	{
		if (s < 0.f)
		{
			if (t < 0.f)
			{
				if (d < 0.f)
				{
					s = clamp(0.f, 1.f, -d / a);
					t = 0.f;
				}
				else
				{
					s = 0.f;
					t = clamp(0.f, 1.f, -e / c);
				}
			}
			else
			{
				s = 0.f;
				t = clamp(0.f, 1.f, -e / c);
			}
		}
		else if (t < 0.f)
		{
			s = clamp(0.f, 1.f, -d / a);
			t = 0.f;
		}
		else
		{
			double invDet = 1.f / det;
			s *= invDet;
			t *= invDet;
		}
	}
	else
	{
		if (s < 0.f)
		{
			double tmp0 = b + d;
			double tmp1 = c + e;
			if (tmp1 > tmp0)
			{
				double numer = tmp1 - tmp0;
				double denom = a - 2.f * b + c;
				s = clamp(0.f, 1.f, numer / denom);
				t = 1.f - s;
			}
			else
			{
				t = clamp(0.f, 1.f, -e / c);
				s = 0.f;
			}
		}
		else if (t < 0.f)
		{
			if (a + d > b + e)
			{
				double numer = c + e - b - d;
				double denom = a - 2.f * b + c;
				s = clamp(0.f, 1.f, numer / denom);
				t = 1.f - s;
			}
			else
			{
				s = clamp(0.f, 1.f, -e / c);
				t = 0.f;
			}
		}
		else
		{
			double numerator = c + e - b - d;
			double denominator = a - 2.f * b + c;
			s = clamp(0.f, 1.f, numerator / denominator);
			t = 1.f - s;
		}
	}

	return (vec3_add(v0, vec3_add(vec3_scale(edge0, s), vec3_scale(edge1,
					t))));
}

/*
 * Checks if a sphere collides with a single triangle.
 */
static bool	test_sphere_triangle(const struct s_sphere *s, t_vec3 v0, t_vec3 v1,
		t_vec3 v2, t_vec3 *out_normal, double *out_penetration,
		double *min_dist_sq)
{
	t_vec3 closest = closest_point_on_triangle(s->transform.pos, v0, v1, v2);
	t_vec3 diff = vec3_sub(s->transform.pos, closest);
	double dist_sq = vec3_mag_sq(diff);
	double radius = sqrt(s->radius_sq);

	if (dist_sq < radius * radius && dist_sq < *min_dist_sq)
	{
		*min_dist_sq = dist_sq;
		double dist = sqrt(dist_sq);
		if (out_normal)
			*out_normal = vec3_scale(diff, 1.0 / (dist + 1e-6));
		// Avoid div by zero
		if (out_penetration)
			*out_penetration = radius - dist;
		return (true);
	}
	return (false);
}

/*
 * Checks if a sphere collides with a capsule.
 */
static bool	detect_sphere_capsule_collision(const struct s_sphere *s,
		const t_collider *c, t_vec3 *out_normal, double *out_penetration)
{
	t_vec3 ab = vec3_sub(c->data.capsule.b, c->data.capsule.a);
	t_vec3 as = vec3_sub(s->transform.pos, c->data.capsule.a);
	double t = vec3_dot(as, ab) / vec3_dot(ab, ab);

	t = clamp(0.0, 1.0, t);
	t_vec3 closest = vec3_add(c->data.capsule.a, vec3_scale(ab, t));
	t_vec3 diff = vec3_sub(s->transform.pos, closest);
	double dist_sq = vec3_mag_sq(diff);
	double radius_sum = sqrt(s->radius_sq) + c->data.capsule.radius;

	if (dist_sq < radius_sum * radius_sum)
	{
		double dist = sqrt(dist_sq);
		if (out_normal)
			*out_normal = vec3_scale(diff, 1.0 / (dist + 1e-6));
		if (out_penetration)
			*out_penetration = radius_sum - dist;
		return (true);
	}
	return (false);
}

/*
 * Traverses the mesh BVH to check for collisions.
 */
bool	detect_sphere_mesh_collision(const struct s_sphere *s, struct s_mesh *m,
		t_vec3 *out_normal, double *out_penetration)
{
	/* Optimization: Use Capsule Collider if available and enabled */
	if (MESH_SIMPLIFY
		&& m->collider.type == COLLIDER_CAPSULE)
	{
		return (detect_sphere_capsule_collision(s, &m->collider, out_normal,
				out_penetration));
	}


	if (!m || !m->bvh_nodes)
		return (false);
	t_aabb s_aabb = sphere_aabb((t_sphere *)s);
	if (!aabb_overlap(&m->bbox, &s_aabb))
		return (false);

	t_mbvh_node *stack[64];
	int top = 0;
	stack[top++] = &m->bvh_nodes[0];

	bool hit = false;
	double min_dist_sq = MAX_VALUE;
	t_vec3 best_normal = {0, 1, 0, 0};
	double best_pen = 0.0;

	while (top > 0)
	{
		t_mbvh_node *node = stack[--top];

		/* Check Sphere AABB vs Node AABB */
		if (!aabb_overlap(&node->bbox, &s_aabb))
			continue ;

		if (node->count > 0) // Leaf
		{
			for (int i = 0; i < node->count; ++i)
			{
				int tri_idx = m->bvh_indices[node->left_or_first + i];
				t_vec3 v0 = m->vertices[m->indices[tri_idx * 3 + 0]];
				t_vec3 v1 = m->vertices[m->indices[tri_idx * 3 + 1]];
				t_vec3 v2 = m->vertices[m->indices[tri_idx * 3 + 2]];

				t_vec3 n;
				double p;
				if (test_sphere_triangle(s, v0, v1, v2, &n, &p, &min_dist_sq))
				{
					hit = true;
					best_normal = n;
					best_pen = p;
				}
			}
		}
		else // Internal
		{
			/* Push children. Order doesn't strictly matter for collision
				unless we want early out, but we want closest point. */
			int left = node->left_or_first;
			int right = left + 1;
			stack[top++] = &m->bvh_nodes[left];
			stack[top++] = &m->bvh_nodes[right];
		}
	}

	if (hit)
	{
		if (out_normal)
			*out_normal = best_normal;
		if (out_penetration)
			*out_penetration = best_pen;
	}
	return (hit);
}
