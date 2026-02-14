/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/13 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

void	process_internal_node(t_bvh_node *node, t_bvh_node *stack[128],
		int *ptr, const t_ray *ray)
{
	t_child_intersections	intersections;
	t_push_args				args;

	intersections = get_child_intersections(node, ray);
	args.stack = stack;
	args.ptr = ptr;
	args.data.left = node->left;
	args.data.right = node->right;
	args.data.left_t = intersections.left_t;
	args.data.right_t = intersections.right_t;
	args.h_l = intersections.h_l;
	args.h_r = intersections.h_r;
	push_children(&args);
}
