/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bake_bmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/12 01:25:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "optimizations.h"
#include <stdio.h>

static void	bmp_le32(unsigned char *b, unsigned int v)
{
	b[0] = (unsigned char)(v);
	b[1] = (unsigned char)(v >> 8);
	b[2] = (unsigned char)(v >> 16);
	b[3] = (unsigned char)(v >> 24);
}

static void	bmp_fill_hdr(unsigned char hdr[BMP_HEADER_SIZE], t_vec2i size)
{
	unsigned int	row_sz;
	unsigned int	pxsz;

	row_sz = (unsigned int)((size.x * BMP_RGB + 3) & ~3);
	pxsz = row_sz * (unsigned int)size.y;
	ft_memset(hdr, 0, BMP_HEADER_SIZE);
	hdr[0] = 'B';
	hdr[1] = 'M';
	bmp_le32(hdr + 2, BMP_HEADER_SIZE + pxsz);
	bmp_le32(hdr + 10, BMP_HEADER_SIZE);
	bmp_le32(hdr + 14, BMP_INFO_HDR_SIZE);
	bmp_le32(hdr + 18, (unsigned int)size.x);
	bmp_le32(hdr + 22, (unsigned int)(-size.y));
	hdr[26] = BMP_PLANES;
	hdr[28] = BMP_BPP;
	bmp_le32(hdr + 34, pxsz);
}

static void	bmp_write_row(FILE *f, t_bake_job *job, int y, unsigned char *row)
{
	size_t	i;
	t_vec2i	p;
	size_t	fr;

	p.y = y;
	p.x = 0;
	fr = job->frame;
	while (p.x < job->width)
	{
		i = (size_t)p.y * (size_t)job->width + (size_t)p.x;
		if (fr > 0)
		{
			row[p.x * BMP_RGB + 0] = (unsigned char)(job->accum_b[i] / fr);
			row[p.x * BMP_RGB + 1] = (unsigned char)(job->accum_g[i] / fr);
			row[p.x * BMP_RGB + 2] = (unsigned char)(job->accum_r[i] / fr);
		}
		p.x++;
	}
	fwrite(row, 1, (size_t)((job->width * BMP_RGB + 3) & ~3), f);
}

void	bake_save(t_bake_job *job)
{
	FILE			*f;
	unsigned char	hdr[BMP_HEADER_SIZE];
	unsigned char	*row;
	int				y;

	f = fopen(job->out_path, "wb");
	if (!f)
		return ;
	bmp_fill_hdr(hdr, vec2i(job->width, job->height));
	fwrite(hdr, 1, BMP_HEADER_SIZE, f);
	row = ft_calloc((size_t)((job->width * BMP_RGB + 3) & ~3), 1);
	if (row)
	{
		y = 0;
		while (y < job->height)
			bmp_write_row(f, job, y++, row);
		free(row);
	}
	fclose(f);
}
