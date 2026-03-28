/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 22:15:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"

/**
 * @brief Matches ASCII nodes and extracts raw vertex/index data.
 */
static bool	p_mesh_ascii(t_fbx *f, char *buf, size_t sz)
{
	char	*p;

	p = fbx_find_node(buf, buf + sz, "Vertices:");
	if (p == NULL)
		return (false);
	f->v = (float *)fbx_parse_array_ascii(&p, &f->vc, 8);
	p = fbx_find_node(buf, buf + sz, "PolygonVertexIndex:");
	if (p == NULL)
		return (false);
	f->ri = (int *)fbx_parse_array_ascii(&p, &f->rc, 4);
	return (f->v != NULL && f->ri != NULL);
}

/**
 * @brief Core FBX ASCII parsing pipeline.
 */
bool	fbx_parse_ascii(t_fbx *fbx)
{
	char	*buf;
	size_t	sz;

	buf = fbx_read_file(fbx->path, &sz);
	if (buf == NULL)
		return (false);
	if (p_mesh_ascii(fbx, buf, sz) == false)
	{
		free(buf);
		return (false);
	}
	/* Build the mesh using common build logic */
	if (fbx_build_mesh(fbx) == false)
	{
		free(buf);
		return (false);
	}
	free(buf);
	return (true);
}
