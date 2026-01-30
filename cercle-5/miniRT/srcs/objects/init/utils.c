/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 05:32:33 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/30 18:25:51 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

static void	init_matrix_with_double(t_matrix *m, double v)
{
	t_index	idx;

	idx.y = 0;
	for (idx.x = 0; idx.x < m->dim.x; idx.x++)
		matrix_set(m, idx, &v);
}

/* init_transform moved to srcs/objects/utils/transform.c */


t_matrix	*init_rgb(void)
{
	t_matrix *m;

	m = create_matrix(create_index(3, 1), sizeof(double));
	if (m)
		init_matrix_with_double(m, 0.0);
	return (m);
}