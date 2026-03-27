/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 22:05:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"

/**
 * @brief Reads and validates FBX format version.
 */
static bool	v_read(t_fbx *f)
{
	char	h[32];

	lseek(f->fd, 0, SEEK_SET);
	if (read(f->fd, h, 23) < 23)
		return (false);
	if (read(f->fd, &f->version, 4) < 4)
		return (false);
	f->is_64 = false;
	if (f->version >= 7500)
		f->is_64 = true;
	return (true);
}

/**
 * @brief Core FBX binary parsing pipeline.
 */
bool	fbx_parse_binary(t_fbx *fbx)
{
	if (v_read(fbx) == false)
		return (false);
	/* Root nodes parse without end offset limit */
	fbx_parse_nodes(fbx, (uint64_t)-1);
	if (fbx_build_mesh(fbx) == false)
		return (false);
	return (true);
}
