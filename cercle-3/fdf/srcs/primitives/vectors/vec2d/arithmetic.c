/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arithmetic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 19:45:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 02:27:15 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "primitives.h"

/**
 * @brief Add another 2D double vector in place.
 * @param self Vector to modify.
 * @param other Value to add component-wise.
 */
void	vec2d_add(t_vec2d *self, t_vec2d other)
{
	self->x += other.x;
	self->y += other.y;
}

/**
 * @brief Subtract another 2D double vector in place.
 * @param self Vector to modify.
 * @param other Value to subtract component-wise.
 */
void	vec2d_sub(t_vec2d *self, t_vec2d other)
{
	self->x -= other.x;
	self->y -= other.y;
}

/**
 * @brief Multiply by another 2D double vector in place.
 * @param self Vector to modify.
 * @param other Value to multiply component-wise.
 */
void	vec2d_multiply(t_vec2d *self, t_vec2d other)
{
	self->x *= other.x;
	self->y *= other.y;
}

/**
 * @brief Divide by another 2D double vector in place when divisors are non-zero.
 * @param self Vector to modify.
 * @param other Divisor vector checked component-wise.
 */
void	vec2d_divide(t_vec2d *self, t_vec2d other)
{
	if (other.x != 0)
		self->x /= other.x;
	if (other.y != 0)
		self->y /= other.y;
}

/**
 * @brief Multiply both components by one double scalar.
 * @param self Vector to modify.
 * @param scalar Scalar multiplier.
 */
void	vec2d_multiply_scalar(t_vec2d *self, double scalar)
{
	self->x *= scalar;
	self->y *= scalar;
}
