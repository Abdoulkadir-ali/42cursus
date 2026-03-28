/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 12:57:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 12:57:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.h"

t_vec2	clamp_vec2(t_vec2 v, t_vec2 min, t_vec2 max)
{
	t_vec2	res;

	res.x = clamp_d(v.x, min.x, max.x);
	res.y = clamp_d(v.y, min.y, max.y);
	return (res);
}
