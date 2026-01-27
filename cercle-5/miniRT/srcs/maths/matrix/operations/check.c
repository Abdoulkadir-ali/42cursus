/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 21:02:42 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/27 21:21:23 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.h"

int	check_multiply(const t_matrix *m1, const t_matrix *m2)
{
	if (!m1 || !m2)
		return (0);
	if (!m1->v || !m2->v)
		return (0);
	if (m1->dim->y != m2->dim->y)
		return (0);
	if (m2->dim->x == m1->dim->x || m2->dim->x == 1)
		return (1);
	return (0);
}

int check_as
