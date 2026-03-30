/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:10:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/11 15:10:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"
#include "raytracing.h"

static void	print_node_info(const t_bvh_node *n, int idx)
{
	if (n->count > 0)
		printf("leaf(refs[%d..%d], bbox: ", n->left_or_first,
			n->left_or_first + n->count - 1);
	else
		printf("internal(left=%d, right=%d, bbox: ", idx + 1,
			n->left_or_first);
	print_vec3((t_vec3 *)&n->bbox.min);
	printf(" to ");
	print_vec3((t_vec3 *)&n->bbox.max);
	printf(")\n");
}

void	print_bvh_node(const t_bvh *b, int idx, int depth)
{
	const t_bvh_node	*n;
	int					i;

	if (!b || idx < 0 || idx >= b->num_nodes)
		return ;
	n = &b->nodes[idx];
	i = -1;
	while (++i < depth)
		printf("  ");
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
	printf("bvh(nodes=%d, refs=%d\n", b->num_nodes, b->num_refs);
	if (b->num_nodes > 0)
		print_bvh_node(b, 0, 1);
	else
		printf("  empty\n");
	printf(")\n");
}
