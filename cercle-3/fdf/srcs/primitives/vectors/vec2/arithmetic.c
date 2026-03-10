/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arithmetic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 13:40:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 03:37:26 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "primitives.h"

/**
 * @brief Add another 2D integer vector in place.
 * @param self Vector to modify.
 * @param other Value to add component-wise.
 */
void	vec2_add(t_vec2 *self, t_vec2 other)
{
	self->x += other.x;
	self->y += other.y;
}

/**
 * @brief Subtract another 2D integer vector in place.
 * @param self Vector to modify.
 * @param other Value to subtract component-wise.
 */
void	vec2_sub(t_vec2 *self, t_vec2 other)
{
	self->x -= other.x;
	self->y -= other.y;
}

/**
 * @brief Multiply by another 2D integer vector in place.
 * @param self Vector to modify.
 * @param other Value to multiply component-wise.
 */
void	vec2_multiply(t_vec2 *self, t_vec2 other)
{
	self->x *= other.x;
	self->y *= other.y;
}

/**
 * @brief Divide by another 2D integer vector in place.
 * @param self Vector to modify.
 * @param other Divisor vector checked component-wise.
 */
void	vec2_divide(t_vec2 *self, t_vec2 other)
{
	if (other.x != 0)
		self->x /= other.x;
	if (other.y != 0)
		self->y /= other.y;
}

/**
 * @brief Multiply both components by one integer scalar.
 * @param self Vector to modify.
 * @param scalar Scalar multiplier.
 */
void	vec2_multiply_scalar(t_vec2 *self, int scalar)
{
	self->x *= scalar;
	self->y *= scalar;
}
