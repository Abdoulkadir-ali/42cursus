#include "objects.h"
#include <stdio.h>
#include <stdarg.h>

static void	glb_log(const char *fmt, ...)
{
	va_list	args;
	FILE	*f;

	f = fopen("debug_glb.txt", "a");
	if (f)
	{
		va_start(args, fmt);
		vfprintf(f, fmt, args);
		va_end(args);
		fclose(f);
	}
	va_start(args, fmt);
	vfprintf(stderr, fmt, args);
	va_end(args);
}

static void	init_mesh(t_mesh *mesh, const char *path)
{
	ft_memset(mesh, 0, sizeof(t_mesh));
	mesh->name = ft_strdup(path);
}

static void	finalize_mesh(t_scene *scene, t_mesh *mesh, const char *path)
{
	int		i;
	double	tmp;

	(void)path;
	
	/* Automatic Z-up to Y-up Conversion (+90 deg pitch) */
	i = 0;
	while (i < mesh->vertex_count)
	{
		tmp = mesh->vertices[i].y;
		mesh->vertices[i].y = -mesh->vertices[i].z;
		mesh->vertices[i].z = tmp;
		if (mesh->normals)
		{
			tmp = mesh->normals[i].y;
			mesh->normals[i].y = -mesh->normals[i].z;
			mesh->normals[i].z = tmp;
		}
		i++;
	}

	if (mesh->skin_data && mesh->vertex_count > 0)
	{
		mesh->base_vertices = malloc(sizeof(t_vec3) * mesh->vertex_count);
		mesh->base_normals = malloc(sizeof(t_vec3) * mesh->vertex_count);
		if (mesh->base_vertices && mesh->vertices)
			ft_memcpy(mesh->base_vertices, mesh->vertices,
				sizeof(t_vec3) * mesh->vertex_count);
		if (mesh->base_normals && mesh->normals)
			ft_memcpy(mesh->base_normals, mesh->normals,
				sizeof(t_vec3) * mesh->vertex_count);
	}
	mesh_build_bvh(mesh);
	scene_add_mesh(scene, *mesh);
}

static void	process_glb_meshes(t_scene *scene, t_json_value *json, char *bin,
		const char *path)
{
	t_json_value	*meshes;
	t_json_value	*mesh_json;
	t_json_value	*prims;
	t_json_value	*prim_json;
	int				i;
	int				j;
	int				*mat_ids;
	int				mat_idx;
	t_mesh			mesh;

	void glb_inspect_animations(t_json_value *json);
	void glb_inspect_skins(t_json_value *json);
	void glb_inspect_nodes(t_json_value *json);

	glb_inspect_animations(json);
	glb_inspect_skins(json);
	glb_inspect_nodes(json);
	
	mat_ids = glb_load_materials(scene, json, bin);
	meshes = json_get(json, "meshes");
	if (!meshes || meshes->type != JSON_ARRAY)
	{
		free(mat_ids);
		return ;
	}
	i = -1;
	while (++i < (int)meshes->u.array.count)
	{
		mesh_json = json_at(meshes, i);
		prims = json_get(mesh_json, "primitives");
		if (!prims || prims->type != JSON_ARRAY)
			continue ;
		j = -1;
		while (++j < (int)prims->u.array.count)
		{
			prim_json = json_at(prims, j);
			mat_idx = json_get_int(prim_json, "material");
			init_mesh(&mesh, path);
			if (glb_load_primitive(&mesh, json, bin, i, j,
					(mat_ids && mat_idx >= 0) ? mat_ids[mat_idx] : 0))
			{
				void glb_load_skeleton(t_mesh *mesh, t_json_value *json, char *bin);
				glb_load_skeleton(&mesh, json, bin);
				finalize_mesh(scene, &mesh, path);
			}
			else
				mesh_free(&mesh);
		}
	}
	free(mat_ids);
}

bool	parse_glb(const char *path, t_scene *scene)
{
	int				fd;
	char			*buf[2];
	t_json_value	*json;

	glb_log("GLB: --- Entering parse_glb for %s ---\n", path);
	buf[0] = NULL;
	buf[1] = NULL;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (false);
	if (!glb_read_buffers(fd, buf))
	{
		close(fd);
		return (false);
	}
	close(fd);
	json = json_parse(buf[0]);
	if (!json)
	{
		glb_log("GLB: JSON PARSE FAILED for %s\n", path);
		glb_log("GLB: JSON Start: %.100s\n", buf[0]);
		free(buf[0]);
		free(buf[1]);
		return (false);
	}
	glb_log("GLB: JSON parsed successfully, first 100 chars: %.100s\n", buf[0]);
	process_glb_meshes(scene, json, buf[1], path);
	glb_load_animations(scene, json, buf[1]);
	json_free(json);
	free(buf[0]);
	free(buf[1]);
	return (true);
}
