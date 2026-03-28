/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 04:40:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 21:55:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"

/**
 * @brief FBX conversion from float buffer to double destination.
 */
static void	*to_double(t_fbx_array *a, void *src, uint32_t *cnt)
{
	double		*dst;
	float		*raw;
	uint32_t	i;

	dst = malloc(a->arr_len * sizeof(double));
	if (dst == NULL)
		return (free(src), NULL);
	raw = (float *)src;
	i = 0;
	while (i < a->arr_len)
	{
		dst[i] = (double)raw[i];
		i++;
	}
	free(src);
	*cnt = a->arr_len;
	return (dst);
}

/**
 * @brief Dispatcher for FBX binary types conversion to engine types.
 */
void	*fbx_convert_array(t_fbx_array *a, void *uncomp, size_t elem_sz,
		uint32_t *count)
{
	void	*final;

	if (a->actual_sz == elem_sz)
	{
		*count = a->arr_len;
		return (uncomp);
	}
	if (a->actual_sz == 4 && elem_sz == 8)
		return (to_double(a, uncomp, count));
	final = malloc(a->arr_len * elem_sz);
	if (final == NULL)
		return (free(uncomp), NULL);
	/* Generic copy if same size or truncation */
	ft_memcpy(final, uncomp, a->arr_len * a->actual_sz);
	free(uncomp);
	*count = a->arr_len;
	return (final);
}
