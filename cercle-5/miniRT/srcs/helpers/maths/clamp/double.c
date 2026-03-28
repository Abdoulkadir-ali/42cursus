/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 12:57:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 12:57:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.h"

double	clamp_d(double v, double min, double max)
{
	if (v < min)
		return (min);
	if (v > max)
		return (max);
	return (v);
}