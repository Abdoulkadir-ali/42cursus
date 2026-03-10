/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arithmetic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 13:42:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 03:37:43 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "primitives.h"

/**
 * @brief Add another 2D unsigned vector in place.
 * @param self Vector to modify.
 * @param other Value to add component-wise.
 */
void	vecu2_add(t_vecu2 *self, t_vecu2 other)
{
	self->x += other.x;
	self->y += other.y;
}

/**
 * @brief Subtract another 2D unsigned vector in place.
 * @param self Vector to modify.
 * @param other Value to subtract component-wise.
 */
void	vecu2_sub(t_vecu2 *self, t_vecu2 other)
{
	self->x -= other.x;
	self->y -= other.y;
}

/**
 * @brief Multiply by another 2D unsigned vector in place.
 * @param self Vector to modify.
 * @param other Value to multiply component-wise.
 */
void	vecu2_multiply(t_vecu2 *self, t_vecu2 other)
{
	self->x *= other.x;
	self->y *= other.y;
}

/**
 * @brief Divide by another 2D unsigned vector in place.
 * @param self Vector to modify.
 * @param other Divisor vector checked component-wise.
 */
void	vecu2_divide(t_vecu2 *self, t_vecu2 other)
{
	if (other.x != 0)
		self->x /= other.x;
	if (other.y != 0)
		self->y /= other.y;
}

/**
 * @brief Multiply both components by one unsigned scalar.
 * @param self Vector to modify.
 * @param scalar Scalar multiplier.
 */
void	vecu2_multiply_scalar(t_vecu2 *self, unsigned int scalar)
{
	self->x *= scalar;
	self->y *= scalar;
}
