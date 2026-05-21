/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/30 00:23:50 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glb.h"
#include "io.h"
#include "material.h"
#include "scene.h"
#include "stb_image.h"

static unsigned char	*to_rgb(unsigned char *src, int w, int h, int n)
{
	unsigned char	*dst;
	int				i;
	int				k;

	if (n == 3)
		return (src);
	dst = (unsigned char *)malloc((size_t)w * h * 3);
	if (!dst)
		return (NULL);
	i = 0;
	while (i < w * h)
	{
		k = i * n;
		if (n == 1)
		{
			dst[i * 3] = src[k];
			dst[i * 3 + 1] = src[k];
			dst[i * 3 + 2] = src[k];
		}
		else if (n == 2)
		{
			dst[i * 3] = src[k];
			dst[i * 3 + 1] = src[k];
			dst[i * 3 + 2] = src[k];
		}
		else
		{
			dst[i * 3] = src[k];
			dst[i * 3 + 1] = src[k + 1];
			dst[i * 3 + 2] = src[k + 2];
		}
		i++;
	}
	return (dst);
}

static int	resolve_image_src(t_glb *g, int img_idx)
{
	const char	*img;
	const char	*v;

	img = json_arr_get(json_obj_find(g->json, g->jend, "images"),
			g->jend, img_idx);
	if (!img)
		return (-1);
	v = json_obj_find(img, g->jend, "bufferView");
	if (!v)
		return (-1);
	return ((int)json_int(v, g->jend));
}

static int	decode_image(t_glb *g, int img_idx, unsigned char **out,
		int *w, int *h)
{
	int				bv_idx;
	int				stride;
	int				n;
	size_t			off;
	size_t			len;
	unsigned char	*dec;
	unsigned char	*rgb;

	bv_idx = resolve_image_src(g, img_idx);
	if (bv_idx < 0 || glb_bv_get(g, bv_idx, &off, &len, &stride) < 0)
		return (-1);
	dec = stbi_load_from_memory(g->bin + off, (int)len, w, h, &n, 0);
	if (!dec)
		return (-1);
	rgb = to_rgb(dec, *w, *h, n);
	if (rgb != dec)
		stbi_image_free(dec);
	if (!rgb)
		return (-1);
	*out = rgb;
	return (0);
}

int	glb_resolve_image(t_glb *g, int img_idx)
{
	unsigned char	*pixels;
	int				w;
	int				h;
	int				tid;

	if (img_idx < 0 || img_idx >= g->n_imgs)
		return (-1);
	if (g->img_tex[img_idx] >= 0 || g->img_tex[img_idx] == -2)
		return (g->img_tex[img_idx] >= 0 ? g->img_tex[img_idx] : -1);
	if (decode_image(g, img_idx, &pixels, &w, &h) < 0)
	{
		g->img_tex[img_idx] = -2;
		return (-1);
	}
	tid = texture_push_image(g->scene, pixels, w, h);
	g->img_tex[img_idx] = tid;
	return (tid);
}
