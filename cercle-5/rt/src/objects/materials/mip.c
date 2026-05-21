/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mip.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 03:20:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 05:01:14 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "material.h"

static void	mip_downsample(unsigned char *dst, const unsigned char *src,
				int dw, int dh, int sw)
{
	int	x;
	int	y;
	int	c;
	int	sum;

	y = 0;
	while (y < dh)
	{
		x = 0;
		while (x < dw)
		{
			c = 0;
			while (c < 3)
			{
				sum = src[((y * 2) * sw + (x * 2)) * 3 + c]
					+ src[((y * 2) * sw + (x * 2 + 1)) * 3 + c]
					+ src[((y * 2 + 1) * sw + (x * 2)) * 3 + c]
					+ src[((y * 2 + 1) * sw + (x * 2 + 1)) * 3 + c];
				dst[(y * dw + x) * 3 + c] = (unsigned char)(sum / 4);
				c++;
			}
			x++;
		}
		y++;
	}
}

void	texture_generate_mips(t_texture *t)
{
	unsigned char	*src;
	unsigned char	*dst;
	t_vec2i			src_dim;
	t_vec2i			dst_dim;
	int				lv;

	t->n_mips = 0;
	src_dim = (t_vec2i){t->w, t->h};
	src = t->pixels;
	lv = 0;
	while (lv < 12)
	{
		dst_dim.x = src_dim.x / 2;
		dst_dim.y = src_dim.y / 2;
		if (dst_dim.x < 1) dst_dim.x = 1;
		if (dst_dim.y < 1) dst_dim.y = 1;
		if (dst_dim.x == 1 && dst_dim.y == 1 && src_dim.x == 1 && src_dim.y == 1)
			break ;
		dst = (unsigned char *)malloc((size_t)dst_dim.x * dst_dim.y * 3);
		if (!dst)
			break ;
		mip_downsample(dst, src, dst_dim.x, dst_dim.y, src_dim.x);
		t->mips[lv].w = dst_dim.x;
		t->mips[lv].h = dst_dim.y;
		t->mips[lv].pixels = dst;
		t->n_mips++;
		src = dst;
		src_dim = dst_dim;
		lv++;
	}
}
