/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 03:20:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 04:51:59 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "skeletal.h"

void	scene_free(t_scene *s)
{
	size_t	i;
	int		m;

	i = 0;
	while (i < s->n_textures)
	{
		m = 0;
		while (m < s->textures[i].n_mips)
			free(s->textures[i].mips[m++].pixels);
		free(s->textures[i++].pixels);
	}
	free(s->textures);
	free(s->lights);
	free(s->bvh_objs);
	free(s->planes);
	free(s->bhs);
	free(s->emit_idx);
	if (s->animator)
		skel_animator_destroy((t_animator *)s->animator);
	memset(s, 0, sizeof(*s));
}
