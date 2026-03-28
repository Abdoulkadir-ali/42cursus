#include "raytracing.h"

static bool occl_sphere(const t_ray *ray, t_scene *scene, int idx, double max_t)
{
	t_vec3 oc;
	double a, b, disc, t, radius;
	t_vec4 pos;

	pos = (t_vec4){scene->primitives.px[idx], scene->primitives.py[idx],
					scene->primitives.pz[idx], 1.0};
	radius = scene->primitives.radii[idx];
	oc = vec3_sub(ray->origin, (t_vec3){pos.x, pos.y, pos.z, 1.0});
	a = vec3_dot(ray->direction, ray->direction);
	b = 2.0 * vec3_dot(oc, ray->direction);
	disc = b * b - 4.0 * a * (vec3_dot(oc, oc) - radius * radius);
	if (disc < 0.0) return (false);
	disc = sqrt(disc);
	t = (-b - disc) / (2.0 * a);
	if (t < EPSILON) t = (-b + disc) / (2.0 * a);
	return (t > EPSILON && t < max_t);
}

bool occlude_object(const t_ray *ray, t_scene *scene, t_bvh_ref ref, double max_t)
{
	t_hit temp;
	if (ref.type == TYPE_SPHERE) return (occl_sphere(ray, scene, ref.index, max_t));
	temp.t = max_t;
	if (intersect_object(ray, scene, ref, &temp))
		return (temp.t > EPSILON && temp.t < max_t);
	return (false);
}

bool bvh_occluded(const t_bvh *bvh, const t_ray *ray, double max_t)
{
	t_occ v;
	int stack[64], ptr, node_idx;
	if (!bvh || bvh->num_nodes == 0) return (false);
	v.bvh = bvh; v.ray = ray; v.max_t = max_t; v.stack = stack; v.ptr = &ptr;
	ptr = 1; stack[0] = 0;
	while (ptr > 0) {
		node_idx = stack[--ptr];
		if (bvh->nodes[node_idx].count > 0) {
			if (process_leaf_occluded(bvh, node_idx, ray, max_t)) return (true);
		} else push_occ_children(&v, node_idx);
	}
	return (false);
}
