/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   query.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/09 17:29:30 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"
#include "raytracing.h"

/**
 * @brief Tests a pair of boxes for collision using AABB broadphase then GJK.
 */
static void	test_box_pair(t_contact_query *qu, t_col_pair *p, t_aabb aabb_a)
{
	if (aabb_overlap(aabb_a, box_aabb((t_box *)p->sb->data)))
	{
		if (gjk_make_contact(p, &qu->contacts[qu->count]))
			qu->count++;
	}
}

/**
 * @brief Tests a box against all other boxes in the scene.
 */
static void	box_vs_boxes(t_contact_query *qu, t_box *bx, size_t idx,
		t_aabb bx_aabb)
{
	size_t		p;
	t_gjk_shape	sa;
	t_gjk_shape	sb;
	t_col_pair	pair;
	t_box		*other;

	sa = init_gjk_shape(bx, gjk_support_box, bx->phys.pos);
	p = idx + 1;
	while (p < qu->engine->scene->box_count && qu->count < qu->max)
	{
		other = &qu->engine->scene->boxes[p];
		sb = init_gjk_shape(other, gjk_support_box, other->phys.pos);
		pair = (t_col_pair){&sa, &sb, &bx->phys, &other->phys,
			&bx->transform, &other->transform};
		test_box_pair(qu, &pair, bx_aabb);
		p++;
	}
}

/**
 * @brief Main query function for box collision detection.
 */
size_t	query_box(t_contact_query *qu, size_t idx)
{
	t_box			*bx;
	t_gjk_shape		sa;
	t_bvh_phys_ctx	ctx;
	t_aabb			aabb;

	bx = &qu->engine->scene->boxes[idx];
	if (bx->phys.is_static)
		return (qu->count);
	aabb = box_aabb(bx);
	box_vs_all_planes(qu, bx);
	box_vs_boxes(qu, bx, idx, aabb);
	sa = init_gjk_shape(bx, gjk_support_box, bx->phys.pos);
	ctx = (t_bvh_phys_ctx){qu, &sa, &bx->phys, &bx->transform, TYPE_BOX};
	bvh_query_shapes(&ctx, aabb);
	return (qu->count);
}
