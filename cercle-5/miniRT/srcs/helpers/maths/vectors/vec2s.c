/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2s.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 03:20:24 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/09 03:20:25 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.h"

t_vec2s	vec2s(size_t x, size_t y)
{
	t_vec2s	v;

	v.x = x;
	v.y = y;
	return (v);
}

t_vec2s	vec2s_add(t_vec2s a, t_vec2s b)
{
	return ((t_vec2s){a.x + b.x, a.y + b.y});
}

t_vec2s	vec2s_sub(t_vec2s a, t_vec2s b)
{
	return ((t_vec2s){a.x - b.x, a.y - b.y});
}
