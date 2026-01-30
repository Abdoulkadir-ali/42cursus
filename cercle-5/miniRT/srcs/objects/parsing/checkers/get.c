/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 23:08:24 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/30 15:47:57 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

t_object_validator	*get_validator(void)
{
	static t_object_validator	v[8] = {{"A", "fc", AMBIENT}, {"C", "vvi",
			CAMERA}, {"L", "vfc", LIGHT}, {"sp", "vfc", SPHERE}, {"pl", "vvc",
			PLANE}, {"sq", "vvfc", SQUARE}, {"cy", "vvffc", CYLINDER}, {NULL, NULL, -1}};

	return (v);
}

char	*get_format_by_type(int type)
{
	t_object_validator	*v;
	int					i;

	v = get_validator();
	i = 0;
	while (v[i].id)
	{
		if (v[i].type == type)
			return (v[i].format);
		i++;
	}
	return (NULL);
}
