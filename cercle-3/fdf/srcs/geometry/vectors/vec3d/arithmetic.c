/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arithmetic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 19:45:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/21 17:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry.h"

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
	if (other.x != 0)
		self->x /= other.x;
	if (other.y != 0)
		self->y /= other.y;
	if (other.z != 0)
		self->z /= other.z;
}

void	vec3d_multiply_scalar(t_vec3d *self, double scalar)
{
	self->x *= scalar;
	self->y *= scalar;
	self->z *= scalar;
}
