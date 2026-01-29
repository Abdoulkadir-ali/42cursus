/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 19:14:54 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/29 14:04:25 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

static bool	check_parameters(t_matrix *m, char *s)
{
	if (!m || !m->dim)
		return (false);
	if (m->dim->x != 3 || m->dim->y != 1)
		return (false);
	if (!s || !is_valid_vector(s))
		return (false);
	return (true);
}

static bool	clamp_component(void *v)
{
	double	*dv;

	if (!v)
		return (false);
	dv = (double *)v;
	if (*dv < -1.0)
		*dv = -1.0;
	else if (*dv > 1.0)
		*dv = 1.0;
	return (true);
}

bool	parse_normal_to_matrix(t_matrix *m, char *s,
		double (*conv)(const char *))
{
	if (!check_parameters(m, s))
		return (false);
	if (!parse_vector(m, s, conv))
		return (false);
	if (!matrix_for_each(m, &clamp_component))
		return (false);
	return (true);
}
