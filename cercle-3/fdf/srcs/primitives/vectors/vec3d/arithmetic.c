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
 * @brief Add another 3D double vector in place.
 * @param self Vector to modify.
 * @param other Value to add component-wise.
 */
void	vec3d_add(t_vec3d *self, t_vec3d other)
{
	self->x += other.x;
	self->y += other.y;
	self->z += other.z;
}

/**
 * @brief Subtract another 3D double vector in place.
 * @param self Vector to modify.
 * @param other Value to subtract component-wise.
 */
void	vec3d_sub(t_vec3d *self, t_vec3d other)
{
	self->x -= other.x;
	self->y -= other.y;
	self->z -= other.z;
}

/**
 * @brief Multiply by another 3D double vector in place.
 * @param self Vector to modify.
 * @param other Value to multiply component-wise.
 */
void	vec3d_multiply(t_vec3d *self, t_vec3d other)
{
	self->x *= other.x;
	self->y *= other.y;
	self->z *= other.z;
}

/**
 * @brief Divide by another 3D double vector in place when divisors are non-zero.
 * @param self Vector to modify.
 * @param other Divisor vector checked component-wise.
 */
void	vec3d_divide(t_vec3d *self, t_vec3d other)
{
	if (other.x != 0)
		self->x /= other.x;
	if (other.y != 0)
		self->y /= other.y;
	if (other.z != 0)
		self->z /= other.z;
}

/**
 * @brief Multiply all components by one double scalar.
 * @param self Vector to modify.
 * @param scalar Scalar multiplier.
 */
void	vec3d_multiply_scalar(t_vec3d *self, double scalar)
{
	self->x *= scalar;
	self->y *= scalar;
	self->z *= scalar;
}
