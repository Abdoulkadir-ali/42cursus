#include "raytracing.h"

static bool occl_sphere(const t_ray *ray, t_scene *scene, int idx, double max_t)
{
	t_vec3 oc;
	double a, b, c, disc, t, radius;
	t_vec3 pos;

	pos = vec3(scene->primitives.px[idx], scene->primitives.py[idx],
					scene->primitives.pz[idx]);
	radius = scene->primitives.radii[idx];
	oc = vec3_sub(ray->origin, pos);
	a = vec3_dot(ray->direction, ray->direction);
	b = 2.0 * vec3_dot(oc, ray->direction);
	c = vec3_dot(oc, oc) - radius * radius;
	disc = b * b - 4.0 * a * c;
	if (disc < 0.0) return (false);
	disc = sqrt(disc);
	t = (-b - disc) / (2.0 * a);
	if (t < EPSILON) t = (-b + disc) / (2.0 * a);
	return (t > EPSILON && t < max_t);
}

static bool occl_tri(const t_ray *ray, t_scene *scene, int i, double max_t)
{
	t_vec3	pvec, tvec, qvec, e2;
	double	det, inv_det, u, v, t;
	t_tri_array *soa = &scene->tri_soa;

	e2 = vec3(soa->ex[1][i], soa->ey[1][i], soa->ez[1][i]);
	pvec = vec3_cross(ray->direction, e2);
	det = vec3_dot(vec3(soa->ex[0][i], soa->ey[0][i], soa->ez[0][i]), pvec);
	if (fabs(det) < 1e-8) return (false);
	inv_det = 1.0 / det;
	tvec = vec3_sub(ray->origin, vec3(soa->vx[0][i], soa->vy[0][i], soa->vz[0][i]));
	u = vec3_dot(tvec, pvec) * inv_det;
	if (u < 0.0 || u > 1.0) return (false);
	qvec = vec3_cross(tvec, vec3(soa->ex[0][i], soa->ey[0][i], soa->ez[0][i]));
	v = vec3_dot(ray->direction, qvec) * inv_det;
	if (v < 0.0 || u + v > 1.0) return (false);
	t = vec3_dot(e2, qvec) * inv_det;
	return (t > EPSILON && t < max_t);
}

bool occlude_object(const t_ray *ray, t_scene *scene, t_bvh_ref ref, double max_t)
{
	t_hit temp;
	if (ref.type == TYPE_SPHERE) return (occl_sphere(ray, scene, ref.index, max_t));
	if (ref.type == TYPE_TRI) return (occl_tri(ray, scene, ref.index, max_t));
	temp.t = max_t;
	if (intersect_object(ray, scene, ref, &temp))
		return (temp.t > EPSILON && temp.t < max_t);
	return (false);
}

bool bvh_occluded(const t_bvh *bvh, const t_ray *ray, double max_t)
{
	t_occ v;
	int stack[64], ptr, node_idx;

	DBG_ENTER("bvh_occluded");
	if (!bvh || bvh->num_nodes == 0)
	{
		DBG_LEAVE("bvh_occluded");
		return (false);
	}
	v.bvh = bvh; v.ray = ray; v.max_t = max_t; v.stack = stack; v.ptr = &ptr;
	ptr = 1; stack[0] = 0;
	while (ptr > 0) {
		node_idx = stack[--ptr];
		if (bvh->nodes[node_idx].count > 0) {
			if (process_leaf_occluded(bvh, node_idx, ray, max_t))
			{
				DBG_TRACE_MSG(DBG_CH_BVH, "bvh_occluded: OCCLUDED\n");
				DBG_LEAVE("bvh_occluded");
				return (true);
			}
		} else push_occ_children(&v, node_idx);
	}
	DBG_TRACE_MSG(DBG_CH_BVH, "bvh_occluded: CLEAR\n");
	DBG_LEAVE("bvh_occluded");
	return (false);
}
