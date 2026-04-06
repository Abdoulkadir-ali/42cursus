/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/13 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fbx.h"
#include <zlib.h>

static bool	fbx_read_array_header(int fd, t_fbx_array *a)
{
	if (safe_read(fd, &a->type, 1) < 1)
		return (false);
	if (a->type == 'd')
		a->actual_sz = 8;
	else if (a->type == 'f' || a->type == 'i')
		a->actual_sz = 4;
	else if (a->type == 'l' || a->type == 'b' || a->type == 'c')
	{
		if (a->type == 'l')
			a->actual_sz = 8;
		else
			a->actual_sz = 1;
	}
	else
		return (false);
	if (safe_read(fd, &a->arr_len, 4) < 4)
		return (false);
	if (safe_read(fd, &a->encoding, 4) < 4)
		return (false);
	if (safe_read(fd, &a->comp_len, 4) < 4)
		return (false);
	if (a->arr_len > 20000000)
		return (false);
	return (true);
}

static void	*fbx_read_compressed(int fd, t_fbx_array *a, void *uncomp_data,
		uLongf *uncomp_len)
{
	void	*comp_data;
	size_t	size;

	size = a->comp_len;
	if (size == 0)
		size = 1;
	comp_data = ft_calloc(1, size);
	if (!comp_data)
		return (free(uncomp_data), NULL);
	if (safe_read(fd, comp_data, a->comp_len) < (ssize_t)a->comp_len)
		return (free(comp_data), free(uncomp_data), NULL);
	if (uncompress(uncomp_data, uncomp_len, comp_data, a->comp_len) != Z_OK)
		return (free(comp_data), free(uncomp_data), NULL);
	free(comp_data);
	return (uncomp_data);
}

static void	*fbx_read_array_payload(int fd, t_fbx_array *a)
{
	uLongf	uncomp_len;
	void	*uncomp_data;
	size_t	size;

	uncomp_len = a->arr_len * a->actual_sz;
	size = uncomp_len;
	if (size == 0)
		size = 1;
	uncomp_data = ft_calloc(1, size);
	if (!uncomp_data)
		return (NULL);
	if (a->encoding == 0)
	{
		if (safe_read(fd, uncomp_data, uncomp_len) < (ssize_t)uncomp_len)
			return (free(uncomp_data), NULL);
		return (uncomp_data);
	}
	return (fbx_read_compressed(fd, a, uncomp_data, &uncomp_len));
}

void		*fbx_convert_array(t_fbx_array *a, void *uncomp, size_t elem_sz,
				size_t *count);

void	*read_fbx_array(int fd, size_t *count, size_t elem_sz)
{
	t_fbx_array	a;
	void		*uncomp_data;

	if (!fbx_read_array_header(fd, &a))
		return (NULL);
	uncomp_data = fbx_read_array_payload(fd, &a);
	if (!uncomp_data)
		return (NULL);
	return (fbx_convert_array(&a, uncomp_data, elem_sz, count));
}
