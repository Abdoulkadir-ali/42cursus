/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ibms.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 14:50:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 14:47:54 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glb.h"

void	load_ibms(t_json_value *json, char *bin, int acc_idx, t_mat4 *dst)
{
	t_accessor		acc;
	t_buffer_view	bv;
	float			*tmp;
	size_t			v[3];

	glb_parse_accessor(json, acc_idx, &acc);
	glb_parse_buffer_view(json, acc.buffer_view, &bv);
	tmp = malloc(sizeof(float) * 16 * acc.count);
	if (!tmp)
		return ;
	glb_extract_data((t_extract){bin, &acc, &bv, tmp, sizeof(float) * 16,
		sizeof(float) * 16, sizeof(float) * 16, acc.count});
	v[0] = -1;
	while (++v[0] < acc.count)
	{
		v[1] = -1;
		while (++v[1] < 4)
		{
			v[2] = -1;
			while (++v[2] < 4)
				dst[v[0]].m[v[2]][v[1]] = tmp[v[0] * 16 + v[2] * 4 + v[1]];
		}
	}
	free(tmp);
}
