/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 19:14:18 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/29 09:18:33 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "debug.h"

static void	free_primitive_p_meta(t_scene *s)
{
	size_t	i;

	if (!s->prim_meta)
		return ;
	i = 0;
	while (i < s->primitives.count)
	{
		free(s->prim_meta[i].name);
		free(s->prim_meta[i].file_path);
		free(s->prim_meta[i].user_comment);
		i++;
	}
	free(s->prim_meta);
}

static void	destroy_geometry(t_scene *s)
{
	int	i;

	free(s->primitives.types);
	free(s->primitives.mat_ids);
	free(s->primitives.is_static);
	free(s->primitives.has_phys);
	free(s->primitives.phys_idx);
	free(s->primitives.float_slab);
	free(s->tri_soa.mat_ids);
	free(s->tri_soa.float_slab);
	free(s->plane_indices);
	if (s->animated)
	{
		i = 0;
		while (i < (int)s->anim_count)
		{
			i++;
		}
		free(s->animated);
	}
}

static void	destroy_metadata(t_scene *s)
{
	free_primitive_p_meta(s);
	free(s->mesh_asset_meta);
	free(s->mesh_instance_meta);
	free(s->mat_meta);
}

void	destroy_scene(t_scene *s)
{
	if (!s)
		return ;
	DBG_INFO_MSG(DBG_CH_PARSER, "destroy_scene: '%s' prims=%zu tris=%zu mats=%zu\n", s->name ? s->name : "?", s->primitives.count, s->tri_soa.count, s->mat_count);
	free(s->name);
	destroy_geometry(s);
	destroy_metadata(s);
	free(s->materials);
	free(s->lights);
	free(s->clips);
	free(s->emissive_cache);
	free(s);
}
