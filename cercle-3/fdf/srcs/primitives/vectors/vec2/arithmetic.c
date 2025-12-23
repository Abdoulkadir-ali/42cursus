/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arithmetic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 13:40:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/23 22:54:10 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "primitives.h"

void	vec2_add(t_vec2 *self, t_vec2 other)
{
	self->x += other.x;
	self->y += other.y;
}

void	vec2_sub(t_vec2 *self, t_vec2 other)
{
	self->x -= other.x;
	self->y -= other.y;
}

void	vec2_multiply(t_vec2 *self, t_vec2 other)
{
	self->x *= other.x;
	self->y *= other.y;
}

void	vec2_divide(t_vec2 *self, t_vec2 other)
{
	if (other.x != 0)
		self->x /= other.x;
	if (other.y != 0)
		self->y /= other.y;
}

void	vec2_multiply_scalar(t_vec2 *self, int scalar)
{
	self->x *= scalar;
	self->y *= scalar;
}
