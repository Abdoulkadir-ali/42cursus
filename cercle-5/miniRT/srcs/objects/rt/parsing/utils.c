/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 17:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/08 01:25:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/objects.h"

bool	parse_float_checked(const char *str, double *out)
{
	char	*endptr;

	if (!str || !*str)
		return (false);
	*out = strtod(str, &endptr);
	if (endptr == str || (*endptr != '\0' && !ft_isspace(*endptr)))
		return (false);
	return (true);
}

bool	parse_vec3_checked(char *str, t_vec3 *out)
{
	char	**tokens;
	double	x;
	double	y;
	double	z;
	bool	res;

	if (!str)
		return (false);
	tokens = ft_split(str, ',');
	if (!tokens)
		return (false);
	if (!tokens[0] || !tokens[1] || !tokens[2] || tokens[3])
	{
		free_split(tokens);
		return (false);
	}
	res = parse_float_checked(tokens[0], &x) && parse_float_checked(tokens[1],
			&y) && parse_float_checked(tokens[2], &z);
	if (res)
		*out = vec3(x, y, z);
	free_split(tokens);
	return (res);
}

t_parse_obj	parse_mesh_entry(char **tokens, t_type type)
{
	t_parse_obj	obj;

	t_vec3 pos, scale, rot_vec;
	obj.type = TYPE_NONE;
	if (!tokens[1] || !tokens[2] || !tokens[3] || !tokens[4])
		return (obj);
	obj.type = type;
	obj.data.mesh_info.path = ft_strdup(tokens[1]);
	if (!parse_vec3_checked(tokens[2], &pos) || !parse_vec3_checked(tokens[3],
			&scale) || !parse_vec3_checked(tokens[4], &rot_vec))
	{
		free(obj.data.mesh_info.path);
		obj.type = TYPE_NONE;
	}
	else
	{
		obj.data.mesh_info.transform.pos = pos;
		obj.data.mesh_info.transform.scale = scale;
		obj.data.mesh_info.transform.rotation = (t_rotator){rot_vec.x,
			rot_vec.y, rot_vec.z};
	}
	return (obj);
}

bool	parse_color_checked(char *str, t_vec3 *out)
{
	t_vec3	col;

	if (!parse_vec3_checked(str, &col))
		return (false);
	if (col.x < 0 || col.x > 255 || col.y < 0 || col.y > 255 || col.z < 0
		|| col.z > 255)
		return (false);
	*out = col;
	return (true);
}
