/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/12 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

static void	init_mesh(t_mesh *mesh, const char *path)
{
	ft_memset(mesh, 0, sizeof(t_mesh));
	mesh->name = ft_strdup(path);
}

static void	finalize_mesh(t_scene *scene, t_mesh *mesh, const char *path,
		bool ok)
{
	(void)path;
	if (ok)
	{
		mesh_build_bvh(mesh);
		scene_add_mesh(scene, *mesh);
		ft_print_debug("GLB: Loaded %s with %d triangles\n", path,
			mesh->tri_count);
	}
	else
		mesh_free(mesh);
}

bool	parse_glb(const char *path, t_scene *scene)
{
	int		fd;
	char	*buf[2];
	t_mesh	mesh;
	bool	ok;

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
	init_mesh(&mesh, path);
	ok = glb_load_mesh_data(&mesh, buf[0], buf[1]);
	finalize_mesh(scene, &mesh, path, ok);
	free(buf[0]);
	free(buf[1]);
	return (true);
}
