/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repack.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 04:20:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/13 04:20:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fbx.h"

t_vec3	*repack_doubles_to_vec3(double *raw, size_t count)
{
	t_vec3		*out;
	size_t	i;

	out = ft_calloc(count, sizeof(t_vec3));
	if (!out)
		return (NULL);
	i = 0;
	while (i < count)
	{
		out[i].x = raw[i * 3];
		out[i].y = raw[i * 3 + 1];
		out[i].z = raw[i * 3 + 2];
		out[i].w = 0.0;
		i++;
	}
	return (out);
}
