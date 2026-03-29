/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynarray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 08:55:25 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/29 08:46:59 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static void	*aligned_realloc(void *ptr, size_t old_sz, size_t new_sz)
{
	void	*new_ptr;

	new_ptr = aligned_alloc(32, new_sz);
	if (!new_ptr)
		return (NULL);
	if (ptr)
	{
		ft_memcpy(new_ptr, ptr, old_sz);
		free(ptr);
	}
	return (new_ptr);
}

bool	dynarray_ensure(void **array, size_t count, size_t *cap, size_t elem_size)
{
	void	*new_ptr;
	size_t	old_sz;
	size_t	new_cap;

	if (count < *cap)
		return (true);
	new_cap = *cap;
	if (new_cap == 0)
		new_cap = 16;
	else
		new_cap *= 2;
	old_sz = *cap * elem_size;
	new_ptr = aligned_realloc(*array, old_sz, new_cap * elem_size);
	if (!new_ptr)
		return (false);
	ft_memset((char *)new_ptr + old_sz, 0, (new_cap - *cap) * elem_size);
	*array = new_ptr;
	*cap = new_cap;
	return (true);
}

bool	dynarray_ensure_count_impl(void **arr, size_t *count_ptr, size_t *cap_ptr, size_t elem_size)
{
    size_t cnt;
    size_t cap;
    bool ok;

    cnt = *count_ptr;
    cap = *cap_ptr;
    ok = dynarray_ensure((void **)arr, cnt, &cap, elem_size);
    *cap_ptr = cap;
    return (ok);
}
