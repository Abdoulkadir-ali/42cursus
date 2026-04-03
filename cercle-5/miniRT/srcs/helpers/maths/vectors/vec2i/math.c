/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2i_math.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 19:31:44 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/06 20:06:38 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.h"

int	vec2i_dot(t_vec2i a, t_vec2i b)
{
	return (a.x * b.x + a.y * b.y);
}

int	vec2i_mag_sq(t_vec2i a)
{
	return (a.x * a.x + a.y * a.y);
}

int	vec2i_mag(t_vec2i a)
{
	return (sqrt(a.x * a.x + a.y * a.y));
}

t_vec2i	vec2i_norm(t_vec2i a)
{
	int	mag;

	mag = vec2i_mag(a);
	if (mag == 0)
		return (a);
	return ((t_vec2i){a.x / mag, a.y / mag});
}
