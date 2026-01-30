/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 04:26:30 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/29 07:21:39 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

t_object	*parse_light(char *line)
{
	t_matrix	*rgb;
	t_index		idx;
	t_object	*obj;
	char		*split;

	split = ft_split(line, ' ');
	if (!validate_line(split, get_format_by_type(LIGHT)))
		return (NULL);
	obj = create_object(sizeof);
	obj->type = LIGHT;
	obj->t->pos = parse_vector(split[1]);
	obj->t->alpha = parse_float(split[2]);
	obj->rgb = parse_int(split[3]);
	free_split(split);
	return (obj);
}
