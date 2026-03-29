/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 11:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 15:15:07 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

void	compute_com(t_physics_body *b)
{
	size_t	i;
	t_vec3	sum;

	sum = vec3(0, 0, 0);
	i = 0;
	while (i < b->sub_count)
	{
		sum = vec3_add(sum, b->sub_shapes[i].offset);
		i++;
	}
	if (b->sub_count > 0)
		b->com = vec3_scale(sum, 1.0 / (double)b->sub_count);
	else
		b->com = vec3(0, 0, 0);
}

void	compute_inertia(t_physics_body *b)
{
	size_t	i;
	t_vec3	r;
	double	ms;

	memset(&b->inv_inertia, 0, sizeof(t_mat3));
	if (b->mass < 1e-6) return ;
	ms = b->mass / (double)b->sub_count;
	i = 0;
	while (i < b->sub_count)
	{
		r = vec3_sub(b->sub_shapes[i].offset, b->com);
		b->inv_inertia.m[0][0] += ms * (r.y * r.y + r.z * r.z);
		b->inv_inertia.m[1][1] += ms * (r.x * r.x + r.z * r.z);
		b->inv_inertia.m[2][2] += ms * (r.x * r.x + r.y * r.y);
		b->inv_inertia.m[0][1] -= ms * (r.x * r.y);
		b->inv_inertia.m[0][2] -= ms * (r.x * r.z);
		b->inv_inertia.m[1][2] -= ms * (r.y * r.z);
		i++;
	}
	b->inv_inertia.m[1][0] = b->inv_inertia.m[0][1];
	b->inv_inertia.m[2][0] = b->inv_inertia.m[0][2];
	b->inv_inertia.m[2][1] = b->inv_inertia.m[1][2];
	mat3_inv(b->inv_inertia, &b->inv_inertia);
}
