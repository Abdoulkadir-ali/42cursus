/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynarray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 08:55:25 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 08:55:27 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "helpers.h"

bool	dynarray_ensure(void **array, size_t count, size_t *cap, size_t elem_size)
{
	void	*new_ptr;
	size_t	new_cap;

	if (count < *cap)
		return (true);
	new_cap = *cap;
	if (new_cap == 0)
		new_cap = 16;
	else
		new_cap *= 2;
	new_ptr = realloc(*array, new_cap * elem_size);
	if (!new_ptr)
		return (false);
	ft_memset((char *)new_ptr + (*cap * elem_size), 0, (new_cap - *cap) * elem_size);
	*array = new_ptr;
	*cap = new_cap;
	return (true);
}

bool	dynarray_ensure_int_impl(void **arr, int *count_ptr, int *cap_ptr, size_t elem_size)
{
	size_t	cnt;
	size_t	cap;
	bool	ok;

	cnt = (size_t)(*count_ptr);
	cap = (size_t)(*cap_ptr);
	ok = dynarray_ensure((void **)arr, cnt, &cap, elem_size);
	*cap_ptr = (int)cap;
	return (ok);
}
