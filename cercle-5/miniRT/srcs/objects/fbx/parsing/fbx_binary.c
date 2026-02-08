/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fbx_binary.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 04:20:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/08 04:20:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "objects/fbx.h"
#include "scene.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* FBX Binary uses a node-based structure with offsets.
   This implementation follows the Layout for 7.x files. */

typedef struct s_fbx_bin_node
{
	uint64_t	end_offset;
	uint64_t	num_properties;
	uint64_t	property_list_len;
	uint8_t		name_len;
	char		name[255];
}				t_fbx_bin_node;

static void	read_node_header(int fd, t_fbx_bin_node *node, bool is_64bit)
{
		uint32_t tmp;

	if (is_64bit)
	{
		if (read(fd, &node->end_offset, 8) < 8)
			return ;
		if (read(fd, &node->num_properties, 8) < 8)
			return ;
		if (read(fd, &node->property_list_len, 8) < 8)
			return ;
	}
	else
	{
		if (read(fd, &tmp, 4) < 4)
			return ;
		node->end_offset = tmp;
		if (read(fd, &tmp, 4) < 4)
			return ;
		node->num_properties = tmp;
		if (read(fd, &tmp, 4) < 4)
			return ;
		node->property_list_len = tmp;
	}
	if (read(fd, &node->name_len, 1) < 1)
		return ;
	ft_memset(node->name, 0, 255);
	if (read(fd, node->name, node->name_len) < node->name_len)
		return ;
}

bool	parse_fbx_binary(const char *path, t_scene *scene)
{
	int				fd;
	char			header[23];
	uint32_t		version;
	bool			is_64bit;
	t_skinned_mesh	mesh;
		t_fbx_bin_node node;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (false);
	if (read(fd, header, 23) < 23)
	{
		close(fd);
		return (false);
	}
	if (read(fd, &version, 4) < 4)
	{
		close(fd);
		return (false);
	}
	is_64bit = (version >= 7500);
	printf("FBX Binary: Version %u, 64-bit offsets: %s\n", version, is_64bit ? "YES" : "NO");
	ft_memset(&mesh, 0, sizeof(t_skinned_mesh));
	mesh.base.name = ft_strdup(path);
	/* Root level traversal */
	while (1)
	{
		read_node_header(fd, &node, is_64bit);
		if (node.end_offset == 0)
			break ; // Sentinel Null Node
		if (ft_strcmp(node.name, "Objects") == 0)
		{
			// Descend into objects to find Geometry
			// In a full implementation, this involves recursive node reading.
			printf("FBX Binary: Found Objects node at offset %lu. Name: %s\n", node.end_offset, node.name);
		}
		lseek(fd, node.end_offset, SEEK_SET);
	}
	close(fd);
	// Inject a placeholder for now
	if (!scene_add_animated(scene, mesh))
		return (false);
	return (true);
}
