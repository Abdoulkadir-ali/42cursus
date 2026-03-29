/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 10:59:54 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 11:00:54 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.h"

t_vec3	vec3_min(t_vec3 a, t_vec3 b)
{
	t_vec3	r;

	r.x = fmin(a.x, b.x);
	r.y = fmin(a.y, b.y);
	r.z = fmin(a.z, b.z);
	r.w = 0.0;
	return (r);
}

t_vec3	vec3_max(t_vec3 a, t_vec3 b)
{
	t_vec3	r;

	r.x = fmax(a.x, b.x);
	r.y = fmax(a.y, b.y);
	r.z = fmax(a.z, b.z);
	r.w = 0.0;
	return (r);
}
