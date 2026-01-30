/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 04:26:30 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/29 07:21:47 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

t_object	*parse_plane(char *line)
{
	t_matrix	*rgb;
	t_index		idx;
	t_object	*obj;
	char		*split;

	split = ft_split(line, ' ');
	if (!validate_line(split, get_format_by_type(PLANE)))
		return (NULL);
	obj = create_object();
	obj->type = PLANE;
	obj->t->pos = parse_vector(split[1]);
	obj->t->normal = parse_vector(split[2]);
	obj->rgb = parse_rgb(split[3]);
	free_split(split);
	return (obj);
}
