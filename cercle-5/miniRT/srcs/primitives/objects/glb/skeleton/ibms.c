/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ibms.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 14:50:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/09 02:57:54 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glb.h"

static void	fill_ibms_matrices(t_mat4 *dst, float *tmp, size_t count)
{
	size_t	i;
	size_t	r;
	size_t	c;

	i = 0;
	while (i < count)
	{
		c = 0;
		while (c < 4)
		{
			r = 0;
			while (r < 4)
				dst[i].m[r][c] = tmp[i * 16 + (r++) * 4 + c];
			c++;
		}
		i++;
	}
}

void	load_ibms(t_json_value *json, char *bin, int acc_idx, t_mat4 *dst)
{
	t_accessor		acc;
	t_buffer_view	bv;
	float			*tmp;

	glb_parse_accessor(json, acc_idx, &acc);
	glb_parse_buffer_view(json, acc.buffer_view, &bv);
	tmp = malloc(sizeof(float) * 16 * acc.count);
	if (!tmp)
		return ;
	glb_extract_data((t_extract){bin, &acc, &bv, tmp, sizeof(float) * 16,
		sizeof(float) * 16, sizeof(float) * 16, acc.count});
	fill_ibms_matrices(dst, tmp, acc.count);
	free(tmp);
}
