/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 10:16:43 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fbx.h"
#include "helpers.h"
#include "types.h"
#include "functions/primitives/scene.h"

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
		fprintf(stderr, "Error: Failed to read FBX binary header\n");
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
		fbx->data.vc, fbx->data.nc);
	if (!fbx->data.v || !fbx->data.ri)
	{
		fprintf(stderr, "Error: FBX missing critical data\n");
		return (false);
	}
	if (fbx->data.vc > 1000000)
	{
		fprintf(stderr, "Error: FBX mesh too large (%zu vertices, limit 1M)\n",
			fbx->data.vc);
		return (false);
	}
	return (true);
}

bool	parse_fbx_binary(const char *path, t_scene *scene)
{
	t_fbx_bin	fbx;

	ft_print_debug("DEBUG: parse_fbx_binary starting for %s\n", path);
	ft_memset(&fbx, 0, sizeof(fbx));
	fbx.fd = -1;
	if (!fbx_bin_open(&fbx, path))
		return (false);
	ft_print_debug("DEBUG: FBX Binary Version: %zu\n", fbx.version);
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
	ft_print_debug("FBX Binary Loaded: %s (%zu tris)\n", path,
		fbx.mesh.base.tri_count);
	return (scene_add_animated(scene, fbx.mesh));
}
