/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   worker_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 00:52:15 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/09 00:52:15 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glb.h"

void	glb_mesh_node_search(t_glb_mesh_task *task, size_t i)
{
	t_json_value	*nodes;
	t_json_value	*node;
	t_index			m_idx_json;
	size_t			k;

	task->meshes[i].node_idx = init_index(0, true);
	task->meshes[i].node_transform = mat4_identity();
	nodes = json_get(task->json, "nodes");
	if (!nodes || nodes->type != JSON_ARRAY)
		return ;
	k = 0;
	while (k < nodes->u.array.count)
	{
		node = json_at(nodes, k);
		m_idx_json = json_get_size_t(node, "mesh");
		if (!m_idx_json.error && m_idx_json.i == i)
		{
			task->meshes[i].node_idx = init_index(k, false);
			task->meshes[i].node_transform = glb_compute_world_transform(
					task->json, k);
			break ;
		}
		k++;
	}
}

void	init_mesh_anim_defaults(t_scene *scene)
{
	size_t		i;
	t_mesh		*m;
	t_mesh_anim	defaults;

	defaults.idx = init_index(0, scene->clip_count == 0);
	defaults.time = 0.0;
	defaults.speed = 1.0;
	defaults.looping = true;
	defaults.paused = false;
	i = 0;
	while (i < scene->mesh_count)
	{
		m = &scene->meshes[i];
		if (m->skeleton && m->bone_count > 0)
			m->anim = defaults;
		else
			ft_memset(&m->anim, 0, sizeof(t_mesh_anim));
		i++;
	}
}

void	parse_header(unsigned char *buf, int *json_len, int *bin_len)
{
	*json_len = *(int *)(buf + 12);
	*bin_len = *(int *)(buf + 20 + *json_len);
}
