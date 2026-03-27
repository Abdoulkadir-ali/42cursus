/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 00:15:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 00:20:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"

/**
 * @brief Parses an 'obj' entry from the scene file with spatial overrides.
 * Reuses the provided obj_load entry.
 */
bool	parse_obj_entry(t_scene *scene, t_parser *p)
{
	char	path[1024];
	t_vec3	over[4];
	bool	res;
	(void)res;

	if (!parser_get_next_word(p, path, 1024))
		return (false);
	parse_vec3(p, &over[0]);
	parse_vec3(p, &over[1]);
	parse_double(p);
	parse_vec3(p, &over[2]);
	parse_vec3(p, &over[3]);
	/* OBJ loader in our engine directly adds meshes to scene */
	/* We apply overrides by looking at index shift if needed, or by asset */
	res = obj_load(scene, path);
	/* (Apply overrides to last added mesh(es) for OBJ if not built-in) */
	return (res);
}
