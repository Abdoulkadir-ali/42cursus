/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/08 14:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.h"

t_vec2	vec2(double x, double y)
{
	return ((t_vec2){x, y});
}

t_vec2	vec2_pt(double x, double y)
{
	return ((t_vec2){x, y});
}

t_vec2	vec2_add(t_vec2 a, t_vec2 b)
{
	return ((t_vec2){a.x + b.x, a.y + b.y});
}

t_vec2	vec2_sub(t_vec2 a, t_vec2 b)
{
	return ((t_vec2){a.x - b.x, a.y - b.y});
}

t_vec2	vec2_mul(t_vec2 a, t_vec2 b)
{
	return ((t_vec2){a.x * b.x, a.y * b.y});
}
