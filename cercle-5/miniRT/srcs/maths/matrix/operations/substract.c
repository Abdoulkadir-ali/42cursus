/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substract.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 02:51:36 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/28 03:41:59 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.h"

static bool	substract_float(void *v1, const void *v2)
{
	*(float *)v1 -= *(const float *)v2;
	return (0);
}

static bool	substract_double(void *v1, const void *v2)
{
	*(double *)v1 -= *(const double *)v2;
	return (0);
}

bool	matrix_substract(t_matrix *m1, const t_matrix *m2, bool (*f)(void *,
			const void *))
{
	return (matrix_op(m1, m2, &check_add, f));
}

// int	main(void)
// {
// 	t_matrix	*m1;
// 	t_matrix	*m2;

// 	m1 = create_matrix(create_index(10, 10), sizeof(float));
// 	m2 = create_matrix(create_index(10, 10), sizeof(float));
// 	m2 = NULL;
// 	print_matrix(m1, &print_float);
// 	matrix_multiply(m1, m2, &substract_float);
// 	print_matrix(m1, &print_float);
// }
