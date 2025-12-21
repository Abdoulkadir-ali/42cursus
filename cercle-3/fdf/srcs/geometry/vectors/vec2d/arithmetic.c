/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arithmetic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 17:00:36 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/13 15:07:06 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry.h"
#include <stdlib.h>

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
	if (other.x != 0.0 && other.y != 0.0)
	{
		self->x /= other.x;
		self->y /= other.y;
	}
	else
	{
		ft_putstr_fd("Zero division error\n", 2);
		exit(1);
	}
}

void	vec2d_multiply_scalar(t_vec2d *self, double scalar)
{
	self->x *= scalar;
	self->y *= scalar;
}
