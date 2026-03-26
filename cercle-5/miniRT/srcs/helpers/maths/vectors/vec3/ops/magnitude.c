/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   magnitude.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 10:59:51 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 11:01:37 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.h"

double	vec3_mag(t_vec3 a)
{
	return (sqrt(vec3_mag_sq(a)));
}

double	vec3_mag_sq(t_vec3 a)
{
	return (vec3_dot(a, a));
}
