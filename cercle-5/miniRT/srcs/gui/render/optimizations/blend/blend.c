/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blend.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 01:05:15 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "optimizations.h"

/*
** Computes a blend weight in [0,256] based on frame delta time.
** Slower frames blend less (more new), faster frames blend more (more prev).
*/
static size_t	calc_alpha(double dt)
{
	float	alpha;

	if (dt < 1e-6)
		return (256);
	alpha = (float)(BLEND_TARGET_DT / dt);
	if (alpha > 1.0f)
		alpha = 1.0f;
	if (alpha < BLEND_ALPHA_MIN)
		alpha = BLEND_ALPHA_MIN;
	return ((size_t)(alpha * 256));
}

/*
** Blends one pixel: alpha/256 of prev, (256-alpha)/256 of new.
*/
static uint32_t	blend_pixel(uint32_t nc, uint32_t oc, size_t a)
{
	size_t	ia;

	ia = 256 - a;
	return ((uint32_t)(
		((a * ((oc >> 16) & 0xFF) + ia * ((nc >> 16) & 0xFF)) >> 8) << 16
		| ((a * ((oc >> 8) & 0xFF) + ia * ((nc >> 8) & 0xFF)) >> 8) << 8
		| (a * (oc & 0xFF) + ia * (nc & 0xFF)) >> 8));
}

/*
** Blends the current display buffer against the previous frame.
** prev_color is updated in-place for the next frame.
*/
void	blend_temporal(t_gui *gui, double dt)
{
	t_optimizations	*o;
	uint32_t		*disp;
	size_t			n;
	size_t			alpha;
	size_t			i;

	o = &gui->opts;
	if (!o->prev_color || !o->prev_valid)
		return ;
	alpha = calc_alpha(dt);
	disp = (uint32_t *)gui->win.addr;
	n = (size_t)gui->win.size.x * (size_t)gui->win.size.y;
	i = 0;
	while (i < n)
	{
		disp[i] = blend_pixel(disp[i], o->prev_color[i], alpha);
		i++;
	}
}
