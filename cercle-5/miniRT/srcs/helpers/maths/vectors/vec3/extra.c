/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_extra.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/12 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.h"

/* vec3_norm is now static inline in maths.h */

t_vec3	vec3_lerp(t_vec3 a, t_vec3 b, double t)
{
	return (vec3_add(a, vec3_scale(vec3_sub(b, a), t)));
}

t_vec3	vec3_min(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){fmin(a.x, b.x), fmin(a.y, b.y), fmin(a.z, b.z),
		fmin(a.w, b.w)});
}

t_vec3	vec3_max(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){fmax(a.x, b.x), fmax(a.y, b.y), fmax(a.z, b.z),
		fmax(a.w, b.w)});
}

bool	vec3_compare(t_vec3 a, t_vec3 b)
{
	return (a.x == b.x && a.y == b.y && a.z == b.z);
}
