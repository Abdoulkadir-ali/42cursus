/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 21:15:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/27 23:45:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static	void	calc_viewport(t_window *win, t_anim *anim, t_render_params *p)
{
	t_anim_clip	*clip;
	float		scale;
	int			bob;

	clip = anim_get_active_clip(anim);
	p->dst.y = DESIRED_HEIGHT;
	p->dst.x = (clip->size.x * p->dst.y + clip->size.y / 2) / clip->size.y;
	if ((int)p->dst.x > win->width - 64)
	{
		p->dst.x = win->width - 64;
		p->dst.y = (clip->size.y * p->dst.x + clip->size.x / 2) / clip->size.x;
	}
	scale = (float)p->dst.y / 180.0f;
	p->offset.x = win->width / 2 - p->dst.x / 2;
	p->offset.x += (int)(clip->offset.x * scale) + win->width / 12;
	bob = (int)(sinf(anim->bob_phase) * 5.0f);
	p->offset.y = win->height - p->dst.y;
	p->offset.y += (int)(clip->offset.y * scale) + bob;
}

static void	render_valid_frame(t_window *win, t_anim *anim, t_anim_clip *clip)
{
	t_render_params	p;
	size_t			frame;

	frame = anim->state.frame % clip->frame_count;
	if (!clip->frames[frame])
	{
		anim_render_hud(win, &anim->punch_texture);
		return ;
	}
	p.win = win;
	p.buf = clip->frames[frame];
	p.src = clip->size;
	calc_viewport(win, anim, &p);
	anim_render_scaled(&p);
}

void	render_weapon_sprite(t_window *win, t_anim *anim)
{
	t_anim_clip	*clip;

	if (!anim)
		return ;
	clip = anim_get_active_clip(anim);
	if (!clip || clip->frame_count == 0 || !clip->frames)
	{
		anim_render_hud(win, &anim->punch_texture);
		return ;
	}
	render_valid_frame(win, anim, clip);
}
