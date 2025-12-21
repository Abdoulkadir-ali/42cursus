/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arithmetic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 17:00:36 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/21 19:34:36 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry.h"
#include <stdlib.h>

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
	if (other.x != 0 && other.y != 0)
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

void	vec2_multiply_scalar(t_vec2 *self, int scalar)
{
	self->x *= scalar;
	self->y *= scalar;
}
