/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arithmetic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 13:42:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 03:37:34 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "primitives.h"

/**
 * @brief Add another 3D unsigned vector in place.
 * @param self Vector to modify.
 * @param other Value to add component-wise.
 */
void	vecu3_add(t_vecu3 *self, t_vecu3 other)
{
	self->x += other.x;
	self->y += other.y;
	self->z += other.z;
}

/**
 * @brief Subtract another 3D unsigned vector in place.
 * @param self Vector to modify.
 * @param other Value to subtract component-wise.
 */
void	vecu3_sub(t_vecu3 *self, t_vecu3 other)
{
	self->x -= other.x;
	self->y -= other.y;
	self->z -= other.z;
}

/**
 * @brief Multiply by another 3D unsigned vector in place.
 * @param self Vector to modify.
 * @param other Value to multiply component-wise.
 */
void	vecu3_multiply(t_vecu3 *self, t_vecu3 other)
{
	self->x *= other.x;
	self->y *= other.y;
	self->z *= other.z;
}

/**
 * @brief Divide by another 3D unsigned vector in place.
 * @param self Vector to modify.
 * @param other Divisor vector checked component-wise.
 */
void	vecu3_divide(t_vecu3 *self, t_vecu3 other)
{
	if (other.x != 0)
		self->x /= other.x;
	if (other.y != 0)
		self->y /= other.y;
	if (other.z != 0)
		self->z /= other.z;
}

/**
 * @brief Multiply all components by one unsigned scalar.
 * @param self Vector to modify.
 * @param scalar Scalar multiplier.
 */
void	vecu3_multiply_scalar(t_vecu3 *self, unsigned int scalar)
{
	self->x *= scalar;
	self->y *= scalar;
	self->z *= scalar;
}
