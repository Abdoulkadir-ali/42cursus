/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 21:02:42 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/28 03:57:16 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.h"

static bool	check_matrices(const t_matrix *m1, const t_matrix *m2)
{
	if (!m1 || !m2)
		return (0);
	if (!m1->v || !m2->v)
		return (0);
	return (1);
}

bool	check_multiply(const t_matrix *m1, const t_matrix *m2)
{
	if (!check_matrices(m1, m2))
		return (0);
	if (m1->dim->y != m2->dim->y)
		return (0);
	if (m2->dim->x == m1->dim->x || m2->dim->x == 1)
		return (1);
	return (0);
}

bool	check_add(const t_matrix *m1, const t_matrix *m2)
{
	if (!check_matrices(m1, m2))
		return (0);
	if (is_same_indexes(m1->dim, m2->dim))
		return (1);
	if (is_same_index_to_val(m2->dim, 1))
		return (1);
	if (is_same_y(m1->dim, m2->dim) && m2->dim->x == 1)
		return (1);
	return (0);
}
