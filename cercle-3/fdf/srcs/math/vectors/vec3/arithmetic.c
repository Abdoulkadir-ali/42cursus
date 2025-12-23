/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arithmetic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 13:40:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/23 13:40:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry.h"

void	vec3_add(t_vec3 *self, t_vec3 other)
{
	self->x += other.x;
	self->y += other.y;
	self->z += other.z;
}

void	vec3_sub(t_vec3 *self, t_vec3 other)
{
	self->x -= other.x;
	self->y -= other.y;
	self->z -= other.z;
}

void	vec3_multiply(t_vec3 *self, t_vec3 other)
{
	self->x *= other.x;
	self->y *= other.y;
	self->z *= other.z;
}

void	vec3_divide(t_vec3 *self, t_vec3 other)
{
	if (other.x != 0)
		self->x /= other.x;
	if (other.y != 0)
		self->y /= other.y;
	if (other.z != 0)
		self->z /= other.z;
}

void	vec3_multiply_scalar(t_vec3 *self, int scalar)
{
	self->x *= scalar;
	self->y *= scalar;
	self->z *= scalar;
}
