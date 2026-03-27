/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 23:40:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 23:55:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"

/**
 * @brief Overrides material properties for high-fidelity scene injection.
 */
static void	override_mats(t_glb *glb, t_vec3 color, t_vec3 emissive)
{
	int	i;

	i = 0;
	while (i < glb->mat_count)
	{
		if (vec3_mag_sq(color) > SCALE_EPSILON)
			glb->materials[i].albedo = vec3_div_scalar(color, 255.0);
		if (vec3_mag_sq(emissive) > SCALE_EPSILON)
		{
			glb->materials[i].emissive = vec3_div_scalar(emissive, 255.0);
			glb->materials[i].is_emissive = true;
		}
		i++;
	}
}

/**
 * @brief Final injection loop for GLB assets with spatial overrides.
 */
static void	inject_glb(t_scene *s, t_glb *g, t_vec3 p[2], double scale)
{
	int	i;
	int	*mmap;

	mmap = malloc(sizeof(int) * g->mat_count);
	i = -1;
	while (++i < g->mat_count)
		mmap[i] = scene_add_material(s, g->materials[i]);
	i = 0;
	while (i < g->mesh_count)
	{
		if (g->mesh_mats != NULL && g->mesh_mats[i] < g->mat_count)
			g->meshes[i].mat_id = mmap[g->mesh_mats[i]];
		g->meshes[i].transform.pos = vec3_add(g->meshes[i].transform.pos, p[0]);
		g->meshes[i].transform.rot = vec3_add(g->meshes[i].transform.rot, p[1]);
		g->meshes[i].transform.scale = vec3_mul_scalar(g->meshes[i].transform.scale, scale);
		scene_add_mesh(s, g->meshes[i]);
		i++;
	}
	free(mmap);
}

/**
 * @brief Parses a 'glb' entry from the scene file.
 * Syntax: glb [path] [pos] [rot] [scale] [color] [emissive]
 */
bool	parse_glb_entry(t_scene *scene, t_parser *p)
{
	t_glb		glb;
	char		path[1024];
	t_vec3		over[4]; /* 0: pos, 1: rot, 2: albedo, 3: emissive */
	double		s;
	int			fd;

	if (!parser_get_next_word(p, path, 1024))
		return (false);
	parse_vec3(p, &over[0]);
	parse_vec3(p, &over[1]);
	s = parse_double(p);
	parse_vec3(p, &over[2]);
	parse_vec3(p, &over[3]);
	fd = open(path, O_RDONLY);
	if (fd < 0 || !glb_parse_to_asset(&glb, fd, path))
		return (false);
	close(fd);
	override_mats(&glb, over[2], over[3]);
	inject_glb(scene, &glb, over, s);
	glb_clear_asset(&glb);
	return (true);
}
