/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arithmetic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 19:45:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/23 22:54:10 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "primitives.h"

void	vec2d_add(t_vec2d *self, t_vec2d other)
{
	self->x += other.x;
	self->y += other.y;
}

void	vec2d_sub(t_vec2d *self, t_vec2d other)
{
	self->x -= other.x;
	self->y -= other.y;
}

void	vec2d_multiply(t_vec2d *self, t_vec2d other)
{
	self->x *= other.x;
	self->y *= other.y;
}

void	vec2d_divide(t_vec2d *self, t_vec2d other)
{
	if (other.x != 0)
		self->x /= other.x;
	if (other.y != 0)
		self->y /= other.y;
}

void	vec2d_multiply_scalar(t_vec2d *self, double scalar)
{
	self->x *= scalar;
	self->y *= scalar;
}
