/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 20:58:13 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/27 21:19:31 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.h"

int	matrix_op(t_matrix *m1, const t_matrix *m2, int (*check)(const t_matrix *,
			const t_matrix *), int (*f)(void *, const void *))
{
	size_t	i;
	size_t	total_size;
	size_t	current_row;

	if (!check(m1, m2) || !f)
		return (1);
	total_size = m1->dim->x * m1->dim->y;
	i = 0;
	while (i < total_size)
	{
		current_row = i / m1->dim->x;
		if (m1->dim->x == m2->dim->x)
		{
			if (f(get_offset(m1, i), get_offset(m2, i)))
				return (1);
		}
		else
		{
			if (f(get_offset(m1, i), get_offset(m2, current_row)))
				return (1);
		}
		i++;
	}
	return (0);
}
