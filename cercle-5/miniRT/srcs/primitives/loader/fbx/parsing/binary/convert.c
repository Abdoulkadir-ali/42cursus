/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_convert.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 04:40:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/13 04:40:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"

static void	*fbx_convert_float_to_double(t_fbx_array *a, void *uncomp,
		uint32_t *count)
{
	void		*final_data;
	float		*src;
	double		*dst;
	uint32_t	i;

	final_data = malloc(a->arr_len * sizeof(double));
	if (!final_data)
		return (free(uncomp), NULL);
	src = (float *)uncomp;
	dst = (double *)final_data;
	i = 0;
	while (i < a->arr_len)
	{
		dst[i] = (double)src[i];
		i++;
	}
	free(uncomp);
	*count = a->arr_len;
	return (final_data);
}

void	*fbx_convert_array(t_fbx_array *a, void *uncomp, size_t elem_sz,
		uint32_t *count)
{
	void	*final_data;
	size_t	copy_sz;

	if (a->actual_sz == elem_sz)
	{
		*count = a->arr_len;
		return (uncomp);
	}
	if (a->actual_sz == 4 && elem_sz == 8)
		return (fbx_convert_float_to_double(a, uncomp, count));
	final_data = malloc(a->arr_len * elem_sz);
	if (!final_data)
		return (free(uncomp), NULL);
	copy_sz = a->actual_sz;
	if (copy_sz > elem_sz)
		copy_sz = elem_sz;
	ft_memcpy(final_data, uncomp, a->arr_len * copy_sz);
	free(uncomp);
	*count = a->arr_len;
	return (final_data);
}
