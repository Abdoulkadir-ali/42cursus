/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 14:15:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 14:34:33 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "helpers.h"
#include <stdlib.h>

t_index	init_index(size_t i, bool error)
{
	t_index	idx;

	idx.i = i;
	idx.error = error;
	return (idx);
}

t_index	index_error(void)
{
	return (init_index(0, true));
}

t_index	index_success(size_t i)
{
	return (init_index(i, false));
}

t_index	*alloc_index(size_t i, bool error)
{
	t_index	*idx;

	idx = ft_calloc(1, sizeof(t_index));
	if (!idx)
		return (NULL);
	idx->i = i;
	idx->error = error;
	return (idx);
}
