/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:10:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/05 15:26:06 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

static void	print_node_info(const t_bvh_node *n, size_t idx)
{
	if (n->count > 0)
		ft_print_debug("leaf(refs[%zu..%zu], bbox: ", n->left_or_first,
			n->left_or_first + n->count - 1);
	else
		ft_print_debug("internal(left=%zu, right=%zu, bbox: ", idx + 1,
			n->left_or_first);
	print_vec3((t_vec3 *)&n->bbox.min);
	ft_print_debug(" to ");
	print_vec3((t_vec3 *)&n->bbox.max);
	ft_print_debug(")\n");
}

void	print_bvh_node(const t_bvh *b, size_t idx, size_t depth)
{
	const t_bvh_node	*n;
	size_t				i;

	if (!b || idx >= b->num_nodes)
		return ;
	n = &b->nodes[idx];
	i = 0;
	while (i < depth)
	{
		ft_print_debug("  ");
		i++;
	}
	print_node_info(n, idx);
	if (n->count == 0)
	{
		print_bvh_node(b, idx + 1, depth + 1);
		print_bvh_node(b, n->left_or_first, depth + 1);
	}
}

void	print_bvh(t_bvh *b)
{
	if (!b)
		return ;
	ft_print_debug("bvh(nodes=%zu, refs=%zu\n", b->num_nodes, b->num_refs);
	if (b->num_nodes > 0)
		print_bvh_node(b, 0, 1);
	else
		ft_print_debug("  empty\n");
	ft_print_debug(")\n");
}
