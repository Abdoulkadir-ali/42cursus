/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 16:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 10:28:50 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

static int	static_bvh_build(t_static_bvh *bvh, t_scene *s, t_static_node *objs,
		int n)
{
	int		node_idx;
	int		mid;
	int		i;
	t_aabb	union_aabb;

	if (n == 0)
		return (-1);
	node_idx = bvh->count++;
	union_aabb = objs[0].aabb;
	i = 0;
	while (++i < n)
	{
		union_aabb.min = vec3_min(union_aabb.min, objs[i].aabb.min);
		union_aabb.max = vec3_max(union_aabb.max, objs[i].aabb.max);
	}
	bvh->nodes[node_idx].aabb = union_aabb;
	if (n == 1)
	{
		bvh->nodes[node_idx] = objs[0];
		bvh->nodes[node_idx].aabb = union_aabb;
		bvh->nodes[node_idx].left = -1;
		bvh->nodes[node_idx].right = -1;
		return (node_idx);
	}
	mid = n / 2;
	bvh->nodes[node_idx].obj_idx = -1;
	bvh->nodes[node_idx].left = static_bvh_build(bvh, s, objs, mid);
	bvh->nodes[node_idx].right = static_bvh_build(bvh, s, objs + mid, n - mid);
	return (node_idx);
}

int	query_static_bvh(t_scene *s, int node_idx, t_gjk_shape *sa,
		t_physics_body *ba, t_transform *ta, t_contact *c, int count, int max)
{
	t_static_node	*n;

	if (node_idx == -1 || count >= max)
		return (count);
	n = &s->static_bvh->nodes[node_idx];
	if (!aabb_overlap(n->aabb, ba->global_aabb))
		return (count);
	if (n->obj_idx != -1)
	{
		if (n->obj_type == 4)
			return (count + gjk_vs_rect(sa, ba, ta, &s->rects[n->obj_idx],
					&c[count]));
		if (n->obj_type == 5)
			return (count + gjk_vs_tri(sa, ba, ta, &s->tris[n->obj_idx],
					&c[count]));
		return (count + gjk_vs_pyramid(sa, ba, ta, &s->pyramids[n->obj_idx],
				&c[count]));
	}
	count = query_static_bvh(s, n->left, sa, ba, ta, c, count, max);
	count = query_static_bvh(s, n->right, sa, ba, ta, c, count, max);
	return (count);
}

void	phys_init_static_bvh(t_scene *s)
{
	int				total;
	t_static_node	*objs;
	int				k;
	int				i;

	total = s->rect_count + s->tri_count + s->pyramid_count;
	if (total == 0)
		return ;
	s->static_bvh = malloc(sizeof(t_static_bvh));
	s->static_bvh->nodes = malloc(sizeof(t_static_node) * total * 2);
	s->static_bvh->count = 0;
	objs = malloc(sizeof(t_static_node) * total);
	k = 0;
	i = -1;
	while (++i < s->rect_count)
		objs[k++] = (t_static_node){rect_aabb(&s->rects[i]), -1, -1, i, 4};
	i = -1;
	while (++i < s->tri_count)
		objs[k++] = (t_static_node){tri_aabb(&s->tris[i]), -1, -1, i, 5};
	i = -1;
	while (++i < s->pyramid_count)
		objs[k++] = (t_static_node){pyramid_aabb(&s->pyramids[i]), -1, -1, i,
			6};
	s->static_bvh->root = static_bvh_build(s->static_bvh, s, objs, total);
	free(objs);
}
