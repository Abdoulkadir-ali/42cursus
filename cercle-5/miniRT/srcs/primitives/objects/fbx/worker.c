/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   worker.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 04:04:20 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 11:48:48 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fbx.h"
#include "functions/primitives/scene.h"

static bool	fbx_is_binary(const char *path)
{
	int		fd;
	char	header[23];
	ssize_t	ret;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (false);
	ret = read(fd, header, 23);
	close(fd);
	return (ret >= 18 && ft_strncmp(header, "Kaydara FBX Binary", 18) == 0);
}

static bool	fbx_parse_format(const char *path, t_scene *scene,
		t_skinned_mesh *mesh)
{
	if (fbx_is_binary(path))
	{
		ft_print_debug("FBX: Binary format detected\n");
		return (parse_fbx_binary(path, mesh));
	}
	ft_print_debug("FBX: ASCII format detected\n");
	return (parse_fbx_ascii(path, scene, mesh));
}

bool	parse_fbx_worker(const char *path, t_scene *scene)
{
	t_skinned_mesh	mesh;

	ft_print_debug("FBX: loading '%s'\n", path);
	ft_memset(&mesh, 0, sizeof(mesh));
	if (!fbx_parse_format(path, scene, &mesh))
		return (false);
	ft_print_debug("FBX: '%s' loaded (%zu tris)\n",
		path, mesh.base.tri_count);
	return (scene_add_animated(scene, mesh));
}
