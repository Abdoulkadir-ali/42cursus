/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 17:00:36 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/12 22:25:07 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vectors.h"

t_vec2	vec2_add(t_vec2 self, t_vec2 other)
{
	t_vec2	r;

	r.x = self.x + other.x;
	r.y = self.y + other.y;
	r.add = vec2_add;
	r.sub = vec2_sub;
	r.multiply = vec2_multiply;
	r.divide = vec2_divide;
	r.multiply_scalar = vec2_multiply_scalar;
	return (r);
}

t_vec2	vec2_sub(t_vec2 self, t_vec2 other)
{
	t_vec2	r;

	r.x = self.x - other.x;
	r.y = self.y - other.y;
	r.add = vec2_add;
	r.sub = vec2_sub;
	r.multiply = vec2_multiply;
	r.divide = vec2_divide;
	r.multiply_scalar = vec2_multiply_scalar;
	return (r);
}

t_vec2	vec2_multiply(t_vec2 self, t_vec2 other)
{
	t_vec2	r;

	r.x = self.x * other.x;
	r.y = self.y * other.y;
	r.add = vec2_add;
	r.sub = vec2_sub;
	r.multiply = vec2_multiply;
	r.divide = vec2_divide;
	r.multiply_scalar = vec2_multiply_scalar;
	return (r);
}

t_vec2	vec2_divide(t_vec2 self, t_vec2 other)
{
	t_vec2	r;

	if (other.x)
		r.x = self.x / other.x;
	if (other.y)
		r.y = self.y / other.y;
	r.add = vec2_add;
	r.sub = vec2_sub;
	r.multiply = vec2_multiply;
	r.divide = vec2_divide;
	r.multiply_scalar = vec2_multiply_scalar;
	return (r);
}

t_vec2	vec2_multiply_scalar(t_vec2 self, double scalar)
{
	t_vec2	r;

	r.x = self.x * scalar;
	r.y = self.y * scalar;
	r.add = vec2_add;
	r.sub = vec2_sub;
	r.multiply = vec2_multiply;
	r.divide = vec2_divide;
	r.multiply_scalar = vec2_multiply_scalar;
	return (r);
}