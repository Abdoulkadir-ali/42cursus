/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/08 18:17:10 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fbx.h"
#include "helpers.h"
#include "types.h"

static void	fbx_bin_free_data(t_fbx_bin *fbx)
{
	if (fbx->data.v)
		free(fbx->data.v);
	if (fbx->data.ri)
		free(fbx->data.ri);
	if (fbx->data.vn)
		free(fbx->data.vn);
	if (fbx->data.vu)
		free(fbx->data.vu);
}

static bool	fbx_bin_open(t_fbx_bin *fbx, const char *path)
{
	char	header[64];

	fbx->fd = open(path, O_RDONLY);
	if (fbx->fd < 0)
		return (false);
	if (read(fbx->fd, header, 23) < 23 || read(fbx->fd, &fbx->version, 4) < 4)
	{
		ft_putstr_fd("Error: Failed to read FBX binary header\n", 2);
		close(fbx->fd);
		fbx->fd = -1;
		return (false);
	}
	ft_memset(&fbx->mesh, 0, sizeof(t_skinned_mesh));
	ft_memset(&fbx->data, 0, sizeof(t_fbx_data));
	fbx->mesh.base.name = ft_strdup(path);
	if (!fbx->mesh.base.name)
	{
		close(fbx->fd);
		fbx->fd = -1;
		return (false);
	}
	return (true);
}

static bool	fbx_bin_parse(t_fbx_bin *fbx)
{
	ft_print_debug("DEBUG: starting parse_nodes recursion\n");
	parse_nodes(fbx->fd, -1, fbx->version >= 7500, &fbx->data);
	close(fbx->fd);
	fbx->fd = -1;
	ft_print_debug("DEBUG: parse_nodes finished. counts: vc=%zu nc=%zu\n",
		fbx->data.rv.y, fbx->data.nu.x);
	if (!fbx->data.v || !fbx->data.ri)
	{
		ft_putstr_fd("Error: FBX missing critical data\n", 2);
		return (false);
	}
	if (fbx->data.rv.y > 1000000)
	{
		ft_putstr_fd("Error: FBX mesh too large\n", 2);
		return (false);
	}
	return (true);
}

static void	fbx_dump_mesh(t_fbx_bin *fbx)
{
	const char	*name;

	name = "(null)";
	if (fbx->mesh.base.name)
		name = fbx->mesh.base.name;
	ft_print_debug("FBX Binary: %zu tris built\n", fbx->mesh.base.tri_count);
	ft_print_debug("[MESH_DUMP] name='%s'\n", name);
	ft_print_debug("[MESH_DUMP] vertex_count=%zu  tri_count=%zu\n",
		fbx->mesh.base.vertex_count, fbx->mesh.base.tri_count);
	ft_print_debug("[MESH_DUMP] vertices=%p  triangles=%p  indices=%p\n",
		(void *)fbx->mesh.base.vertices, (void *)fbx->mesh.base.triangles,
		(void *)fbx->mesh.base.indices);
	ft_print_debug("[MESH_DUMP] bbox min=(%.3f,%.3f,%.3f) ",
		fbx->mesh.base.bbox.min.x, fbx->mesh.base.bbox.min.y,
		fbx->mesh.base.bbox.min.z);
	ft_print_debug("max=(%.3f,%.3f,%.3f)\n",
		fbx->mesh.base.bbox.max.x, fbx->mesh.base.bbox.max.y,
		fbx->mesh.base.bbox.max.z);
}

bool	parse_fbx_binary(const char *path, t_skinned_mesh *out)
{
	t_fbx_bin	fbx;

	ft_memset(&fbx, 0, sizeof(fbx));
	fbx.fd = -1;
	if (!fbx_bin_open(&fbx, path))
		return (false);
	if (!fbx_bin_parse(&fbx))
	{
		fbx_bin_free_data(&fbx);
		free(fbx.mesh.base.name);
		return (false);
	}
	if (!fbx_bin_build_mesh(&fbx))
	{
		mesh_free(&fbx.mesh.base);
		return (false);
	}
	fbx_dump_mesh(&fbx);
	*out = fbx.mesh;
	return (true);
}
