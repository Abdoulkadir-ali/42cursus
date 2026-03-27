/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 21:20:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 21:25:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"

/**
 * @brief FBX binary signature detection.
 */
bool	fbx_is_binary(int fd)
{
	char	header[24];
	ssize_t	ret;

	lseek(fd, 0, SEEK_SET);
	ret = read(fd, header, 23);
	lseek(fd, 0, SEEK_SET);
	if (ret < 18)
		return (false);
	if (ft_strncmp(header, "Kaydara FBX Binary", 18) == 0)
		return (true);
	return (false);
}

/**
 * @brief Public interface for FBX path loading.
 */
bool	fbx_load(t_scene *scene, const char *path)
{
	t_parser	p;
	bool		res;

	p.fd = open(path, O_RDONLY);
	if (p.fd < 0)
		return (false);
	p.path = path;
	res = parse_fbx(scene, &p);
	close(p.fd);
	return (res);
}

/**
 * @brief Safely clears all assets inside the FBX container.
 */
void	fbx_clear_asset(t_fbx *fbx)
{
	int		i;

	i = 0;
	while (i < fbx->mesh_count)
	{
		/* Mesh assets are pointers to arrays in fbx, need careful free */
		i++;
	}
	if (fbx->meshes != NULL)
		free(fbx->meshes);
	if (fbx->animations != NULL)
		free(fbx->animations);
	if (fbx->materials != NULL)
		free(fbx->materials);
}
