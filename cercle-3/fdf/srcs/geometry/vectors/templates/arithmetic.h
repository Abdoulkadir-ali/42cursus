/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arithmetic.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 00:40:00 by abdoali          ###   ########.fr       */
/*   Updated: 2025/12/21 00:40:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Template for vector arithmetic operations.
**
** Required Macros:
** - T_VEC: The vector structure type (e.g. t_vec3)
** - T_SCALAR: The scalar type (e.g. int, double, unsigned int)
** - PREFIX: The function prefix (e.g. vec3)
** - COMPONENT_COUNT: 2 or 3
*/

#ifndef CONCAT
# define CONCAT(a, b) a ## _ ## b
#endif

#ifndef FN_NAME
# define FN_NAME(prefix, name) CONCAT(prefix, name)
#endif

void	FN_NAME(PREFIX, add)(T_VEC *self, T_VEC other)
{
	self->x += other.x;
	self->y += other.y;
#if COMPONENT_COUNT == 3
	self->z += other.z;
#endif
}

void	FN_NAME(PREFIX, sub)(T_VEC *self, T_VEC other)
{
	self->x -= other.x;
	self->y -= other.y;
#if COMPONENT_COUNT == 3
	self->z -= other.z;
#endif
}

void	FN_NAME(PREFIX, multiply)(T_VEC *self, T_VEC other)
{
	self->x *= other.x;
	self->y *= other.y;
#if COMPONENT_COUNT == 3
	self->z *= other.z;
#endif
}

void	FN_NAME(PREFIX, divide)(T_VEC *self, T_VEC other)
{
#if COMPONENT_COUNT == 3
	if (other.x != 0 && other.y != 0 && other.z != 0)
	{
		self->x /= other.x;
		self->y /= other.y;
		self->z /= other.z;
	}
#else
	if (other.x != 0 && other.y != 0)
	{
		self->x /= other.x;
		self->y /= other.y;
	}
#endif
	else
	{
		ft_putstr_fd("Zero division error\n", 2);
		exit(1);
	}
}

void	FN_NAME(PREFIX, multiply_scalar)(T_VEC *self, T_SCALAR scalar)
{
	self->x *= scalar;
	self->y *= scalar;
#if COMPONENT_COUNT == 3
	self->z *= scalar;
#endif
}
