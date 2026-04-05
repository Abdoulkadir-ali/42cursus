/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 12:49:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/05 15:26:06 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

void	print_vec2(t_vec2 *v)
{
	if (!v)
		return ;
	ft_print_debug("vec2(%.4f, %.4f)", v->x, v->y);
}

void	print_vec3(t_vec3 *v)
{
	if (!v)
		return ;
	ft_print_debug("vec3(%.4f, %.4f, %.4f, w: %.4f)", v->x, v->y, v->z, v->w);
}

void	print_mat4(t_mat4 *m)
{
	int	i;
	int	j;

	if (!m)
		return ;
	ft_print_debug("mat4(\n");
	i = 0;
	while (i < 4)
	{
		ft_print_debug("  [ ");
		j = 0;
		while (j < 4)
		{
			ft_print_debug("%.4f", m->m[i][j]);
			if (j < 3)
				ft_print_debug(", ");
			j++;
		}
		ft_print_debug(" ]\n");
		i++;
	}
	ft_print_debug(")");
}

void	print_transform(t_transform *t)
{
	if (!t)
		return ;
	ft_print_debug("transform(\n");
	ft_print_debug("  pos: ");
	print_vec3(&t->pos);
	ft_print_debug("\n  rot: pitch: %.4f, ", t->rotation.pitch);
	ft_print_debug("yaw: %.4f, roll: %.4f", t->rotation.yaw, t->rotation.roll);
	ft_print_debug("\n  scale: ");
	print_vec3(&t->scale);
	ft_print_debug("\n  forward: ");
	print_vec3(&t->forward);
	ft_print_debug("\n  right: ");
	print_vec3(&t->right);
	ft_print_debug("\n  up: ");
	print_vec3(&t->up);
	ft_print_debug("\n)");
}

void	print_aabb(t_aabb *b)
{
	if (!b)
		return ;
	ft_print_debug("aabb(\n  min: ");
	print_vec3(&b->min);
	ft_print_debug("\n  max: ");
	print_vec3(&b->max);
	ft_print_debug("\n)");
}
