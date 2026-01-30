/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 19:14:54 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/30 18:39:53 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

static bool	check_parameters(t_matrix *m, char *s)
{
	if (!m)
		return (false);
	if (m->dim.x != 3 || m->dim.y != 1)
		return (false);
	if (!s || !is_valid_vector(s))
		return (false);
	return (true);
}

static bool	clamp_component(void *v)
{
	double	*dv;

	if (!v)
		return (false);
	dv = (double *)v;
	if (*dv < -1.0)
		*dv = -1.0;
	else if (*dv > 1.0)
		*dv = 1.0;
	return (true);
}

bool	parse_normal_to_matrix(t_matrix *m, char *s,
		double (*conv)(const char *))
{
	t_index	idx;
	size_t	i;
	double	val;
	t_nodes	*parts;
	t_nodes	*cur;

	if (!check_parameters(m, s))
		return (false);
	parts = ft_split_nodes(s, ",", &any_match);
	if (!parts)
		return (false);
	cur = parts;
	idx = create_index(0, 0);
	i = 0;
	while (cur && i < m->dim.x)
	{
		val = conv((const char *)cur->content);
		matrix_set(m, idx, &val);
		cur = cur->next;
		idx.x++;
		i++;
	}
	ft_lstclear(&parts, free);
	if (!matrix_for_each(m, &clamp_component))
		return (false);
	return (true);
}
