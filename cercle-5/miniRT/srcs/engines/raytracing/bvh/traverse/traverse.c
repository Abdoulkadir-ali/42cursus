#include "raytracing.h"

void push_occ_children(t_occ *v, int node_idx)
{
	int l, r;
	double tl, tr, tlm, trm;

	if (*v->ptr + 2 >= BVH_STACK_MAX)
		return ;
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

void	push_children(t_bvh_stack *s, int node_idx)
{
	int		l;
	int		r;
	double	tl;
	double	tr;
	double	tlm;
	double	trm;
	bool	hl;
	bool	hr;

	if (s->ptr + 2 >= BVH_STACK_MAX)
		return ;
	l = s->bvh->nodes[node_idx].left_or_first;
	r = l + 1;
	hl = aabb_intersect_fast(&s->bvh->nodes[l].bbox, s->ray, &tl, &tlm);
	hr = aabb_intersect_fast(&s->bvh->nodes[r].bbox, s->ray, &tr, &trm);
	if (hl && hr)
	{
		if (tl <= tr)
		{
			s->stack[s->ptr] = r;
			s->stack_tmin[s->ptr++] = tr;
			s->stack[s->ptr] = l;
			s->stack_tmin[s->ptr++] = tl;
		}
		else
		{
			s->stack[s->ptr] = l;
			s->stack_tmin[s->ptr++] = tl;
			s->stack[s->ptr] = r;
			s->stack_tmin[s->ptr++] = tr;
		}
	}
	else if (hl)
	{
		s->stack[s->ptr] = l;
		s->stack_tmin[s->ptr++] = tl;
	}
	else if (hr)
	{
		s->stack[s->ptr] = r;
		s->stack_tmin[s->ptr++] = tr;
	}
}
