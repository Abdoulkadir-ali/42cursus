/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 01:24:30 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 04:50:24 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "scene.h"

int	ensure_default_texture(t_scene *s)
{
	if (s->n_textures > 0)
		return (0);
	return (texture_make_checker(s, v3(0.85f, 0.85f, 0.85f), v3(0.15f, 0.15f,
				0.15f), 4.0f));
}
