/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 04:26:30 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/29 07:21:22 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

t_object	*parse_cylinder(char *line)
{
	t_matrix	*rgb;
	t_index		idx;
	t_object	*obj;
	char		*split;

	split = ft_split(line, ' ');
	if (!validate_line(split, get_format_by_type(CAMERA)))
		return (NULL);
	obj = create_object();
	obj->type = CAMERA;
	obj->t->pos = parse_vector(split[1]);
	obj->t->normal = parse_norm_vector(split[2]);
	obj->fov = parse_int(split[1]);
	free_split(split);
	return (obj);
}
