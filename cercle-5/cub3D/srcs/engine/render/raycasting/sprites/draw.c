/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 15:16:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/08 02:02:39 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "gameplay.h"

static void	draw_pixel(t_window *win, t_entity *ent, t_vec2i p, t_spr_draw *sd)
{
	uint32_t	*tex;
	uint32_t	pix;
	t_vec2i		tex_p;
	int			d;

	tex = ent->clip->frames[ent->anim.frame % ent->clip->frame_count];
	tex_p.x = ((p.x - sd->start.x) * (int)ent->clip->size.x) / sd->spr_sz.x;
	if (tex_p.x < 0 || (size_t)tex_p.x >= ent->clip->size.x)
		return ;
	d = p.y - sd->start.y;
	tex_p.y = (d * (int)ent->clip->size.y) / sd->spr_sz.y;
	if (tex_p.y < 0 || (size_t)tex_p.y >= ent->clip->size.y)
		return ;
	pix = tex[tex_p.y * ent->clip->size.x + tex_p.x];
	if (anim_is_transparent(pix))
		return ;
	*((uint32_t *)(win->addr + p.y * win->line_len) + p.x) = pix;
}

void	draw_sprite(t_window *win, t_entity *ent, t_vec2 t, t_spr_draw *sd)
{
	t_vec2i	p;
	int		idx;

	sd->start.x -= sd->spr_sz.x / 2;
	sd->start.y = sd->dsy;
	sd->depth = t.y;
	p.x = sd->start.x - 1;
	while (++p.x < sd->start.x + sd->spr_sz.x)
	{
		if (p.x < 0 || p.x >= win->width)
			continue ;
		p.y = sd->start.y - 1;
		while (++p.y < sd->start.y + sd->spr_sz.y)
		{
			if (p.y < 0 || p.y >= win->height)
				continue ;
			idx = p.y * win->width + p.x;
			if (t.y >= win->z_buffer[idx])
				continue ;
			draw_pixel(win, ent, p, sd);
		}
	}
}
