/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 18:12:09 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/29 06:59:23 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.h"

void	print_float(void *v)
{
	printf("%8.2f", *(float *)v);
}

void	print_double(void *v)
{
	printf("%8.2f", *(double *)v);
}

static void	print_sep(void)
{
	printf(", ");
}

static void	print_nl(void)
{
	printf("\n");
}

void	print_matrix(t_matrix *m, void (*f)(void *))
{
	t_iterate_events	events;

	if (!m || !m->dim)
		return ;
	printf("Matrix of dimensions : x : %zu\t y : %zu\n", m->dim->x, m->dim->y);
	create_event(&events, &print_sep, &print_nl);
	matrix_iterate(m, f, &events);
	printf("\n");
}
