/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 03:01:50 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/28 03:26:46 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.h"

void	*get_offset(const t_matrix *m, size_t i)
{
	if (!m || !m->v)
		return (NULL);
	return ((char *)m->v + (i * m->elem_size));
}

void	*matrix_get(const t_matrix *m, t_index *i)
{
	return (get_offset(m, flatten_index(m->dim, i)));
}
