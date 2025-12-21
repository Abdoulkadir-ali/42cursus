/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arithmetic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 00:50:00 by abdoali          ###   ########.fr       */
/*   Updated: 2025/12/21 00:50:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry.h"

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

void	vecu2_multiply_scalar(t_vecu2 *self, unsigned int scalar)
{
	self->x *= scalar;
	self->y *= scalar;
}
