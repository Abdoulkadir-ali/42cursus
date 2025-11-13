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
	ft_putstr_fd("Zero division error", 2);
	exit(1);
}

void	vec2d_multiply_scalar(t_vec2d *self, double scalar)
{
	__m128d	va;
	__m128d	vs;
	__m128d	vc;

	va = _mm_load_pd((double *)self);
	vs = _mm_set1_pd(scalar);
	vc = _mm_mul_pd(va, vs);
	_mm_store_pd((double *)self, vc);
}
