/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sample.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 19:14:18 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 13:46:37 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions/primitives/objects/surface.h"

static t_vec3	sample_checker(t_texture *tex, double u, double v)
{
	int	ch;

	ch = (int)(floor(u * tex->scale) + floor(v * tex->scale)) % 2;
	if ((u * tex->scale) < 0)
		ch++;
	if ((v * tex->scale) < 0)
		ch++;
	if (ch % 2)
		return (tex->color_a);
	return (tex->color_b);
}

static t_vec3	texel_at(t_texture *tex, int x, int y)
{
	char			*px;
	unsigned int	cl;

	x = x % tex->width;
	if (x < 0)
		x += tex->width;
	y = y % tex->height;
	if (y < 0)
		y += tex->height;
	px = tex->addr + (y * tex->len + x * (tex->bpp / 8));
	cl = *(unsigned int *)px;
	return (vec3((cl >> 16) & 0xFF, (cl >> 8) & 0xFF, cl & 0xFF));
}

static t_vec3	sample_bitmap(t_texture *tex, double u, double v)
{
	double	f[2];
	int		i[2];
	double	w[2];
	t_vec3	t_b[2];

	f[0] = u * tex->width - 0.5;
	f[1] = v * tex->height - 0.5;
	i[0] = f[0];
	if (f[0] < 0.0 && (double)i[0] != f[0])
		i[0]--;
	i[1] = f[1];
	if (f[1] < 0.0 && (double)i[1] != f[1])
		i[1]--;
	w[0] = f[0] - (double)i[0];
	w[1] = f[1] - (double)i[1];
	t_b[0] = vec3_add(vec3_scale(texel_at(tex, i[0], i[1]), 1.0 - w[0]),
			vec3_scale(texel_at(tex, i[0] + 1, i[1]), w[0]));
	t_b[1] = vec3_add(vec3_scale(texel_at(tex, i[0], i[1] + 1), 1.0 - w[0]),
			vec3_scale(texel_at(tex, i[0] + 1, i[1] + 1), w[0]));
	return (vec3_add(vec3_scale(t_b[0], 1.0 - w[1]), vec3_scale(t_b[1], w[1])));
}

/*
** Samples a color from a texture (Solid, Checker, or Bitmap).
*/
t_vec3	sample_texture(t_texture *tex, double u, double v)
{
	static int count = 0;
	if (count < 10)
	{
		ft_print_debug("sample_texture: type=%d addr=%p u=%f v=%f\n", 
			tex->type, tex->addr, u, v);
		count++;
	}
	if (tex->type == TEX_SOLID)
		return (tex->color_a);
	if (tex->type == TEX_CHECKER)
		return (sample_checker(tex, u, v));
	if (tex->type == TEX_BITMAP && tex->addr)
		return (sample_bitmap(tex, u, v));
	return (vec3(255, 0, 255));
}
