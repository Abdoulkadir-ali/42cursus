/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entry.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 16:34:35 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 17:48:30 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glb.h"

static void	parse_header(unsigned char *buf, int *json_len, int *bin_len)
{
	*json_len = *(int *)(buf + 12);
	*bin_len = *(int *)(buf + 20 + *json_len);
}

static void	load_glb_meshes_into_scene(t_json_value *json, char *bin,
				t_scene *scene, t_index *mat_ids)
{
	t_json_value	*v[3];
	t_mesh			m;
	size_t			i;
	t_index			midx;

	v[0] = json_get(json, "meshes");
	if (!v[0] || v[0]->type != JSON_ARRAY)
		return ;
	ft_print_debug("GLB: Loading %zu mesh(es)...\n", v[0]->u.array.count);
	i = 0;
	while (i < v[0]->u.array.count)
	{
		ft_print_debug("GLB: Mesh %zu/%zu...\n", i + 1, v[0]->u.array.count);
		ft_memset(&m, 0, sizeof(t_mesh));
		glb_load_mesh(&m, json, bin, (int)i);
		ft_print_debug("GLB: Mesh %zu: %zu verts, %zu indices\n",
			i + 1, m.base_geometry.vertex_count,
			m.base_geometry.index_count);
		v[1] = json_at(json_get(json_at(v[0], i), "primitives"), 0);
		midx = json_get_size_t(v[1], "material");
		if (!midx.error && mat_ids)
			m.mat_id = mat_ids[midx.i].i;
		else
			m.mat_id = scene_add_material(scene, vec3(200, 200, 200)).i;
		if (json_get(json, "skins"))
		{
			ft_print_debug("GLB: Mesh %zu: loading skeleton...\n", i + 1);
			glb_load_skeleton(&m, json, bin, glb_count_extra_anim_nodes(json));
			ft_print_debug("GLB: Mesh %zu: skeleton done (%zu bones)\n",
				i + 1, m.bone_count);
		}
		scene_add_mesh(scene, m);
		ft_print_debug("GLB: Mesh %zu added to scene\n", i + 1);
		i++;
	}
}

/**
 * Main entry point for loading a GLB file into the engine scene.
 * Parses the binary header, extracts JSON and binary chunks, and
 * delegates the mesh and animation loading.
 */
bool	parse_glb(const char *path, t_scene *scene)
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
	free(mat_ids);
	json_free(json);
	free(buf);
	ft_print_debug("GLB: '%s' fully loaded\n", path);
	return (true);
}
