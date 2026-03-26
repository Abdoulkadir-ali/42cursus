/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2i_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 19:31:44 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/06 20:06:26 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.h"

t_vec2i	vec2i_add(t_vec2i a, t_vec2i b)
{
	return ((t_vec2i){a.x + b.x, a.y + b.y});
}

t_vec2i	vec2i_sub(t_vec2i a, t_vec2i b)
{
	return ((t_vec2i){a.x - b.x, a.y - b.y});
}

t_vec2i	vec2i_mul(t_vec2i a, t_vec2i b)
{
	return ((t_vec2i){a.x * b.x, a.y * b.y});
}

t_vec2i	vec2i_scale(t_vec2i a, int s)
{
	return ((t_vec2i){a.x * s, a.y * s});
}
