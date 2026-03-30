/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/12 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

void	glb_extract_data(t_extract_ctx ctx)
{
	int		i;
	int		src_stride;
	char	*src;
	char	*dst;

	if (!ctx.bin || !ctx.bv || !ctx.acc || !ctx.entry)
		return ;
	src = ctx.bin + ctx.bv->byte_offset + ctx.acc->byte_offset;
	src_stride = ctx.bv->byte_stride;
	if (src_stride == 0)
		src_stride = ctx.type_size;
	dst = (char *)ctx.entry;
	i = 0;
	while (i < ctx.count)
	{
		ft_memcpy(dst + i * ctx.stride, src + i * src_stride, ctx.type_size);
		i++;
	}
}

void	glb_handle_indices_short(t_mesh *mesh, t_json_value *json, char *bin, int idx)
{
	t_accessor		acc;
	t_buffer_view	bv;
	t_extract_ctx	ctx;
	unsigned short	*temp;
	int				k;

	glb_parse_accessor(json, idx, &acc);
	glb_parse_buffer_view(json, acc.buffer_view, &bv);
	temp = malloc(sizeof(unsigned short) * acc.count);
	if (!temp)
		return ;
	ctx = (t_extract_ctx){bin, &acc, &bv, temp, sizeof(unsigned short),
		acc.count, sizeof(unsigned short)};
	glb_extract_data(ctx);
	k = -1;
	while (++k < acc.count)
		mesh->indices[k] = (int)temp[k];
	free(temp);
}
