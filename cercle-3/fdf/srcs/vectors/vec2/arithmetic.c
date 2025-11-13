/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arithmetic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 17:00:36 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/13 12:59:46 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vectors.h"
#include <xmmintrin.h>
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
		ft_putstr_fd("Zero division error", 2);
		exit(1);
	}
}

void	vec2_multiply_scalar(t_vec2 *self, double scalar)
{
	__m128d	va;
	__m128d	vs;
	__m128d	vc;

	va = _mm_set_pd((double)self->y, (double)self->x);
	vs = _mm_set1_pd(scalar);
	vc = _mm_mul_pd(va, vs);
	self->x = (int)_mm_cvtsd_f64(vc);
	self->y = (int)_mm_cvtsd_f64(_mm_unpackhi_pd(vc, vc));
}
