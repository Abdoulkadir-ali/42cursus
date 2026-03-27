/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repack.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 04:20:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 22:30:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"

/**
 * @brief Converts raw double array to engine's t_vec3 array.
 */
t_vec3	*fbx_repack_vec3(double *raw, uint32_t v_count)
{
	t_vec3		*out;
	uint32_t	i;

	out = ft_calloc(v_count, sizeof(t_vec3));
	if (out == NULL)
		return (NULL);
	i = 0;
	while (i < v_count)
	{
		out[i].x = raw[i * 3];
		out[i].y = raw[i * 3 + 1];
		out[i].z = raw[i * 3 + 2];
		out[i].w = 1.0;
		i++;
	}
	return (out);
}
