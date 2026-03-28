/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 12:57:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 12:57:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.h"

t_vec3	clamp_vec3(t_vec3 v, t_vec3 min, t_vec3 max)
{
	t_vec3	res;

	res.x = clamp_d(v.x, min.x, max.x);
	res.y = clamp_d(v.y, min.y, max.y);
	res.z = clamp_d(v.z, min.z, max.z);
	res.w = v.w;
	return (res);
}
