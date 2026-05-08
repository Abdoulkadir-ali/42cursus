/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 16:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/08 02:01:34 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "physics.h"

static void	draw_column_pixel(t_render_col *rc, t_texture *tex, t_vec3i tyx)
{
	unsigned int	pix;
	uint32_t		*dst;

	dst = (uint32_t *)(rc->win->addr + (size_t)tyx.y * rc->win->line_len)
		+ rc->screen_x;
	pix = tex->data[tyx.z * tex->size.x + tyx.x];
	if (rc->dda->side == 1)
		pix = (pix & 0xFF000000) | (((pix & 0x00FEFEFE) >> 1) & 0x007F7F7F);
	*dst = pix;
	if (rc->win->z_buffer)
		rc->win->z_buffer[(size_t)tyx.y * rc->win->width + rc->screen_x]
			= rc->dda->perp_dist;
}

static void	set_tx(t_render_col *rc, t_texture *tex, int *tx)
{
	*tx = (int)(get_wall_x(rc) * (float)tex->size.x);
	if ((rc->dda->side == 0 && rc->dda->step_x > 0)
		|| (rc->dda->side == 1 && rc->dda->step_y < 0))
		*tx = (int)tex->size.x - *tx - 1;
	if (*tx < 0)
		*tx = 0;
	if ((size_t)(*tx) >= tex->size.x)
		*tx = (int)tex->size.x - 1;
}

static void	draw_textured_line(t_render_col *rc, t_vec2i range, int line_h,
				int wall_top)
{
	t_texture	*tex;
	float		step;
	float		pos;
	int			y;
	int			txy[2];

	tex = get_render_texture(rc);
	set_tx(rc, tex, &txy[0]);
	if (tex->stretch)
		step = (float)tex->size.y / (float)line_h;
	else
		step = (float)tex->size.y * WALL_HEIGHT / (float)line_h;
	pos = ((float)range.x - (float)wall_top) * step;
	y = range.x;
	while (y <= range.y)
	{
		txy[1] = (((int)pos % (int)tex->size.y) + (int)tex->size.y)
			% (int)tex->size.y;
		if (!rc->skip_trans || (tex->data[txy[1] * tex->size.x + txy[0]]
				>> 24) != 0)
			draw_column_pixel(rc, tex, (t_vec3i){txy[0], y, txy[1]});
		pos += step;
		y++;
	}
}

static int	calc_ds_base(t_render_col *rc, float plane_len, int lh)
{
	int	voff;
	int	joff;

	voff = (int)(rc->world->player.render_pitch_offset
			* (float)rc->win->height);
	joff = (int)(rc->world->player.render_pos_z
			* (float)rc->win->height * (0.66f / plane_len)
			/ rc->dda->perp_dist);
	return (rc->win->height / 2 - voff + joff
		- (int)((float)lh * (WALL_HEIGHT - 0.5f) / WALL_HEIGHT));
}

void	draw_column(t_render_col *rc, float plane_len, bool skip_trans)
{
	int		lh;
	int		ds;
	int		dsb;
	t_vec2i	r;

	rc->skip_trans = skip_trans;
	if (rc->dda->perp_dist < 0.0001f)
		rc->dda->perp_dist = 0.0001f;
	lh = (int)((float)rc->win->height * WALL_HEIGHT / rc->dda->perp_dist);
	lh = (int)((float)lh * (0.66f / plane_len));
	dsb = calc_ds_base(rc, plane_len, lh);
	ds = dsb;
	if (rc->dda->tex_idx == TEX_DOOR)
		ds -= (int)(door_open_at(rc->world->map, rc->dda->map_x,
					rc->dda->map_y) * (float)lh);
	r.x = ds;
	if (r.x < dsb)
		r.x = dsb;
	if (r.x < 0)
		r.x = 0;
	r.y = ds + lh;
	if (r.y >= rc->win->height)
		r.y = rc->win->height - 1;
	if (r.x <= r.y)
		draw_textured_line(rc, r, lh, ds);
}
