/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 17:00:36 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/12 22:25:16 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vectors.h"

t_vec3	vec3_add(t_vec3 self, t_vec3 other)
{
	t_vec3	r;

	r.x = self.x + other.x;
	r.y = self.y + other.y;
	r.z = self.z + other.z;
	r.add = vec3_add;
	r.sub = vec3_sub;
	r.multiply = vec3_multiply;
	r.divide = vec3_divide;
	r.multiply_scalar = vec3_multiply_scalar;
	return (r);
}

t_vec3	vec3_sub(t_vec3 self, t_vec3 other)
{
	t_vec3	r;

	r.x = self.x - other.x;
	r.y = self.y - other.y;
	r.z = self.z - other.z;
	r.add = vec3_add;
	r.sub = vec3_sub;
	r.multiply = vec3_multiply;
	r.divide = vec3_divide;
	r.multiply_scalar = vec3_multiply_scalar;
	return (r);
}

t_vec3	vec3_multiply(t_vec3 self, t_vec3 other)
{
	t_vec3	r;

	r.x = self.x * other.x;
	r.y = self.y * other.y;
	r.z = self.z * other.z;
	r.add = vec3_add;
	r.sub = vec3_sub;
	r.multiply = vec3_multiply;
	r.divide = vec3_divide;
	r.multiply_scalar = vec3_multiply_scalar;
	return (r);
}

t_vec3	vec3_divide(t_vec3 self, t_vec3 other)
{
	t_vec3	r;

	if (other.x)
		r.x = self.x / other.x;
	if (other.y)
		r.y = self.y / other.y;
	if (other.z)
		r.z = self.z / other.z;
	r.add = vec3_add;
	r.sub = vec3_sub;
	r.multiply = vec3_multiply;
	r.divide = vec3_divide;
	r.multiply_scalar = vec3_multiply_scalar;
	return (r);
}

t_vec3	vec3_multiply_scalar(t_vec3 self, double scalar)
{
	t_vec3	r;

	r.x = self.x * scalar;
	r.y = self.y * scalar;
	r.z = self.z * scalar;
	r.add = vec3_add;
	r.sub = vec3_sub;
	r.multiply = vec3_multiply;
	r.divide = vec3_divide;
	r.multiply_scalar = vec3_multiply_scalar;
	return (r);
}