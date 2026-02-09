/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fbx_binary.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 04:20:00 by abdoali           #+#    #+#             */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

static ssize_t	safe_read(int fd, void *buf, size_t count)
{
	return (read(fd, buf, count));
}

static void	read_offsets(int fd, t_fbx_bin_node *node, bool is_64bit)
{
	uint32_t	tmp;

	if (is_64bit)
	{
		safe_read(fd, &node->end_offset, 8);
		safe_read(fd, &node->num_properties, 8);
		safe_read(fd, &node->property_list_len, 8);
	}
	else
	{
		safe_read(fd, &tmp, 4);
		node->end_offset = tmp;
		safe_read(fd, &tmp, 4);
		node->num_properties = tmp;
		safe_read(fd, &tmp, 4);
		node->property_list_len = tmp;
	}
}

static void	read_node_header(int fd, t_fbx_bin_node *node, bool is_64bit)
{
	read_offsets(fd, node, is_64bit);
	if (safe_read(fd, &node->name_len, 1) < 1)
	{
		node->end_offset = 0;
		return ;
	}
	ft_memset(node->name, 0, 255);
	if (node->name_len > 0)
		safe_read(fd, node->name, node->name_len);
}

bool	parse_fbx_binary(const char *path, t_scene *scene)
{
	int				fd;
	char			header[23];
	uint32_t		version;
	t_skinned_mesh	mesh;
	t_fbx_bin_node	node;

	if ((fd = open(path, O_RDONLY)) < 0)
		return (false);
	if (read(fd, header, 23) < 23 || read(fd, &version, 4) < 4)
		return (close(fd), false);
	ft_memset(&mesh, 0, sizeof(t_skinned_mesh));
	mesh.base.name = ft_strdup(path);
	while (1)
	{
		read_node_header(fd, &node, version >= 7500);
		if (node.end_offset == 0)
			break ;
		lseek(fd, node.end_offset, SEEK_SET);
	}
	close(fd);
	printf("FBX Binary: Parsed %s (No Geometry yet)\n", path);
	/* Do NOT add to scene if we have no geometry to avoid crashes/empty nodes */
	if (mesh.base.tri_count == 0)
	{
		free(mesh.base.name);
		return (false);
	}
	mesh_build_bvh(&mesh.base);
	return (scene_add_animated(scene, mesh));
}
