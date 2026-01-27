/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 17:54:58 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/27 20:45:05 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.h"

bool	check_dimensions(t_index *dim)
{
	if ((dim->x == 0 && dim->y == 0) || (dim->x > SIZE_MAX / dim->y))
		return (0);
	return (1);
}

/* We assume the dimensions are valid from this
point on to facilitate the free*/
t_matrix	*create_matrix(t_index *dim, size_t elem_size)
{
	t_matrix	*m;

	if (!check_dimensions(dim))
	{
		printf("Invalid dimensions formatrix (probably too big)\n");
		free(dim);
		return (NULL);
	}
	m = malloc(sizeof(t_matrix));
	if (!m)
		return (NULL);
	m->dim = dim;
	m->v = ft_calloc(dim->x * dim->y, elem_size);
	if (!m->v)
	{
		free(m);
		return (NULL);
	}
	return (m);
}

// int	main(void)
// {
// 	t_matrix	*my_mat;
// 	t_matrix	*pix_mat;
// 	t_index		*dim;

// 	dim = create_index(10, 10);
// 	print_index(dim);
// 	my_mat = create_matrix(dim, sizeof(float));
// 	print_matrix(my_mat, print_float);
// 	pix_mat = create_matrix(dim, sizeof(double));
// 	print_matrix(my_mat, print_double);
// 	return (0);
// }
