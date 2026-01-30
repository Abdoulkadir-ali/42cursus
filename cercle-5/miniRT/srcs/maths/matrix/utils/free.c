/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 22:40:36 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/30 18:09:24 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.h"

bool	free_matrix(t_matrix *m, void (*del)(void *))
{
	if (!m)
		return (0);
	if (m->v)
	{
		if (del)
			matrix_iterate(m, del, NULL);
		free(m->v);
		m->v = NULL;
	}
	free(m);
	return (1);
}
