/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   occluded.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 04:10:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 03:48:48 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

/**
 * @brief Distributes early occlusion branching tracking stack bounds.
 * 
 * Checks sequential hits for shadow testing efficiently, logging order priorities naturally.
 * Identifies and maps closer hits preferentially limiting extra search ranges effectively.
 * 
 * @param bvh Pointer wrapping node contexts and temporal stack array bounds.
 * @param node_idx Intersecting target indicating hierarchical level positional values.
 */
static void	push_occ_children(t_occ *bvh, int node_idx)
{
	int		l;
	int		r;
	double	tl;
	double	tr;

	l = bvh->bvh->nodes[node_idx].left_or_first;
	r = node_idx + 1;
	tl = aabb_hit_time_or_neg1(bvh->bvh, l, bvh->ray, bvh->max_t);
	tr = aabb_hit_time_or_neg1(bvh->bvh, r, bvh->ray, bvh->max_t);
	if (tl >= 0.0 && tr >= 0.0 && tl <= tr)
	{
		bvh->stack[(*bvh->ptr)++] = r;
		bvh->stack[(*bvh->ptr)++] = l;
	}
	else if (tl >= 0.0 && tr >= 0.0)
	{
		bvh->stack[(*bvh->ptr)++] = l;
		bvh->stack[(*bvh->ptr)++] = r;
	}
	else if (tl >= 0.0)
		bvh->stack[(*bvh->ptr)++] = l;
	else if (tr >= 0.0)
		bvh->stack[(*bvh->ptr)++] = r;
}

/**
 * @brief Evaluates particular geometry mesh references restricting bounding shadow searches.
 * 
 * Dispatches specifically formatted animated and traditional static mesh functions
 * seamlessly invoking occlusion tests skipping intensive normal parsing methods safely.
 * 
 * @param ray Immutable line trace mapping intersections internally tracked limits.
 * @param ref Reference isolating type index formats wrapping target primitives correctly.
 * @param bvh Main scene hierarchy packing object nodes mapping structure properties.
 * @param max_t Outer limit validating distant obstruction ranges bounding logic checks.
 * 
 * @return True confirms physical geometry occlusion existing securely within bounds.
 */
static bool	check_ref_occluded(const t_ray *ray, const t_bvh_ref *ref,
		const t_bvh *bvh, double max_t)
{
	if (ref->type == TYPE_MESH)
		return (mesh_occluded(ray, &bvh->scene->meshes[ref->index], max_t));
	if (ref->type == TYPE_ANIM)
		return (mesh_occluded(ray, &bvh->scene->animated[ref->index].base,
				max_t));
	return (occlude_object(ray, bvh->scene, *ref, max_t));
}

/**
 * @brief Parses enclosed spatial bounds grouping objects testing generic occlusion checks.
 * 
 * Validates array chunks progressively scanning references looping across leaf elements naturally.
 * Overrides remaining elements gracefully early aborting once unpassable obstruction reveals completely.
 * 
 * @param bvh Global reference enclosing active environmental array indices parsing boundaries.
 * @param node_idx Initial array parameter finding mapping coordinates bounding boxes reliably.
 * @param ray Positional path tracing line intersections finding geometry obstructions linearly.
 * @param max_t Cap boundary specifying limitation tracking tests dropping elements aggressively.
 * 
 * @return Boolean returning true successfully indicating hit occurrences.
 */
static bool	process_leaf_occluded(const t_bvh *bvh, int node_idx,
		const t_ray *ray, double max_t)
{
	const t_bvh_node	*node;
	int					i;
	int					end;

	node = &bvh->nodes[node_idx];
	i = node->left_or_first;
	end = i + node->count;
	while (i < end)
	{
		if (check_ref_occluded(ray, &bvh->refs[i], bvh, max_t))
			return (true);
		i++;
	}
	return (false);
}

/**
 * @brief Analyzes hierarchical logic dispatching leaf operations testing block properties globally.
 * 
 * Consumes stack records linearly verifying node counts. Successfully isolates bounds allocating tests optimally.
 * 
 * @param occ Wrapping structure handling array tracking bounds managing local memory variables dynamically.
 * 
 * @return Successful logic yields true restricting traversal steps confirming intersections appropriately.
 */
static bool	handle_node_occ(t_occ *occ)
{
	int					i;
	const t_bvh_node	*node;

	i = occ->stack[--(*occ->ptr)];
	node = &occ->bvh->nodes[i];
	if (node->count > 0)
		return (process_leaf_occluded(occ->bvh, i, occ->ray, occ->max_t));
	if (*occ->ptr < 126)
	{
		push_occ_children(occ, i);
	}
	return (false);
}

/**
 * @brief Topmost continuous mechanism orchestrating occlusion loops traversing unrolled tree buffers intuitively.
 * 
 * Integrates array variables simulating hierarchical iteration recursively maintaining compact local registers safely.
 * Operates explicitly resolving shadow rays skipping standard memory records mapping optimal times cleanly.
 * 
 * @param bvh Object carrying virtual boundary structure arrays testing global elements intuitively.
 * @param ray Constant variable guiding paths checking geometric components returning precise limits securely.
 * @param max_t Capping limits bounding testing logic appropriately handling unrolled steps effectively.
 * 
 * @return Conclusive true validates explicit obstructions resolving checks confirming geometries reliably.
 */
bool	bvh_traverse_loop(const t_bvh *bvh, const t_ray *ray, double max_t)
{
	int			stack[128];
	int			ptr;
	t_occ	occ;

	occ.stack = stack;
	occ.ptr = &ptr;
	occ.bvh = bvh;
	occ.ray = ray;
	occ.max_t = max_t;
	ptr = 0;
	stack[ptr++] = 0;
	while (ptr > 0)
	{
		if (handle_node_occ(&occ))
			return (true);
	}
	return (false);
}
