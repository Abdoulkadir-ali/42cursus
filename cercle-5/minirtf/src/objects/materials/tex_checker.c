/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 03:20:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 04:58:39 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "material.h"
#include "scene.h"

int	texture_make_checker(t_scene *s, t_vec3 a, t_vec3 b, float scale)
{
	t_texture	*tmp;
	size_t		new_cap;

	if (s->n_textures >= s->cap_textures)
	{
		new_cap = s->cap_textures * 2;
		tmp = (t_texture *)realloc(s->textures,
				sizeof(t_texture) * new_cap);
		if (!tmp)
			return (-1);
		memset(tmp + s->cap_textures, 0,
			sizeof(t_texture) * (new_cap - s->cap_textures));
		s->textures = tmp;
		s->cap_textures = new_cap;
	}
	s->textures[s->n_textures].kind = TEX_CHECKER;
	s->textures[s->n_textures].color_a = a;
	s->textures[s->n_textures].color_b = b;
	s->textures[s->n_textures].scale = scale;
	return ((int)s->n_textures++);
}
