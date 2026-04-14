/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/12 22:03:20 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "color.h"

/* rt_unpack_color and rt_pack_color are now static inline in render.h */

/*
** gamma == 50 -> exp_val == 1.0 -> powf(x,1) = x. Skip to avoid 3
** expensive powf calls per pixel when using default neutral gamma.
*/
static void	apply_gamma(t_vec3f *ch, float gamma)
{
	float	exp_val;

	if (gamma <= 0.0)
		return ;
	exp_val = 50.0f / gamma;
	if (fabsf(exp_val - 1.0f) < 0.002f)
		return ;
	ch->x = powf(fmaxf(ch->x / 255.0f, 0.0f), exp_val) * 255.0f;
	ch->y = powf(fmaxf(ch->y / 255.0f, 0.0f), exp_val) * 255.0f;
	ch->z = powf(fmaxf(ch->z / 255.0f, 0.0f), exp_val) * 255.0f;
}

/*
** applies brightness, contrast, gamma, and saturation
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
	apply_gamma(ch, (float)opts->gamma);
	ch->x = fminf(fmaxf(ch->x, 0.0f), 255.0f);
	ch->y = fminf(fmaxf(ch->y, 0.0f), 255.0f);
	ch->z = fminf(fmaxf(ch->z, 0.0f), 255.0f);
}
