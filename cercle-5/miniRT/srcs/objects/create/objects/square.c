/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 04:26:30 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/29 07:22:06 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

t_object	*parse_square(char line)
{
	t_matrix	*rgb;
	t_index		idx;
	t_object	*obj;
	char		*split;

	split = ft_split(line, ' ');
	if (!validate_line(split, get_format_by_type(SQUARE)))
		return (NULL);
	obj = create_object();
	obj->type = SQUARE;
	obj->t->pos = parse_vector(split[1]);
	m = matrix_add_scalar(parse_vector(split[2]), parse_float(split[2]));
	obj->t->scale = m;
	obj->rgb = parse_vector(split[3]);
	free_split(split);
	return (obj);
}
