/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex_image.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 03:20:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 04:59:50 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "material.h"
#include "scene.h"

int	texture_push_image(t_scene *s, unsigned char *pixels, int w, int h)
{
	t_texture	*tmp;
	size_t		new_cap;
	int			idx;

	if (!pixels || w <= 0 || h <= 0)
		return (-1);
	if (s->n_textures >= s->cap_textures)
	{
		new_cap = 8;
		if (s->cap_textures)
			new_cap = s->cap_textures * 2;
		tmp = (t_texture *)realloc(s->textures,
				sizeof(t_texture) * new_cap);
		if (!tmp)
			return (free(pixels), -1);
		memset(tmp + s->cap_textures, 0,
			sizeof(t_texture) * (new_cap - s->cap_textures));
		s->textures = tmp;
		s->cap_textures = new_cap;
	}
	idx = (int)s->n_textures++;
	s->textures[idx].kind = TEX_IMAGE;
	s->textures[idx].w = w;
	s->textures[idx].h = h;
	s->textures[idx].pixels = pixels;
	texture_generate_mips(&s->textures[idx]);
	return (idx);
}
