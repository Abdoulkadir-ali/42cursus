/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/08 14:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

/**
 * Parses the ambient light entry from tokens.
 *
 * @param tokens The array of strings.
 * @return The parsed object data.
 */
/**
 * Parses the ambient light entry from the buffered parser.
 */
t_parse_obj	parse_ambient(t_parser *p)
{
	t_parse_obj	res = {0};

	res.type = TYPE_NONE;
	res.data.ambient.brightness = parse_double(p);
	if (!parse_vec3(p, &res.data.ambient.rgb))
		return (res);
	res.type = TYPE_AMBIENT;
	return (res);
}
