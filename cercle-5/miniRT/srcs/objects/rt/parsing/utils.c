/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 17:30:00 by abdoali           #+#    #+#             */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

/**
 * Parses a float value from a string and checks for validity.
 * 
 * @param str The string to parse.
 * @param out Pointer to store the result.
 * @return True if successful, false otherwise.
 */
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

/**
 * Parses a comma-separated triplet of floats into a t_vec3.
 * 
 * @param str The string to parse (e.g., "1.0,2.0,3.0").
 * @param out Pointer to store the resulting t_vec3.
 * @return True if successful, false otherwise.
 */
bool	parse_vec3_checked(char *str, t_vec3 *out)
{
	char	**tokens;
	t_vec3	v;
	bool	res;

	v = vec3(0, 0, 0);

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
	res = parse_float_checked(tokens[0], &v.x);
	res = res && parse_float_checked(tokens[1], &v.y);
	res = res && parse_float_checked(tokens[2], &v.z);
	if (res)
		*out = v;
	free_split(tokens);
	return (res);
}

/**
 * Parses a mesh entry from tokens.
 * 
 * @param tokens The array of strings.
 * @param type The object type (TYPE_ANIM or TYPE_MESH).
 * @return The parsed object data.
 */
t_parse_obj	parse_mesh_entry(char **tokens, t_type type)
{
	t_parse_obj	obj;
	t_vec3		pos;
	t_vec3		scale;
	t_vec3		rot;

	obj.type = TYPE_NONE;
	if (!tokens[1] || !tokens[2] || !tokens[3] || !tokens[4])
		return (obj);
	obj.type = type;
	obj.data.mesh_info.path = ft_strdup(tokens[1]);
	if (!parse_vec3_checked(tokens[2], &pos) || !parse_vec3_checked(tokens[3], \
			&scale) || !parse_vec3_checked(tokens[4], &rot))
	{
		free(obj.data.mesh_info.path);
		obj.type = TYPE_NONE;
	}
	else
	{
		obj.data.mesh_info.transform.pos = pos;
		obj.data.mesh_info.transform.scale = scale;
		obj.data.mesh_info.transform.rotation = (t_rotator){rot.x, \
			rot.y, rot.z};
	}
	return (obj);
}

/**
 * Parses a color triplet from a string and validates the range [0, 255].
 * 
 * @param str The string to parse.
 * @param out Pointer to store the resulting t_vec3.
 * @return True if successful, false otherwise.
 */
bool	parse_color_checked(char *str, t_vec3 *out)
{
	t_vec3	col;

	if (!parse_vec3_checked(str, &col))
		return (false);
	if (col.x < 0 || col.x > 255 || col.y < 0 || col.y > 255 || col.z < 0 \
		|| col.z > 255)
		return (false);
	*out = col;
	return (true);
}
