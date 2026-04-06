/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 10:52:37 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "color.h"

t_vec3f	rt_unpack_color(size_t c)
{
	t_vec3	v;
	t_vec3f	vf;

	v = unpack_rgb(c);
	vf.x = (float)v.x;
	vf.y = (float)v.y;
	vf.z = (float)v.z;
	vf.w = (float)v.w;
	return (vf);
}

size_t	rt_pack_color(t_vec3f v)
{
	t_vec3	vd;

	vd.x = (double)v.x;
	vd.y = (double)v.y;
	vd.z = (double)v.z;
	vd.w = (double)v.w;
	return ((size_t)pack_rgb(vd));
}

t_vec3i	rt_unpack_color_v(size_t c)
{
	return (unpack_rgb_v((uint32_t)c));
}

size_t	rt_pack_color_v(t_vec3i v)
{
	return ((size_t)pack_rgb_v(v));
}

/*
** apply_bcg: applies brightness, contrast, gamma, and saturation
** to a float[3] RGB channel array (values in [0,255]).
** All opts values are in [0,100] with 50 = neutral.
*/
void	apply_bcg(t_vec3f *ch, const t_raytracer_settings *opts)
{
	t_vec2f	p;
	t_vec3f	f;

	f.x = (float)((opts->brightness - 50.0) / 50.0 * 255.0);
	ch->x += f.x;
	ch->y += f.x;
	ch->z += f.x;
	f.y = (float)(opts->contrast / 50.0);
	p.y = 127.5f;
	ch->x = (ch->x - p.y) * f.y + p.y;
	ch->y = (ch->y - p.y) * f.y + p.y;
	ch->z = (ch->z - p.y) * f.y + p.y;
	f.z = (float)(opts->saturation / 50.0);
	p.x = 0.299f * ch->x + 0.587f * ch->y + 0.114f * ch->z;
	ch->x = p.x + (ch->x - p.x) * f.z;
	ch->y = p.x + (ch->y - p.x) * f.z;
	ch->z = p.x + (ch->z - p.x) * f.z;
	if (opts->gamma > 0.0)
	{
		float	exp_val;

		exp_val = (float)(50.0 / opts->gamma);
		ch->x = powf(fmaxf(ch->x / 255.0f, 0.0f), exp_val) * 255.0f;
		ch->y = powf(fmaxf(ch->y / 255.0f, 0.0f), exp_val) * 255.0f;
		ch->z = powf(fmaxf(ch->z / 255.0f, 0.0f), exp_val) * 255.0f;
	}
	ch->x = fminf(fmaxf(ch->x, 0.0f), 255.0f);
	ch->y = fminf(fmaxf(ch->y, 0.0f), 255.0f);
	ch->z = fminf(fmaxf(ch->z, 0.0f), 255.0f);
}
