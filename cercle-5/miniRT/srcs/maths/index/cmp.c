/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 02:24:57 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/28 03:01:16 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.h"

bool	is_same_x(t_index *i1, t_index *i2)
{
	return (i1->x == i2->x);
}

bool	is_same_y(t_index *i1, t_index *i2)
{
	return (i1->y == i2->y);
}

bool	is_same_indexes(t_index *i1, t_index *i2)
{
	return (is_same_x(i1, i2) && is_same_y(i1, i2));
}

bool	is_same_index_to_val(t_index *i1, size_t v)
{
	t_index	*i2;
	bool	res;

	i2 = create_index(v, v);
	if (!i2)
		return (0);
	res = is_same_indexes(i1, i2);
	free(i2);
	return (res);
}
