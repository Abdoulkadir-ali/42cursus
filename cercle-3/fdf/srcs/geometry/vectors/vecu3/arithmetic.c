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

void	vecu3_add(t_vecu3 *self, t_vecu3 other)
{
	self->x += other.x;
	self->y += other.y;
	self->z += other.z;
}

void	vecu3_sub(t_vecu3 *self, t_vecu3 other)
{
	self->x -= other.x;
	self->y -= other.y;
	self->z -= other.z;
}

void	vecu3_multiply(t_vecu3 *self, t_vecu3 other)
{
	self->x *= other.x;
	self->y *= other.y;
	self->z *= other.z;
}

void	vecu3_divide(t_vecu3 *self, t_vecu3 other)
{
	if (other.x != 0 && other.y != 0 && other.z != 0)
	{
		self->x /= other.x;
		self->y /= other.y;
		self->z /= other.z;
	}
	else
	{
		ft_putstr_fd("Zero division error\n", 2);
		exit(1);
	}
}

void	vecu3_multiply_scalar(t_vecu3 *self, unsigned int scalar)
{
	self->x *= scalar;
	self->y *= scalar;
	self->z *= scalar;
}
