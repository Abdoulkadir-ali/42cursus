/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/05 00:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "animations.h"

char	*animation_mesh_name(t_mesh *m)
{
	if (m->name)
		return (m->name);
	return ("?");
}

static size_t	count_skinned(t_scene *sc)
{
	size_t	i;
	size_t	n;

	n = 0;
	i = 0;
	while (i < sc->mesh_count)
	{
		if (sc->meshes[i].skeleton && sc->meshes[i].bone_count > 0)
			n++;
		i++;
	}
	return (n);
}

static void	fill_indices(t_anim_engine *eng, t_scene *sc)
{
	size_t	i;
	size_t	n;

	n = 0;
	i = 0;
	while (i < sc->mesh_count)
	{
		if (sc->meshes[i].skeleton && sc->meshes[i].bone_count > 0)
		{
			eng->mesh_indices[n] = i;
			ft_print_debug("[ANIM]   indexed mesh[%zu] '%s' bones=%zu\n",
				i, animation_mesh_name(&sc->meshes[i]),
				sc->meshes[i].bone_count);
			n++;
		}
		i++;
	}
}

void	anim_engine_rebuild_index(t_anim_engine *eng, t_scene *sc)
{
	size_t	n;

	free(eng->mesh_indices);
	eng->mesh_indices = NULL;
	eng->mesh_count = 0;
	if (!sc)
		return ;
	n = count_skinned(sc);
	ft_print_debug("[ANIM] rebuild_index: %zu/%zu skinned\n", n,
		sc->mesh_count);
	if (n == 0)
		return ;
	eng->mesh_indices = malloc(sizeof(size_t) * n);
	if (!eng->mesh_indices)
		return ;
	eng->mesh_count = n;
	fill_indices(eng, sc);
}
