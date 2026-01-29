/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 19:14:54 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/29 07:08:12 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.h"

static bool	normalize_vector(t_matrix *m)
{
	t_index idx;
	double *vx;
	double *vy;
	double *vz;
	double norm;

	if (!m)
		return (false);
	idx.y = 0;
	idx.x = 0;
	vx = (double *)matrix_get(m, &idx);
	idx.x = 1;
	vy = (double *)matrix_get(m, &idx);
	idx.x = 2;
	vz = (double *)matrix_get(m, &idx);
	if (!vx || !vy || !vz)
		return (false);
	norm = sqrt((*vx) * (*vx) + (*vy) * (*vy) + (*vz) * (*vz));
	if (norm == 0.0)
		return (false);
	*vx /= norm;
	*vy /= norm;
	*vz /= norm;
	return (true);
}