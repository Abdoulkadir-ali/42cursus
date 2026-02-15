/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   roots.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/08 14:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.h"

/*
** Solves a quadratic equation ax^2 + bx + c = 0.
** Stores the two roots in t1 and t2.
** Returns true if real roots exist, false otherwise.
*/
bool	solve_quadratic(t_quadratic q, t_quadratic_roots *roots)
{
	double	discriminant;
	double	sqrt_d;

	if (fabs(q.a) < EPSILON)
		return (false);
	discriminant = q.b * q.b - 4 * q.a * q.c;
	if (discriminant < 0)
		return (false);
	sqrt_d = sqrt(discriminant);
	roots->t1 = (-q.b - sqrt_d) / (2 * q.a);
	roots->t2 = (-q.b + sqrt_d) / (2 * q.a);
	return (true);
}
