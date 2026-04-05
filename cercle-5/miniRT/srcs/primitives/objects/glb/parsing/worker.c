/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   worker.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 16:34:35 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/05 11:47:24 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glb.h"

static void	parse_header(unsigned char *buf, int *json_len, int *bin_len)
{
	*json_len = *(int *)(buf + 12);
	*bin_len = *(int *)(buf + 20 + *json_len);
}

static void	*glb_mesh_worker(void *ptr)
{
	t_glb_mesh_task	*task;
	size_t			i;
	t_json_value	*v[2];
	t_index			midx;

	task = (t_glb_mesh_task *)ptr;
	while (1)
	{
		i = __sync_fetch_and_add(&task->next_idx, 1);
		if (i >= task->count)
			break ;
		glb_load_mesh(&task->meshes[i], task->json, task->bin, i);
		v[0] = json_get(task->json, "meshes");
		v[1] = json_at(json_get(json_at(v[0], i), "primitives"), 0);
		midx = json_get_size_t(v[1], "material");
		if (!midx.error && task->mat_ids)
		{
			task->meshes[i].mat_id = task->mat_ids[midx.i].i;
			ft_print_debug("GLB Mesh %zu mat_id: %zu\n", i, task->meshes[i].mat_id);
		}
		else
		{
			task->meshes[i].mat_id = (size_t)-1;
			ft_print_debug("GLB Mesh %zu has NO material\n", i);
		}
		
		/* Find node that uses this mesh */
		task->meshes[i].node_idx = (t_index){0, true};
		task->meshes[i].node_transform = mat4_identity();
		t_json_value *nodes = json_get(task->json, "nodes");
		if (nodes && nodes->type == JSON_ARRAY)
		{
			size_t k = 0;
			while (k < nodes->u.array.count)
			{
				t_json_value *node = json_at(nodes, k);
				t_index m_idx_json = json_get_size_t(node, "mesh");
				if (!m_idx_json.error && m_idx_json.i == i)
				{
					task->meshes[i].node_idx = (t_index){k, false};
					task->meshes[i].node_transform = glb_compute_world_transform(task->json, k);
					break;
				}
				k++;
			}
		}
		ft_print_debug("GLB Mesh Worker: i=%zu, sizeof(t_mesh)=%zu\n", i, sizeof(t_mesh));
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
	t_json_value	*v_meshes;

	v_meshes = json_get(json, "meshes");
	if (!v_meshes || v_meshes->type != JSON_ARRAY)
		return ;
	ft_memset(&task, 0, sizeof(t_glb_mesh_task));
	task.count = v_meshes->u.array.count;
	task.meshes = ft_calloc(task.count, sizeof(t_mesh));
	task.json = json;
	task.bin = bin;
	task.mat_ids = mat_ids;
	task.scene = scene;
	parallel_run(scene->pool, task.count, glb_mesh_worker, &task);
	i = 0;
	while (i < task.count)
	{
		if (task.meshes[i].mat_id == (size_t)-1)
			task.meshes[i].mat_id = scene_add_material(scene, vec3(200, 200, 200)).i;
		scene_add_mesh(scene, task.meshes[i++]);
	}
	free(task.meshes);
}


/**
 * Main entry point for loading a GLB file into the engine scene.
 * Parses the binary header, extracts JSON and binary chunks, and
 * delegates the mesh and animation loading.
 */
static void	init_mesh_anim_defaults(t_scene *scene)
{
	size_t		i;
	t_mesh		*m;
	t_mesh_anim	defaults;

	defaults.clip_idx = (scene->clip_count > 0) ? 0 : -1;
	defaults.time = 0.0;
	defaults.speed = 1.0;
	defaults.looping = true;
	defaults.paused = false;
	ft_print_debug("[ANIM] init_mesh_anim_defaults: %zu meshes, %zu clips\n",
		scene->mesh_count, scene->clip_count);
	i = 0;
	while (i < scene->mesh_count)
	{
		m = &scene->meshes[i];
		if (m->skeleton && m->bone_count > 0)
		{
			m->anim = defaults;
			ft_print_debug(
				"[ANIM]   mesh[%zu] '%s': skinned, clip_idx=%d looping=%d\n",
				i, m->name ? m->name : "?",
				m->anim.clip_idx, m->anim.looping);
		}
		else
		{
			ft_memset(&m->anim, 0, sizeof(t_mesh_anim));
			ft_print_debug("[ANIM]   mesh[%zu] '%s': no skeleton\n",
				i, m->name ? m->name : "?");
		}
		i++;
	}
}

bool	parse_glb_worker(const char *path, t_scene *scene)
{
	size_t			size;
	unsigned char	*buf;
	t_json_value	*json;
	int				len[2];
	char			*bin;
	t_index			*mat_ids;
	t_mesh_resource	res;

	ft_print_debug("GLB: Reading file '%s'\n", path);
	buf = glb_read_file(path, &size);
	if (!buf)
		return (false);
	ft_print_debug("GLB: File loaded (%zu bytes)\n", size);
	parse_header(buf, &len[0], &len[1]);
	ft_print_debug("GLB: Parsing JSON chunk (%d bytes)...\n", len[0]);
	json = json_parse_len((char *)(buf + 20), len[0]);
	if (!json)
		return (free(buf), false);
	ft_print_debug("GLB: JSON parsed, binary chunk = %d bytes\n", len[1]);
	bin = (char *)(buf + 28 + len[0]);
	ft_memset(&res, 0, sizeof(t_mesh_resource));
	res.materials = scene->materials;
	res.mat_count = scene->mat_count;
	res.mat_cap = scene->mat_cap;
	ft_print_debug("GLB: Loading materials...\n");
	mat_ids = glb_load_materials(&res, scene->mlx, json, bin);
	scene->materials = res.materials;
	scene->mat_count = res.mat_count;
	scene->mat_cap = res.mat_cap;
	ft_print_debug("GLB: Materials loaded (%zu total in scene)\n",
		scene->mat_count);
	load_glb_meshes_into_scene(json, bin, scene, mat_ids);
	ft_print_debug("GLB: Loading animations...\n");
	glb_load_animations(scene, json, bin);
	ft_print_debug("GLB: Animations loaded (%zu clips in scene)\n",
		scene->clip_count);
	init_mesh_anim_defaults(scene);
	free(mat_ids);
	json_free(json);
	free(buf);
	ft_print_debug("GLB: parse_glb_worker: sizeof(t_mesh)=%zu\n", sizeof(t_mesh));
	ft_print_debug("GLB: '%s' fully loaded\n", path);
	return (true);
}
