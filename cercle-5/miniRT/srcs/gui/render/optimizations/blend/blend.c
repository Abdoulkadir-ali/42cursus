/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blend.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 23:35:55 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

#define BLEND_TARGET_DT		0.04
#define BLEND_ALPHA_MIN		0.15f

static int	blend_pixel(int nc, int oc, int a)
{
	int	ia;
	int	r;
	int	g;
	int	b;

	ia = 256 - a;
	r = (a * ((nc >> 16) & 0xFF) + ia * ((oc >> 16) & 0xFF)) >> 8;
	g = (a * ((nc >> 8) & 0xFF) + ia * ((oc >> 8) & 0xFF)) >> 8;
	b = (a * (nc & 0xFF) + ia * (oc & 0xFF)) >> 8;
	return ((r << 16) | (g << 8) | b);
}

static int	calc_alpha(double dt)
{
	float	alpha;

	if (dt < 1e-6)
		return (256);
	alpha = (float)(BLEND_TARGET_DT / dt);
	if (alpha > 1.0f)
		alpha = 1.0f;
	if (alpha < BLEND_ALPHA_MIN)
		alpha = BLEND_ALPHA_MIN;
	return ((int)(alpha * 256));
}

void	blend_temporal(t_gui *gui, double dt)
{
	uint32_t	*disp;
	int			*prev;
	size_t		n;
	int			alpha;
	size_t		i;

	if (!gui->render.prev_buf)
		return ;
	alpha = calc_alpha(dt);
	disp = (uint32_t *)gui->win.disp_addr;
	prev = gui->render.prev_buf;
	n = (size_t)gui->win.disp_size.x * gui->win.disp_size.y;
	i = 0;
	while (i < n)
	{
		disp[i] = (uint32_t)blend_pixel((int)disp[i], (int)prev[i], alpha);
		prev[i] = disp[i];
		i++;
	}
}

void	blend_free(t_gui *gui)
{
	free(gui->render.prev_buf);
	gui->render.prev_buf = NULL;
}
