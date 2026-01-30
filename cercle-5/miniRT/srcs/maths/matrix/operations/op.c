/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 20:58:13 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/30 15:56:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.h"

bool	matrix_op(t_matrix *m1, const t_matrix *m2,
		bool (*check)(const t_matrix *, const t_matrix *), bool (*f)(void *,
			const void *))
{
	size_t	i;
	size_t	total_size;
	size_t	current_row;

	if (!check(m1, m2) || !f)
		return (0);
	total_size = m1->dim.x * m1->dim.y;
	i = 0;
	while (i < total_size)
	{
		current_row = i / m1->dim.x;
		if (is_same_index_to_val(m2->dim, 1))
		{
			if (!f(get_offset(m1, i), get_offset(m2, 0)))
				return (0);
		}
		else if (is_same_x(m1->dim, m2->dim))
		{
			if (!f(get_offset(m1, i), get_offset(m2, i)))
				return (0);
		}
		else
		{
			if (!f(get_offset(m1, i), get_offset(m2, current_row)))
				return (0);
		}
		i++;
	}
	return (1);
}
