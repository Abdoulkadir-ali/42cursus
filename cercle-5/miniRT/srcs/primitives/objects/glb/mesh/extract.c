/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 16:33:40 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/30 22:29:31 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glb.h"

/**
 * Extracts binary data from a GLB buffer given an accessor and buffer view.
 * Handles strided data copies into the destination buffer.
 */
void	glb_extract_data(t_extract ext)
{
	unsigned char	*src;
	unsigned char	*dst;
	size_t			i;

	src = (unsigned char *)(ext.bin + ext.bv->byte_offset
			+ ext.acc->byte_offset);
	dst = (unsigned char *)ext.dst;
	i = -1;
	while (++i < (size_t)ext.count)
	{
		ft_memcpy(dst + i * ext.dst_stride, src + i * ext.ext_stride,
			ext.elem_size);
	}
}
