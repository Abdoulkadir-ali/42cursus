/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_entry.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 20:50:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 11:50:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

static bool	rt_parse_mesh_info(t_parser *p, t_mesh_info *info)
{
	if (!parse_vec3(p, &info->transform.pos))
		return (false);
	if (!parse_vec3(p, &info->transform.forward))
		return (false);
	if (vec3_mag_sq(info->transform.forward) > 0.0)
		info->transform.forward = vec3_norm(info->transform.forward);
	else
		info->transform.forward = vec3(0, 0, 1);
	info->transform.scale = vec3(1, 1, 1);
	rt_parse_scale_raw(p, &info->transform.scale);
	parser_skip_spaces(p);
	if (parser_peek(p) && parser_peek(p) != '\n')
		parse_vec3(p, &info->color);
	parser_skip_spaces(p);
	if (parser_peek(p) && parser_peek(p) != '\n')
		parse_vec3(p, &info->emission);
	return (true);
}

bool	parse_mesh_entry(t_scene *scene, t_parser *p, t_type type)
{
	t_mesh_info	info;
	char		path[1024];

	if (!rt_parse_token(p, path, sizeof(path)))
		return (false);
	ft_memset(&info, 0, sizeof(t_mesh_info));
	info.path = ft_strdup(path);
	info.color = vec3(255, 255, 255);
	info.emission = vec3(0, 0, 0);
	if (!rt_parse_mesh_info(p, &info))
	{
		free(info.path);
		return (false);
	}
	return (handle_mesh_injection_internal(scene, &info, type));
}
