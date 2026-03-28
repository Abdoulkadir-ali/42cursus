#include "raytracing.h"

static void compute_push_hits(t_push *v, t_bvh_stack *bvh, int node_idx)
{
	v->left = bvh->bvh->nodes[node_idx].left_or_first;
	v->right = v->left + 1;
	v->tl = 0.0; v->tr = 0.0;
	aabb_intersect_fast(&bvh->bvh->nodes[v->left].bbox, bvh->ray, &v->tl, &v->tl_max);
	aabb_intersect_fast(&bvh->bvh->nodes[v->right].bbox, bvh->ray, &v->tr, &v->tr_max);
	v->hit_l = (v->tl_max >= 0.0 && v->tl_max >= v->tl);
	v->hit_r = (v->tr_max >= 0.0 && v->tr_max >= v->tr);
	if (v->tl < 0.0) v->tl = 0.0;
	if (v->tr < 0.0) v->tr = 0.0;
}

static void push_children_both(t_bvh_stack *bvh, t_push *v)
{
	if (v->tl >= v->tr) {
		bvh->stack[bvh->ptr] = v->left;
		bvh->stack_tmin[bvh->ptr++] = v->tl;
		bvh->stack[bvh->ptr] = v->right;
		bvh->stack_tmin[bvh->ptr++] = v->tr;
	} else {
		bvh->stack[bvh->ptr] = v->right;
		bvh->stack_tmin[bvh->ptr++] = v->tr;
		bvh->stack[bvh->ptr] = v->left;
		bvh->stack_tmin[bvh->ptr++] = v->tl;
	}
}

void push_children(t_bvh_stack *bvh, int node_idx)
{
	t_push v;
	compute_push_hits(&v, bvh, node_idx);
	if (v.hit_l && v.hit_r) push_children_both(bvh, &v);
	else if (v.hit_l) {
		bvh->stack[bvh->ptr] = v.left;
		bvh->stack_tmin[bvh->ptr++] = v.tl;
	} else if (v.hit_r) {
		bvh->stack[bvh->ptr] = v.right;
		bvh->stack_tmin[bvh->ptr++] = v.tr;
	}
}
