/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterate.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 18:29:01 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/30 15:57:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.h"

void	create_event(t_iterate_events *events, void (*on_new_row)(void),
		void (*on_new_line)(void))
{
	events->on_new_row = on_new_row;
	events->on_new_line = on_new_line;
}

void	matrix_iterate(t_matrix *m, void (*f)(void *), t_iterate_events *events)
{
	size_t	i;
	size_t	total;
	char	*ptr;

	if (!m || !m->v)
		return ;
	if (!check_dimensions(m->dim))
	{
		printf("Couldn't iterate, invalid dimensions");
		return ;
	}
	total = m->dim.x * m->dim.y;
	ptr = (char *)m->v;
	i = 0;
	while (i < total)
	{
		if (events && i && i % m->dim.x == 0)
			events->on_new_line();
		f((void *)ptr);
		ptr += m->elem_size;
		if (events)
			events->on_new_row();
		i++;
	}
}

bool	matrix_for_each(t_matrix *m, bool (*f)(void *))
{
	size_t i;
	size_t total;
	char *ptr;

	if (!m || !m->v)
		return (false);
	if (!check_dimensions(m->dim))
	{
		printf("Couldn't iterate, invalid dimensions");
		return (false);
	}
	total = m->dim.x * m->dim.y;
	ptr = (char *)m->v;
	i = 0;
	while (i < total)
	{
		if (!f((void *)ptr))
			return (false);
		ptr += m->elem_size;
		i++;
	}
	return (true);
}