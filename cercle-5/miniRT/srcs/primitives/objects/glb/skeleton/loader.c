/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 16:21:45 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/09 03:10:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glb.h"

static void	load_skeleton_data(t_mesh *mesh, t_json_value *js[2])
{
	size_t	*node_map;
	size_t	i;

	node_map = malloc(sizeof(*node_map) * PARSER_BUF_SIZE);
	i = 0;
	while (i < PARSER_BUF_SIZE)
	{
		node_map[i] = 0;
		i++;
	}
	init_bone_data(mesh, js[0], js[1], node_map);
	link_glb_parents(mesh, js[0], js[1], node_map);
	free(node_map);
}

void	glb_load_skeleton(t_mesh *mesh, t_json_value *json, char *bin,
			size_t extra_count)
{
	t_json_value	*skin;
	t_json_value	*js[2];
	t_mat4			*ibms;
	t_index			idx;

	skin = json_at(json_get(json, "skins"), 0);
	js[0] = json_get(skin, "joints");
	js[1] = json_get(json, "nodes");
	if (!skin || !js[0] || !js[1])
		return ;
	setup_skeleton(mesh, js[0]->u.array.count, extra_count);
	ibms = malloc(sizeof(t_mat4) * mesh->bone_count);
	if (!ibms)
		return ;
	idx = json_get_size_t(skin, "inverseBindMatrices");
	load_ibms(json, bin, idx.i, ibms);
	load_skeleton_data(mesh, js);
	set_ibms(mesh, ibms);
	free(ibms);
}
