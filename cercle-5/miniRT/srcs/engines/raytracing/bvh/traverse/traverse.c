#include "raytracing.h"

void push_occ_children(t_occ *v, int node_idx)
{
	int l, r;
	double tl, tr, tlm, trm;

	l = v->bvh->nodes[node_idx].left_or_first;
	r = l + 1;
	tl = 0.0; tr = 0.0;
	aabb_intersect_fast(&v->bvh->nodes[l].bbox, v->ray, &tl, &tlm);
	aabb_intersect_fast(&v->bvh->nodes[r].bbox, v->ray, &tr, &trm);
	if (tlm >= 0.0 && tlm >= tl && trm >= 0.0 && trm >= tr) {
		if (tl <= tr) { v->stack[(*v->ptr)++] = r; v->stack[(*v->ptr)++] = l; }
		else { v->stack[(*v->ptr)++] = l; v->stack[(*v->ptr)++] = r; }
	} else if (tlm >= 0.0 && tlm >= tl) v->stack[(*v->ptr)++] = l;
	else if (trm >= 0.0 && trm >= tr) v->stack[(*v->ptr)++] = r;
}

bool process_leaf_occluded(const t_bvh *bvh, int node_idx, const t_ray *ray, double max_t)
{
	int i, end;
	i = bvh->nodes[node_idx].left_or_first;
	end = i + bvh->nodes[node_idx].count;
	while (i < end) {
		if (occlude_object(ray, bvh->scene, bvh->refs[i], max_t)) return (true);
		i++;
	}
	return (false);
}
