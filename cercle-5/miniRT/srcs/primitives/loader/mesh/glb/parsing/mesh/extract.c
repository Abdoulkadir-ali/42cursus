/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 15:55:08 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"

/**
 * @brief Binary data extractor using core structures.
 * No _ctx used here, only raw members.
 */
void	glb_extract_data(char *bin, t_glb_accessor *acc, t_glb_buffer_view *bv, 
		void *entry)
{
	int		i;
	int		src_stride;
	char	*src;
	char	*dst;

	if (bin == NULL || bv == NULL || acc == NULL || entry == NULL)
		return ;
	if (acc->byte_offset + acc->count * acc->type_size > bv->byte_length)
		return ;
	src = bin + bv->byte_offset + acc->byte_offset;
	src_stride = bv->byte_stride;
	if (src_stride == 0)
		src_stride = acc->type_size;
	dst = (char *)entry;
	if (src_stride == (int)acc->type_size && (int)acc->stride == (int)acc->type_size)
	{
		ft_memcpy(dst, src, (size_t)acc->count * acc->type_size);
		return ;
	}
	i = 0;
	while (i < acc->count)
	{
		ft_memcpy(dst + i * acc->stride, src + i * src_stride, acc->type_size);
		i++;
	}
}

/**
 * @brief Handles 16-bit indices by expanding them to 32-bit locally.
 * Variables limited to 4. No loops other than while.
 */
void	glb_handle_indices_short(t_mesh_asset *mesh, t_json_value *json, char *bin, 
		int idx)
{
	t_glb_accessor		acc;
	t_glb_buffer_view	bv;
	unsigned short	*temp;
	int				k;

	glb_parse_accessor(json, idx, &acc);
	glb_parse_buffer_view(json, acc.buffer_view, &bv);
	temp = malloc(sizeof(unsigned short) * acc.count);
	if (temp == NULL)
		return ;
	acc.type_size = sizeof(unsigned short);
	acc.stride = sizeof(unsigned short);
	glb_extract_data(bin, &acc, &bv, temp);
	k = 0;
	while (k < acc.count)
	{
		mesh->indices[k] = (int)temp[k];
		k++;
	}
	free(temp);
}
