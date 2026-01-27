/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterate.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 18:29:01 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/27 20:06:25 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.h"

void	create_event(t_iterate_events *events, void (*on_new_row)(void),
		void (*on_new_line)(void))
{
	events->on_new_row = on_new_row;
	events->on_new_line = on_new_line;
}

void	iterate_matrix(t_matrix *m, void (*f)(void *), t_iterate_events *events)
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
	total = m->dim->x * m->dim->y;
	ptr = (char *)m->v;
	i = 0;
	while (i < total)
	{
		if (i && i % m->dim->y == 0)
			events->on_new_line();
		f((void *)ptr);
		ptr += m->elem_size;
		events->on_new_row();
		i++;
	}
}
