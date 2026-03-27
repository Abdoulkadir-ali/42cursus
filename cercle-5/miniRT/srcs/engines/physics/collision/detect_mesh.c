/* migrated from srcs/objects/mesh/collision/detect.c */

#include "physics.h"

static bool test_tri(const struct s_sphere *s, t_vec3 v[3], t_mesh_query *q)
{
	t_tri_var	tri;

	tri.cl = closest_point_on_triangle(s->transform.pos, v[0], v[1], v[2]);
	tri.d = vec3_sub(s->transform.pos, tri.cl);
	tri.dsq = vec3_mag_sq(tri.d);
	tri.rad = sqrt(s->radius_sq);
	if (tri.dsq < tri.rad * tri.rad && tri.dsq < q->min_d)
	{
		q->min_d = tri.dsq;
		tri.dist = sqrt(tri.dsq);
		if (q->out_n)
			*q->out_n = vec3_scale(tri.d, 1.0 / (tri.dist + 1e-6));
		if (q->out_p)
			*q->out_p = tri.rad - tri.dist;
		return (true);
	}
	return (false);
}

static bool leaf(t_mesh_query *q, t_mbvh_node *node)
{
	int		i;
	int		t_idx;
	t_vec3	v[3];

	i = 0;
	while (i < node->count)
	{
		t_idx = q->m->bvh_indices[node->left_or_first + i];
		v[0] = q->m->vertices[q->m->indices[t_idx * 3 + 0]];
		v[1] = q->m->vertices[q->m->indices[t_idx * 3 + 1]];
		v[2] = q->m->vertices[q->m->indices[t_idx * 3 + 2]];
		if (test_tri(q->s, v, q))
			q->hit = true;
		i++;
	}
	return (q->hit);
}

static bool bvh(t_mesh_query *q)
{
	t_mbvh_node	*stk[64];
	int			top;
	t_mbvh_node	*n;

	top = 0;
	stk[top++] = &q->m->bvh_nodes[0];
	while (top > 0)
	{
		n = stk[--top];
		if (!aabb_overlap(n->bbox, q->sa))
			continue ;
		if (n->count > 0)
		{
			if (leaf(q, n))
				q->hit = true;
		}
		else
		{
			stk[top++] = &q->m->bvh_nodes[n->left_or_first];
			stk[top++] = &q->m->bvh_nodes[n->left_or_first + 1];
		}
	}
	return (q->hit);
}

static bool capsule(const struct s_sphere *s, const t_collider *c, t_vec3 *n,
	double *p)
{
	t_capsule_var	v;

	v.ab = vec3_sub(c->data.capsule.b, c->data.capsule.a);
	v.as = vec3_sub(s->transform.pos, c->data.capsule.a);
	v.t = fmin(1.0, fmax(0.0, vec3_dot(v.as, v.ab) / vec3_dot(v.ab, v.ab)));
	v.cl = vec3_add(c->data.capsule.a, vec3_scale(v.ab, v.t));
	v.d = vec3_sub(s->transform.pos, v.cl);
	v.dsq = vec3_mag_sq(v.d);
	v.rs = sqrt(s->radius_sq) + c->data.capsule.radius;
	if (v.dsq < v.rs * v.rs)
	{
		v.dist = sqrt(v.dsq);
		if (n)
			*n = vec3_scale(v.d, 1.0 / (v.dist + 1e-6));
		if (p)
			*p = v.rs - v.dist;
		return (true);
	}
	return (false);
}

bool detect_sphere_mesh_collision(const struct s_sphere *s, struct s_mesh *m,
	t_vec3 *out_n, double *out_p)
{
	t_mesh_query	q;

	if (MESH_SIMPLIFY && m->collider.type == COLLIDER_CAPSULE)
		return (capsule(s, &m->collider, out_n, out_p));
	if (!m || !m->bvh_nodes)
		return (false);
	q = (t_mesh_query){s, m, out_n, out_p, sphere_aabb((t_sphere *)s), 1e30, 0};
	if (!aabb_overlap(m->bbox, q.sa))
		return (false);
	q.hit = bvh(&q);
	return (q.hit);
}
