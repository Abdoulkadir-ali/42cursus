/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 20:10:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/09 20:10:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

void	print_vec2(t_vec2 *v)
{
	if (!v)
		return ;
	printf("vec2(%.4f, %.4f)", v->x, v->y);
}

void	print_vec3(t_vec3 *v)
{
	if (!v)
		return ;
	printf("vec3(%.4f, %.4f, %.4f, w: %.4f)", v->x, v->y, v->z, v->w);
}

void	print_mat4(t_mat4 *m)
{
	int	i;
	int	j;

	if (!m)
		return ;
	printf("mat4(\n");
	i = 0;
	while (i < 4)
	{
		printf("  [ ");
		j = 0;
		while (j < 4)
		{
			printf("%.4f", m->m[i][j]);
			if (j < 3)
				printf(", ");
			j++;
		}
		printf(" ]\n");
		i++;
	}
	printf(")");
}

void	print_transform(t_transform *t)
{
	if (!t)
		return ;
	printf("transform(\n");
	printf("  pos: ");
	print_vec3(&t->pos);
	printf("\n  rot: pitch: %.4f, ", t->rotation.pitch);
	printf("yaw: %.4f, roll: %.4f", t->rotation.yaw, t->rotation.roll);
	printf("\n  scale: ");
	print_vec3(&t->scale);
	printf("\n  forward: ");
	print_vec3(&t->forward);
	printf("\n  right: ");
	print_vec3(&t->right);
	printf("\n  up: ");
	print_vec3(&t->up);
	printf("\n)");
}

void	print_aabb(t_aabb *b)
{
	if (!b)
		return ;
	printf("aabb(\n  min: ");
	print_vec3(&b->min);
	printf("\n  max: ");
	print_vec3(&b->max);
	printf("\n)");
}
