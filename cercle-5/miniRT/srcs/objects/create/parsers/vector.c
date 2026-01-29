/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 23:08:24 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/29 07:13:42 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

bool	is_triple(char *s, bool (*f)(char *))
{
	char	**split;
	int		count;
	bool	res;

	count = 0;
	res = true;
	split = ft_split(s, ',');
	if (!split)
		return (false);
	while (split[count])
	{
		if (!f(split[count]))
			res = false;
		count++;
	}
	if (count != 3)
		res = false;
	free_split(split);
	return (res);
}

bool	is_valid_vector(char *s)
{
	return (is_triple(s, &is_valid_float));
}

static bool	check_parameters(t_matrix *m, char *s)
{
	if (!m || !m->dim)
		return (false);
	if (m->dim->x != 3 || m->dim->y != 1)
		return (false);
	if (!s || !is_valid_vector(s))
		return (false);
	return (true);
}

bool	parse_vector_to_matrix(t_matrix *m, char *s, void *(*f)(char *))
{
	t_index	idx;
	char	**parts;
	size_t	i;
	void	*v;

	if (!check_parameters(m, s))
		return (false);
	parts = ft_split(s, ',');
	if (!parts)
		return (false);
	idx.y = 0;
	i = 0;
	while (parts[i] && i < m->dim->x)
	{
		idx.x = i;
		v = f(parts[i++]);
		matrix_set(m, &idx, &v);
	}
	free_split(parts);
	return (true);
}
