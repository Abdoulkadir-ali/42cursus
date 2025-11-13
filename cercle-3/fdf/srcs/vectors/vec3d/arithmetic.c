/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arithmetic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 17:00:36 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/13 13:11:26 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vectors.h"

void	vec3d_add(t_vec3d *self, t_vec3d other)
{
	self->x += other.x;
	self->y += other.y;
	self->z += other.z;
}

void	vec3d_sub(t_vec3d *self, t_vec3d other)
{
	self->x -= other.x;
	self->y -= other.y;
	self->z -= other.z;
}

void	vec3d_multiply(t_vec3d *self, t_vec3d other)
{
	self->x *= other.x;
	self->y *= other.y;
	self->z *= other.z;
}

void	vec3d_divide(t_vec3d *self, t_vec3d other)
{
	if (other.x != 0.0 && other.y != 0.0 && other.z != 0.0)
	{
		self->x /= other.x;
		self->y /= other.y;
		self->z /= other.z;
	}
	ft_putstr_fd("Zero division error", 2);
	exit(1);
}

void	vec3d_multiply_scalar(t_vec3d *self, double scalar)
{
	self->x *= scalar;
	self->y *= scalar;
	self->z *= scalar;
}
