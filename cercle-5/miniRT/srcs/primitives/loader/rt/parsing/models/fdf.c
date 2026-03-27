/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 23:58:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 00:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"

/**
 * @brief Parses an 'fdf' entry from the scene file.
 * Syntax: fdf [path] [pos] [rot] [scale] [color] [emissive]
 */
bool	parse_fdf_entry(t_scene *scene, t_parser *p)
{
	t_fdf		fdf;
	char		path[1024];
	t_vec3		over[4]; /* 0: pos, 1: rot, 2: albedo, 3: emissive */
	double		s;
	t_parser	fp;

	if (!parser_get_next_word(p, path, 1024))
		return (false);
	parse_vec3(p, &over[0]);
	parse_vec3(p, &over[1]);
	s = parse_double(p);
	parse_vec3(p, &over[2]);
	parse_vec3(p, &over[3]);
	fp.fd = open(path, O_RDONLY);
	if (fp.fd < 0 || !fdf_parse_grid_single_pass(&fdf, &fp))
		return (false);
	close(fp.fd);
	fdf.mesh.transform.pos = vec3_add(fdf.mesh.transform.pos, over[0]);
	fdf.mesh.transform.rot = vec3_add(fdf.mesh.transform.rot, over[1]);
	fdf.mesh.transform.scale = vec3_mul_scalar(fdf.mesh.transform.scale, s);
	scene_add_mesh(scene, fdf.mesh);
	return (true);
}
