/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 06:17:49 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 06:17:50 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "raytracing.h"

/**
 * @brief Performs AABB slab intersection checks calculating preliminary hit timing values.
 * 
 * Executes boundary proximity checks specifically against the Left and Right node
 * boundaries encapsulated within the BVH tree mapping. This tracks `tmin` variables,
 * safely resetting stray bounds backwards preventing internal volume tunneling errors.
 * 
 * @param v        Collection properties object recording timings and verification flags.
 * @param bvh      State block holding iterative arrays managing rendering context.
 * @param node_idx Array integer parameter specifying current spatial separation.
 * 
 * @return No explicit return. Output configures metrics globally via reference tracking.
 */
static void	compute_push_hits(t_push_vars *v, t_bvh_stack *bvh,
 			    int node_idx)
{
	v->left = bvh->bvh->nodes[node_idx].left_or_first;
	v->right = node_idx + 1;
	v->tl = 0.0;
	v->tr = 0.0;
	v->hit_l = aabb_intersect_fast(&bvh->bvh->nodes[v->left].bbox,
			bvh->ray, &v->tl, &v->tl_max);
	v->hit_r = aabb_intersect_fast(&bvh->bvh->nodes[v->right].bbox,
			bvh->ray, &v->tr, &v->tr_max);
	if (v->tl < 0.0)
		v->tl = 0.0;
	if (v->tr < 0.0)
		v->tr = 0.0;
	if (v->hit_l && v->tl > bvh->hit_t)
		v->hit_l = false;
	if (v->hit_r && v->tr > bvh->hit_t)
		v->hit_r = false;
}

/**
 * @brief Registers both sibling branches to the traversal stack managing depth insertion order.
 * 
 * Operates intelligently by evaluating closest node proximity initially, placing 
 * farther leaves lower dynamically avoiding delayed evaluations during front-to-back sorting.
 * 
 * @param bvh Wrapper enclosing all contextual tracking and stack metrics limits.
 * @param v   Data context wrapping the exact intersection timings parsed individually.
 * 
 * @return No return type. Evaluates internal stack variables entirely.
 */
static void	push_children_both(t_bvh_stack *bvh, t_push_vars *v)
{
	if (v->tl <= v->tr)
	{
		bvh->stack[bvh->ptr++] = v->right;
		bvh->stack[bvh->ptr++] = v->left;
		bvh->stack_tmin[bvh->ptr - 2] = v->tr;
		bvh->stack_tmin[bvh->ptr - 1] = v->tl;
	}
	else
	{
		bvh->stack[bvh->ptr++] = v->left;
		bvh->stack[bvh->ptr++] = v->right;
		bvh->stack_tmin[bvh->ptr - 2] = v->tl;
		bvh->stack_tmin[bvh->ptr - 1] = v->tr;
	}
}

/**
 * @brief Principal dispatcher handling single or double children push behavior dynamically.
 * 
 * Utilizes timing configuration algorithms to analyze hit outcomes mapping accurately
 * onto stack arrays. Effectively skips failed node subtrees streamlining global
 * iteration cycles traversing BVH blocks.
 * 
 * @param bvh      Context structure packing internal properties mapping traversal layers.
 * @param node_idx The specific pointer inside tracking indicating index arrays boundaries.
 * 
 * @return Output registers automatically mapping children within the stack buffer index.
 */
void	push_children(t_bvh_stack *bvh, int node_idx)
{
	t_push_vars v;

	compute_push_hits(&v, bvh, node_idx);
	if (v.hit_l && v.hit_r)
	{
		push_children_both(bvh, &v);
	}
	else if (v.hit_l)
	{
		bvh->stack[bvh->ptr] = v.left;
		bvh->stack_tmin[bvh->ptr] = v.tl;
		bvh->ptr++;
	}
	else if (v.hit_r)
	{
		bvh->stack[bvh->ptr] = v.right;
		bvh->stack_tmin[bvh->ptr] = v.tr;
		bvh->ptr++;
	}
}