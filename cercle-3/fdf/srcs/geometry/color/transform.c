/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 18:24:11 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/25 19:11:16 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry.h"

void	clamp_color(t_vec3 *color, int min, int max)
{
	color->x = clamp((int)color->x, min, max);
	color->y = clamp((int)color->y, min, max);
	color->z = clamp((int)color->z, min, max);
}

t_vec3	shift_color(t_vec3 color, t_vec3 shift)
{
	vec3_add(&color, shift);
	clamp_color(&color, 0, 255);
	return (color);
}

t_vec3	interpolate_color(t_vec3 c1, t_vec3 c2, double ratio)
{
	t_vec3	res1;
	t_vec3	res2;
	int		factor1;
	int		factor2;

	factor1 = (int)((1.0 - ratio) * 256);
	factor2 = (int)(ratio * 256);
	res1 = c1;
	res2 = c2;
	vec3_multiply_scalar(&res1, factor1);
	vec3_multiply_scalar(&res2, factor2);
	vec3_add(&res1, res2);
	vec3_divide(&res1, create_color(256, 256, 256));
	clamp_color(&res1, 0, 255);
	return (res1);
}

t_vec3	get_height_color(double z, int min_z, int max_z)
{
	t_vec3				c_low;
	t_vec3				c_mid;
	t_vec3				c_high;
	t_height_color_ctx	ctx;

	c_low = create_color(0, 0, 255);
	c_mid = create_color(0, 255, 0);
	c_high = create_color(255, 0, 0);
	if (max_z == min_z)
		return (c_mid);
	ctx.shift = 0;
	if (min_z < 0)
		ctx.shift = -min_z;
	ctx.effective_z = z + ctx.shift;
	ctx.max_effective = max_z + ctx.shift;
	if (ctx.max_effective <= 0)
		return (c_mid);
	ctx.ratio = clamp_d(log(ctx.effective_z + 1) / log(ctx.max_effective + 1),
			0.0, 1.0);
	if (ctx.ratio < 0.5)
		return (interpolate_color(c_low, c_mid, ctx.ratio * 2.0));
	else
		return (interpolate_color(c_mid, c_high, (ctx.ratio - 0.5) * 2.0));
}
