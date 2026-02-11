/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynarray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antigravity <antigravity@gemini.google.com> +#    +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 00:00:00 by antigravity       #+#    #+#             */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * Ensures that the array capability is sufficient to hold at least one more element.
 * If *count >= *cap, doubles the capacity (or sets to initial 16).
 *
 * @param array Pointer to the array pointer (void**).
 * @param count Current number of elements.
 * @param cap Pointer to current capacity.
 * @param elem_size Size of a single element.
 * @return true on success, false on allocation failure.
 */
bool	dynarray_ensure(void **array, size_t count, size_t *cap, size_t elem_size)
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
		fprintf(stderr, "Error: Memory allocation failed in dynarray_ensure\n");
		return (false);
	}
	*array = new_ptr;
	*cap = new_cap;
	return (true);
}
