/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 12:57:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 12:57:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.h"

t_vec2	clamp_vec2d(t_vec2 v, double min, double max)
{
	t_vec2	res;

	res.x = clamp_d(v.x, min, max);
	res.y = clamp_d(v.y, min, max);
	return (res);
}
