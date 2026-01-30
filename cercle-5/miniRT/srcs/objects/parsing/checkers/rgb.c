/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 23:07:46 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/30 17:10:49 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

static bool	is_rgb_int(char *s)
{
	int	val;

	if (!is_valid_int(s))
		return (false);
	val = ft_atoi(s);
	if (val < 0 || val > 255)
		return (false);
	return (true);
}

bool	is_valid_rgb(const char *s)
{
	return (is_triple(s, &is_rgb_int));
}

bool	parse_rgb(t_matrix *m, char *s, bool (*conv)(const char *))
{
	t_nodes	*split;
	t_index	idx;
	size_t	i;
	int		iv;
	double	dv;

	if (!m)
		return (false);
	if (m->dim.x != 3 || m->dim.y != 1)
		return (false);
	if (!s || !is_valid_rgb(s))
		return (false);
	{
		t_nodes *parts;
		t_nodes *cur;

		parts = ft_split_nodes(s, ",", &any_match);
		if (!parts)
			return (false);
		cur = parts;
		i = 0;
		idx.y = 0;
		while (cur && i < m->dim.x)
		{
			idx.x = i;
			if (!conv((const char *)cur->content))
			{
				ft_lstclear(&parts, free);
				return (false);
			}
			iv = ft_atoi((const char *)cur->content);
			dv = ((double)iv) / 255.0;
			matrix_set(m, idx, &dv);
			cur = cur->next;
			i++;
		}
		ft_lstclear(&parts, free);
	}
	return (true);
}
