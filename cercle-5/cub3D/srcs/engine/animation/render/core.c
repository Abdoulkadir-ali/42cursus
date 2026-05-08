/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 21:15:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/27 21:15:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void	anim_render_scaled(t_render_params *p)
{
	size_t			py;
	size_t			px;
	unsigned int	pix;
	t_vec2i			v;
	size_t			idx;

	py = -1;
	while (++py < p->dst.y)
	{
		px = -1;
		while (++px < p->dst.x)
		{
			idx = (py * p->src.y / p->dst.y) * p->src.x;
			idx += (px * p->src.x / p->dst.x);
			pix = p->buf[idx];
			if (anim_is_transparent(pix))
				continue ;
			v = (t_vec2i){p->offset.x + (int)px, p->offset.y + (int)py};
			anim_write_pixel(p->win, v, pix);
		}
	}
}

static	void	blit_px(t_window *win, t_vec2i b, t_vec2i p, unsigned int pix)
{
	t_vec2i	v;
	int		sy;
	int		sx;

	sy = -1;
	while (++sy < WPN_SCALE)
	{
		sx = -1;
		while (++sx < WPN_SCALE)
		{
			v.x = b.x + p.x * WPN_SCALE + sx;
			v.y = b.y + p.y * WPN_SCALE + sy;
			anim_write_pixel(win, v, pix);
		}
	}
}

void	anim_render_hud(t_window *win, t_texture *tex)
{
	t_vec2i			base;
	size_t			px;
	size_t			py;
	unsigned int	pix;

	if (!tex || !tex->data)
		return ;
	base.x = win->width / 2 - (tex->size.x * WPN_SCALE) / 2;
	base.y = win->height - tex->size.y * WPN_SCALE;
	py = -1;
	while (++py < tex->size.y)
	{
		px = -1;
		while (++px < tex->size.x)
		{
			pix = tex->data[py * tex->size.x + px];
			if (!anim_is_transparent(pix))
				blit_px(win, base, (t_vec2i){(int)px, (int)py}, pix);
		}
	}
}
