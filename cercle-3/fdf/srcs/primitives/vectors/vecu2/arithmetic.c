/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arithmetic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 13:42:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/23 22:54:10 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "primitives.h"

void	vecu2_add(t_vecu2 *self, t_vecu2 other)
{
	self->x += other.x;
	self->y += other.y;
}

void	vecu2_sub(t_vecu2 *self, t_vecu2 other)
{
	self->x -= other.x;
	self->y -= other.y;
}

void	vecu2_multiply(t_vecu2 *self, t_vecu2 other)
{
	self->x *= other.x;
	self->y *= other.y;
}

void	vecu2_divide(t_vecu2 *self, t_vecu2 other)
{
	if (other.x != 0)
		self->x /= other.x;
	if (other.y != 0)
		self->y /= other.y;
}

void	vecu2_multiply_scalar(t_vecu2 *self, unsigned int scalar)
{
	self->x *= scalar;
	self->y *= scalar;
}
