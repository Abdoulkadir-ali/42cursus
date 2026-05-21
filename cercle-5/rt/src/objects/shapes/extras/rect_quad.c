/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rect_quad.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 19:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 17:54:27 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	parse_rect_quad(char **t, int n, t_scene *s)
{
	t_vec3	a;
	t_vec3	b;
	t_vec3	c;
	t_vec3	d;
	t_vec3	col;
	int		first;

	if (n != 6)
		return (0);
	if (!parse_vec3(t[1], &a) || !parse_vec3(t[2], &b)
		|| !parse_vec3(t[3], &c) || !parse_vec3(t[4], &d))
		return (0);
	if (!parse_color(t[5], &col))
		return (0);
	first = s->n_bvh;
	if (!push_tri(s, a, b, c, col))
		return (0);
	if (!push_tri(s, a, c, d, col))
		return (0);
	s->last_kind = 1;
	s->last_first = first;
	s->last_count = 2;
	return (1);
}
