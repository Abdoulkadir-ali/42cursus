/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 17:00:36 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/12 22:23:20 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vectors.h"

t_vec2d	vec2d_add(t_vec2d self, t_vec2d other)
{
	t_vec2d	r;

	r.x = self.x + other.x;
	r.y = self.y + other.y;
	r.add = vec2d_add;
	r.sub = vec2d_sub;
	r.multiply = vec2d_multiply;
	r.divide = vec2d_divide;
	r.multiply_scalar = vec2d_multiply_scalar;
	return (r);
}

t_vec2d	vec2d_sub(t_vec2d self, t_vec2d other)
{
	t_vec2d	r;

	r.x = self.x - other.x;
	r.y = self.y - other.y;
	r.add = vec2d_add;
	r.sub = vec2d_sub;
	r.multiply = vec2d_multiply;
	r.divide = vec2d_divide;
	r.multiply_scalar = vec2d_multiply_scalar;
	return (r);
}

t_vec2d	vec2d_multiply(t_vec2d self, t_vec2d other)
{
	t_vec2d	r;

	r.x = self.x * other.x;
	r.y = self.y * other.y;
	r.add = vec2d_add;
	r.sub = vec2d_sub;
	r.multiply = vec2d_multiply;
	r.divide = vec2d_divide;
	r.multiply_scalar = vec2d_multiply_scalar;
	return (r);
}

t_vec2d	vec2d_divide(t_vec2d self, t_vec2d other)
{
	t_vec2d	r;

	if (other.x)
		r.x = self.x / other.x;
	if (other.y)
		r.y = self.y / other.y;
	r.add = vec2d_add;
	r.sub = vec2d_sub;
	r.multiply = vec2d_multiply;
	r.divide = vec2d_divide;
	r.multiply_scalar = vec2d_multiply_scalar;
	return (r);
}

t_vec2d	vec2d_multiply_scalar(t_vec2d self, double scalar)
{
	t_vec2d	r;

	r.x = self.x * scalar;
	r.y = self.y * scalar;
	r.add = vec2d_add;
	r.sub = vec2d_sub;
	r.multiply = vec2d_multiply;
	r.divide = vec2d_divide;
	r.multiply_scalar = vec2d_multiply_scalar;
	return (r);
}