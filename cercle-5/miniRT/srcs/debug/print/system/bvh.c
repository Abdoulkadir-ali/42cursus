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

void	print_bvh_node(t_bvh_node *n, int depth)
{
	int			i;
	const char	*leaf;

	if (!n)
		return ;
	leaf = "yes";
	if (n->left || n->right)
		leaf = "no";
	i = 0;
	while (i < depth)
	{
		printf("  ");
		i++;
	}
	printf("node(refs: %zu, leaf: %s, bbox: ", n->num_refs, leaf);
	print_vec3(&n->bbox.min);
	printf(" to ");
	print_vec3(&n->bbox.max);
	printf(")\n");
	if (n->left)
		print_bvh_node(n->left, depth + 1);
	if (n->right)
		print_bvh_node(n->right, depth + 1);
}

void	print_bvh(t_bvh *b)
{
	if (!b)
		return ;
	printf("bvh(root:\n");
	if (b->root)
		print_bvh_node(b->root, 1);
	else
		printf("  NULL\n");
	printf(")\n");
}
