/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynarray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 13:47:02 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/11 13:47:02 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <stdlib.h>
#include <stdio.h>

/* Ensure capacity for one more element. */
bool	dynarray_ensure(void **array, size_t count,
		size_t *cap, size_t elem_size)
{
	void	*new_ptr;
	size_t	new_cap;

	if (count < *cap)
		return (true);
	if (*cap == 0)
		new_cap = 16;
	else
		new_cap = *cap * 2;
	new_ptr = realloc(*array, new_cap * elem_size);
	if (!new_ptr)
	{
		fprintf(stderr,
			"Error: Memory allocation failed in dynarray_ensure\n");
		return (false);
	}
	/* Zero out the new portion of the array */
	ft_memset((char *)new_ptr + (*cap * elem_size), 0,
		(new_cap - *cap) * elem_size);
	*array = new_ptr;
	*cap = new_cap;
	return (true);
}
