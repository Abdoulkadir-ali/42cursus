/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 12:57:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 12:57:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.h"

t_vec3	clamp_vec3d(t_vec3 v, double min, double max)
{
	t_vec3	res;

	res.x = clamp_d(v.x, min, max);
	res.y = clamp_d(v.y, min, max);
	res.z = clamp_d(v.z, min, max);
	res.w = v.w;
	return (res);
}
