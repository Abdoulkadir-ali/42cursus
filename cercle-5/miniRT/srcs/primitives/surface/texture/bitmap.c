/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 05:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "surface.h"

static void	get_bilinear(t_texture *tex, double u, double v, t_bilinear *b)
{
	b->ux = u * tex->width - TEX_CENTER_OFFSET;
	b->uy = v * tex->height - TEX_CENTER_OFFSET;
	b->xi = (int)b->ux;
	if (b->ux < 0.0 && (double)b->xi != b->ux)
		b->xi--;
	b->yi = (int)b->uy;
	if (b->uy < 0.0 && (double)b->yi != b->uy)
		b->yi--;
	b->wx = b->ux - (double)b->xi;
	b->wy = b->uy - (double)b->yi;
}

/**
 * @brief Samples a bitmap texture with bilinear filtering.
 * @param tex Pointer to the bitmap texture.
 * @param u Horizontal UV.
 * @param v Vertical UV.
 * @return t_vec3 The interpolated color.
 */
t_vec3	sample_bitmap(t_texture *tex, double u, double v)
{
	t_bilinear	b;
	t_vec3		top;
	t_vec3		bot;

	get_bilinear(tex, u, v, &b);
	top = vec3_add(vec3_scale(texel_at(tex, b.xi, b.yi), 1.0 - b.wx),
			vec3_scale(texel_at(tex, b.xi + 1, b.yi), b.wx));
	bot = vec3_add(vec3_scale(texel_at(tex, b.xi, b.yi + 1), 1.0 - b.wx),
			vec3_scale(texel_at(tex, b.xi + 1, b.yi + 1), b.wx));
	return (vec3_add(vec3_scale(top, 1.0 - b.wy), vec3_scale(bot, b.wy)));
}
