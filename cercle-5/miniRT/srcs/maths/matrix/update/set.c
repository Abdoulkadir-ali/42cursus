/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 03:01:50 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/28 03:49:12 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.h"

bool	matrix_set(t_matrix *m, t_index *i, void *new)
{
	void	*target;

	target = matrix_get(m, i);
	if (!target || !new)
		return (0);
	ft_memcpy(target, new, m->elem_size);
	return (1);
}
