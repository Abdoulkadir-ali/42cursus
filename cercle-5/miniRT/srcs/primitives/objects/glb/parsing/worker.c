/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   worker.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 16:34:35 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/10 01:52:11 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glb.h"

static void	glb_mesh_worker_mat(t_glb_mesh_task *task, size_t i)
{
	t_json_value	*v[2];
	t_index			midx;

	v[0] = json_get(task->json, "meshes");
	v[1] = json_at(json_get(json_at(v[0], i), "primitives"), 0);
	midx = json_get_size_t(v[1], "material");
	task->meshes[i].mat_id = task->fallback_mat_id;
	if (!midx.error && task->mat_ids)
		task->meshes[i].mat_id = task->mat_ids[midx.i].i;
}

static void	*glb_mesh_worker(void *ptr)
{
	t_glb_mesh_task	*task;
	size_t			i;

	task = (t_glb_mesh_task *)ptr;
	while (1)
	{
		i = __sync_fetch_and_add(&task->next_idx, 1);
		if (i >= task->count)
			break ;
		glb_load_mesh(&task->meshes[i], task->json, task->bin, i);
		glb_mesh_worker_mat(task, i);
		glb_mesh_node_search(task, i);
		glb_finalize_mesh(&task->meshes[i]);
		if (json_get(task->json, "skins"))
			glb_load_skeleton(&task->meshes[i], task->json, task->bin,
				glb_count_extra_anim_nodes(task->json));
	}
	return (NULL);
}

static void	load_glb_meshes_into_scene(t_json_value *json, char *bin,
				t_scene *scene, t_index *mat_ids)
{
	t_glb_mesh_task	task;
	size_t			i;
	t_json_value	*m_json;

	m_json = json_get(json, "meshes");
	if (!m_json || m_json->type != JSON_ARRAY)
		return ;
	ft_memset(&task, 0, sizeof(t_glb_mesh_task));
	task.count = m_json->u.array.count;
	task.meshes = ft_calloc(task.count, sizeof(t_mesh));
	task.json = json;
	task.bin = bin;
	task.mat_ids = mat_ids;
	task.scene = scene;
	task.fallback_mat_id = scene_add_material(scene, vec3(200, 200, 200)).i;
	parallel_run(scene->pool, task.count, glb_mesh_worker, &task);
	i = 0;
	while (i < task.count)
		scene_add_mesh(scene, task.meshes[i++]);
	free(task.meshes);
}

static void	load_glb_resources(t_scene *scene, t_json_value *json, char *bin,
				unsigned char *buf)
{
	t_mesh_resource	res;
	t_index			*m_ids;

	ft_memset(&res, 0, sizeof(t_mesh_resource));
	res.materials = scene->materials;
	res.mat_count = scene->mat_count;
	res.mat_cap = scene->mat_cap;
	m_ids = glb_load_materials(&res, scene->mlx, json, bin);
	scene->materials = res.materials;
	scene->mat_count = res.mat_count;
	scene->mat_cap = res.mat_cap;
	load_glb_meshes_into_scene(json, bin, scene, m_ids);
	glb_load_animations(scene, json, bin);
	init_mesh_anim_defaults(scene);
	free(m_ids);
	json_free(json);
	free(buf);
}

bool	parse_glb_worker(const char *path, t_scene *scene)
{
	size_t			size;
	unsigned char	*buf;
	t_json_value	*json;
	int				len[2];

	buf = glb_read_file(path, &size);
	if (!buf)
		return (false);
	parse_header(buf, &len[0], &len[1]);
	json = json_parse_len((char *)(buf + 20), len[0]);
	if (!json)
		return (free(buf), false);
	load_glb_resources(scene, json, (char *)(buf + 28 + len[0]), buf);
	return (true);
}
