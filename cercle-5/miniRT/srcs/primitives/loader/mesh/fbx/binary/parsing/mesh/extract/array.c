/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 21:50:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"
#include <zlib.h>

/**
 * @brief FBX binary array header parsing.
 */
static bool	h_read(int fd, t_fbx_array *a)
{
	if (read(fd, &a->type, 1) < 1)
		return (false);
	a->actual_sz = 1;
	if (a->type == 'd' || a->type == 'l')
		a->actual_sz = 8;
	else if (a->type == 'f' || a->type == 'i')
		a->actual_sz = 4;
	if (read(fd, &a->arr_len, 4) < 4 || read(fd, &a->encoding, 4) < 4
		|| read(fd, &a->comp_len, 4) < 4)
		return (false);
	if (a->arr_len > 2000000)
		return (false);
	return (true);
}

/**
 * @brief Handle zlib decompression for FBX binary chunks.
 */
static void	*c_read(int fd, t_fbx_array *a, void *uncomp_data, uLongf *ulen)
{
	void	*comp_data;

	comp_data = malloc(a->comp_len + 1);
	if (comp_data == NULL)
		return (free(uncomp_data), NULL);
	if (read(fd, comp_data, a->comp_len) < (ssize_t)a->comp_len)
		return (free(comp_data), free(uncomp_data), NULL);
	if (uncompress(uncomp_data, ulen, comp_data, a->comp_len) != Z_OK)
		return (free(comp_data), free(uncomp_data), NULL);
	free(comp_data);
	return (uncomp_data);
}

/**
 * @brief Acquires FBX binary array payload (raw or compressed).
 */
static void	*p_read(int fd, t_fbx_array *a)
{
	uLongf	ulen;
	void	*u_data;

	ulen = (uLongf)((size_t)a->arr_len * (size_t)a->actual_sz);
	u_data = malloc(ulen + 1);
	if (u_data == NULL)
		return (NULL);
	if (a->encoding == 0)
	{
		if (read(fd, u_data, ulen) < (ssize_t)ulen)
			return (free(u_data), NULL);
		return (u_data);
	}
	return (c_read(fd, a, u_data, &ulen));
}

/**
 * @brief Core entry for reading and extracting compressed FBX arrays.
 */
void	*read_fbx_array(int fd, uint32_t *count, size_t elem_sz)
{
	t_fbx_array	a;
	void		*uncomp_data;

	if (h_read(fd, &a) == false)
		return (NULL);
	uncomp_data = p_read(fd, &a);
	if (uncomp_data == NULL)
		return (NULL);
	/* Pointer to conversion will follow in convert.c */
	return (fbx_convert_array(&a, uncomp_data, elem_sz, count));
}
