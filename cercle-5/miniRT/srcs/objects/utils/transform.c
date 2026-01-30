/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 18:22:56 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/30 18:28:42 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

static void	init_matrix_with_double(t_matrix *m, double v)
{
	t_index idx;

	idx.y = 0;
	for (idx.x = 0; idx.x < m->dim.x; idx.x++)
		matrix_set(m, idx, &v);
}

/* Initialize a transform: pos, rotation (both zeros) and scale (ones) */

t_transform	*init_transform(void)
{
	t_transform *t;

	t = malloc(sizeof(*t));
	if (!t)
		return (NULL);
	t->pos = create_matrix(create_index(3, 1), sizeof(double));
	t->rotation = create_matrix(create_index(3, 1), sizeof(double));
	t->scale = create_matrix(create_index(3, 1), sizeof(double));
	if (!t->pos || !t->rotation || !t->scale)
	{
		if (t->pos)
			free_matrix(t->pos, NULL);
		if (t->rotation)
			free_matrix(t->rotation, NULL);
		if (t->scale)
			free_matrix(t->scale, NULL);
		free(t);
		return (NULL);
	}

	/* initialize defaults */
	init_matrix_with_double(t->pos, 0.0);
	init_matrix_with_double(t->rotation, 0.0);
	init_matrix_with_double(t->scale, 1.0);
	return (t);
}

void	free_transform(t_transform *t)
{
	if (!t)
		return ;
	free_matrix(t->pos, NULL);
	free_matrix(t->rotation, NULL);
	free_matrix(t->scale, NULL);
	free(t);
}
