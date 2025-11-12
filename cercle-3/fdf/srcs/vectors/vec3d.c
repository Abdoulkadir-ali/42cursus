/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 17:00:36 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/12 22:25:21 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vectors.h"

t_vec3d	vec3d_add(t_vec3d self, t_vec3d other)
{
	t_vec3d	r;

	r.x = self.x + other.x;
	r.y = self.y + other.y;
	r.z = self.z + other.z;
	r.add = vec3d_add;
	r.sub = vec3d_sub;
	r.multiply = vec3d_multiply;
	r.divide = vec3d_divide;
	r.multiply_scalar = vec3d_multiply_scalar;
	return (r);
}

t_vec3d	vec3d_sub(t_vec3d self, t_vec3d other)
{
	t_vec3d	r;

	r.x = self.x - other.x;
	r.y = self.y - other.y;
	r.z = self.z - other.z;
	r.add = vec3d_add;
	r.sub = vec3d_sub;
	r.multiply = vec3d_multiply;
	r.divide = vec3d_divide;
	r.multiply_scalar = vec3d_multiply_scalar;
	return (r);
}

t_vec3d	vec3d_multiply(t_vec3d self, t_vec3d other)
{
	t_vec3d	r;

	r.x = self.x * other.x;
	r.y = self.y * other.y;
	r.z = self.z * other.z;
	r.add = vec3d_add;
	r.sub = vec3d_sub;
	r.multiply = vec3d_multiply;
	r.divide = vec3d_divide;
	r.multiply_scalar = vec3d_multiply_scalar;
	return (r);
}

t_vec3d	vec3d_divide(t_vec3d self, t_vec3d other)
{
	t_vec3d	r;

	if (other.x)
		r.x = self.x / other.x;
	if (other.y)
		r.y = self.y / other.y;
	if (other.z)
		r.z = self.z / other.z;
	r.add = vec3d_add;
	r.sub = vec3d_sub;
	r.multiply = vec3d_multiply;
	r.divide = vec3d_divide;
	r.multiply_scalar = vec3d_multiply_scalar;
	return (r);
}

t_vec3d	vec3d_multiply_scalar(t_vec3d self, double scalar)
{
	t_vec3d	r;

	r.x = self.x * scalar;
	r.y = self.y * scalar;
	r.z = self.z * scalar;
	r.add = vec3d_add;
	r.sub = vec3d_sub;
	r.multiply = vec3d_multiply;
	r.divide = vec3d_divide;
	r.multiply_scalar = vec3d_multiply_scalar;
	return (r);
}