/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/13 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

void	push_both_children(t_bvh_node *stack[128], int *ptr, t_push_data *data)
{
	if (*ptr >= 126)
		return ;
	if (data->left_t.x > data->right_t.x)
	{
		stack[(*ptr)++] = data->left;
		stack[(*ptr)++] = data->right;
	}
	else
	{
		stack[(*ptr)++] = data->right;
		stack[(*ptr)++] = data->left;
	}
}

void	push_single_child(t_bvh_node *stack[128], int *ptr, t_bvh_node *child)
{
	if (*ptr >= 127)
		return ;
	stack[(*ptr)++] = child;
}

void	push_children(t_bvh_node *stack[128], int *ptr, t_push_data *data)
{
	if (data->h_l && data->h_r)
		push_both_children(stack, ptr, data);
	else if (data->h_l)
		push_single_child(stack, ptr, data->left);
	else if (data->h_r)
		push_single_child(stack, ptr, data->right);
}
