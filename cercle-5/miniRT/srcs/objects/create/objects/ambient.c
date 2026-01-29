/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 04:26:30 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/29 07:23:16 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

t_object	*parse_ambient(char *line)
{
	t_matrix	*rgb;
	t_index		idx;
	t_object	*obj;
	char		**split;

	split = ft_split(line, ' ');
	if (!validate_line(split, get_format_by_type(AMBIENT)))
		return (NULL);
	obj = create_object();
	obj->type = AMBIENT;
	obj->alpha = parse_float(split[1]);
	parse_rgb_to_matrix(rgb, split[2], &to_double);
	obj->rgb = rgb;
	return (obj);
}
