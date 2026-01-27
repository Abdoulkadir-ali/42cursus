/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiply.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 20:08:56 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/27 21:19:18 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.h"

static int	multiply_float(void *v1, const void *v2)
{
	*(float *)v1 *= *(const float *)v2;
	return (0);
}

// static int	multiply_double(void *v1, const void *v2)
// {
// 	*(double *)v1 *= *(const double *)v2;
// 	return (0);
// }

int	matrix_multiply(t_matrix *m1, const t_matrix *m2, int (*f)(void *,
			const void *))
{
	return (matrix_op(m1, m2, &check_multiply, f));
}

int	main(void)
{
	t_matrix	*m1;
	t_matrix	*m2;

	m1 = create_matrix(create_index(10, 10), sizeof(float));
	m2 = create_matrix(create_index(10, 10), sizeof(float));
	m2 = NULL;
	print_matrix(m1, &print_float);
	matrix_multiply(m1, m2, &multiply_float);
	print_matrix(m1, &print_float);
}
