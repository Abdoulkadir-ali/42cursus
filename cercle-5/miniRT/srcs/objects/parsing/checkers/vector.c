/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 23:08:24 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/30 18:39:53 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

bool	is_triple(const char *s, bool (*f)(const char *))
{
	t_nodes *split;
	t_nodes *cur;
	int	count;
	bool	res;

	count = 0;
	res = true;
	split = ft_split_nodes(s, ",", &any_match);
	if (!split)
		return (false);
	cur = split;
	while (cur)
	{
		if (!f((const char *)cur->content))
			res = false;
		count++;
		cur = cur->next;
	}
	if (count != 3)
		res = false;
	ft_lstclear(&split, free);
	return (res);
}

bool	is_valid_vector(const char *s)
{
	return (is_triple(s, &is_valid_float));
}

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

bool	parse_vector(t_matrix *m, char *s, double *(*f)(const char *))
{
	t_index	idx;
	size_t	i;
	double	*v;

	if (!check_parameters(m, s))
		return (false);
	{
		t_nodes *parts;
		t_nodes *cur;

		parts = ft_split_nodes(s, ",", &any_match);
		if (!parts)
			return (false);
		cur = parts;
		idx.y = 0;
		i = 0;
		while (cur && i < m->dim.x)
		{
			idx.x = i;
			v = f((const char *)cur->content);
			if (!v)
			{
				ft_lstclear(&parts, free);
				return (false);
			}
			matrix_set(m, idx, v);
			free(v);
			cur = cur->next;
			i++;
		}
		ft_lstclear(&parts, free);
		return (true);
	}

}
