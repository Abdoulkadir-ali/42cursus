/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 21:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/27 18:32:21 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "helpers/index.h"

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
