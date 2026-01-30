/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 02:46:38 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/30 18:09:24 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.h"

static bool	add_float(void *v1, const void *v2)
{
	*(float *)v1 += *(const float *)v2;
	return (1);
}

static bool	add_double(void *v1, const void *v2)
{
	*(double *)v1 += *(const double *)v2;
	return (1);
}

bool	matrix_add(t_matrix *m1, const t_matrix *m2, bool (*f)(void *,
			const void *))
{
	return (matrix_op(m1, m2, &check_add, f));
}

bool	matrix_add_scalar(t_matrix *m, void *v, bool (*f)(void *, const void *))
{
	t_matrix	*scalar;
	t_index		idx;
	bool		res;

	if (!m || !v)
		return (false);
	scalar = create_matrix(create_index(1, 1), m->elem_size);
	if (!scalar)
		return (false);
	idx.x = 0;
	idx.y = 0;
	matrix_set(scalar, idx, v);
	res = matrix_add(m, scalar, f);
	free_matrix(scalar, NULL);
	return (res);
}

// int	main(void)
// {
// 	t_matrix	*m1;
// 	t_matrix	*m2;
// 	float		v;
// 	size_t		i;

// 	i = 0;
// 	v = 55;
// 	m1 = create_matrix(create_index(10, 20), sizeof(float));
// 	m2 = create_matrix(create_index(1, 20), sizeof(float));
// 	while (i < 20)
// 	{
// 		matrix_set(m2, create_index(0, i++), (void *)&v);
// 		v++;
// 	}
// 	print_matrix(m1, &print_float);
// 	print_matrix(m2, &print_float);
// 	matrix_add(m1, m2, &add_float);
// 	print_matrix(m1, &print_float);
// 	matrix_transpose(&m1);
// 	print_matrix(m1, &print_float);
// }
