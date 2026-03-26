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
	return ((t_vec3){fmin(a.x, b.x), fmin(a.y, b.y), fmin(a.z, b.z), fmin(a.w,
			b.w)});
}

t_vec3	vec3_max(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){fmax(a.x, b.x), fmax(a.y, b.y), fmax(a.z, b.z), fmax(a.w,
			b.w)});
}
