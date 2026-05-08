/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 22:57:50 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 00:19:47 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

t_vec3	anim_decode_pixel(unsigned int p)
{
	t_vec3	c;

	c.x = (float)((p >> 16) & 0xFF);
	c.y = (float)((p >> 8) & 0xFF);
	c.z = (float)(p & 0xFF);
	return (c);
}

int	anim_is_transparent(unsigned int pix)
{
	return (pix == 0x00000000u || ((pix & 0x00FFFFFFu) == WPIX_TRANS));
}

void	anim_blend_pixel(t_window *win, t_vec2i pos, unsigned int src_pix)
{
	unsigned char	*pixel;
	unsigned int	s[4];
	unsigned int	d[3];
	unsigned int	oner;

	pixel = (unsigned char *)(win->addr + pos.y * win->line_len + pos.x
			* (win->bpp / 8));
	s[3] = (src_pix >> 24) & 0xFFu;
	if (s[3] == 0u)
		return ;
	s[0] = (src_pix >> 16) & 0xFFu;
	s[1] = (src_pix >> 8) & 0xFFu;
	s[2] = src_pix & 0xFFu;
	d[2] = (unsigned int)pixel[0];
	d[1] = (unsigned int)pixel[1];
	d[0] = (unsigned int)pixel[2];
	oner = 255u - s[3];
	pixel[0] = (unsigned char)((s[2] * s[3] + d[2] * oner + 127u) / 255u);
	pixel[1] = (unsigned char)((s[1] * s[3] + d[1] * oner + 127u) / 255u);
	pixel[2] = (unsigned char)((s[0] * s[3] + d[0] * oner + 127u) / 255u);
}

void	anim_write_pixel(t_window *win, t_vec2i pos, unsigned int src_pix)
{
	unsigned int	sa;

	sa = (src_pix >> 24) & 0xFFu;
	if (sa == 255u || sa == 0u)
	{
		put_pixel(win, (t_vec2){(float)pos.x, (float)pos.y},
			anim_decode_pixel(src_pix));
		return ;
	}
	anim_blend_pixel(win, pos, src_pix);
}
