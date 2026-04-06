/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 16:15:48 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fbx.h"

static bool	ascii_parse_mesh(t_fbx_ascii *asc)
{
	char	*temp;

	temp = find_node(asc->p, asc->end, "Vertices:");
	if (!temp)
		return (false);
	temp = advance_to_data(temp, asc->end);
	asc->mesh.base.vertices = parse_array(&temp, &asc->rv.y, sizeof(t_vec3),
			f_vec3);
	if (!asc->mesh.base.vertices)
		return (false);
	temp = find_node(asc->p, asc->end, "PolygonVertexIndex:");
	if (!temp)
		return (false);
	temp = advance_to_data(temp, asc->end);
	asc->ri = parse_array(&temp, &asc->rv.x, sizeof(int), f_int);
	if (!asc->ri)
		return (false);
	ascii_load_normals(asc);
	ascii_load_uvs(asc);
	return (true);
}

static bool	ascii_build_mesh(t_fbx_ascii *asc, t_scene *scene,
		const char *path)
{
	t_fbx_flat_params	p;

	p.raw = asc->ri;
	p.rv.x = asc->rv.x;
	p.n = asc->rn;
	p.nu.x = asc->nu.x;
	p.u = asc->ru;
	p.nu.y = asc->nu.y;
	p.rv.y = asc->rv.y;
	fbx_build_flat(&asc->mesh.base, &p);
	if (asc->mesh.base.tri_count == 0)
		return (false);
	mesh_build_bvh(&asc->mesh.base);
	asc->mat_id = parse_texture(asc->p, asc->end, scene, path);
	if (!asc->mat_id.error)
		asc->mesh.base.mat_id = asc->mat_id.i;
	return (true);
}

static bool	parse_fbx_ascii_internal(t_fbx_ascii *asc, t_scene *scene,
		const char *path)
{
	if (!ascii_parse_mesh(asc))
		return (false);
	if (!ascii_build_mesh(asc, scene, path))
		return (false);
	ft_print_debug("FBX ASCII: %zu tris built\n",
		asc->mesh.base.tri_count);
	return (true);
}

static bool	setup(t_fbx_ascii *asc, const char *path)
{
	size_t	size;

	ft_memset(asc, 0, sizeof(*asc));
	asc->path = path;
	asc->buf = read_file_content(path, &size);
	if (!asc->buf)
		return (false);
	asc->p = asc->buf;
	asc->end = asc->buf + size;
	ft_memset(&asc->mesh, 0, sizeof(t_skinned_mesh));
	asc->mesh.base.name = ft_strdup(path);
	if (!asc->mesh.base.name)
	{
		free(asc->buf);
		return (false);
	}
	return (true);
}

bool	parse_fbx_ascii(const char *path, t_scene *scene, t_skinned_mesh *out)
{
	t_fbx_ascii	asc;

	ft_print_debug("FBX ASCII: parsing '%s'\n", path);
	if (!setup(&asc, path))
		return (false);
	if (!parse_fbx_ascii_internal(&asc, scene, path))
	{
		mesh_free(&asc.mesh.base);
		free(asc.buf);
		return (false);
	}
	free(asc.buf);
	*out = asc.mesh;
	return (true);
}
