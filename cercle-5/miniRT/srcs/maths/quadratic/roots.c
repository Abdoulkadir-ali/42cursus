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
bool	solve_quadratic(double a, double b, double c, double *t1, double *t2)
{
	double	discriminant;
	double	sqrt_d;

	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (false);
	sqrt_d = sqrt(discriminant);
	*t1 = (-b - sqrt_d) / (2 * a);
	*t2 = (-b + sqrt_d) / (2 * a);
	return (true);
}
